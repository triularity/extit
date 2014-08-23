/*
 * @(#) extit/src/ir/ir.c
 *
 * Interface Repository implementation.
 *
 * Copyright (c) 2014, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <extit/base.h>
#include <extit/ir.h>
#include <extit/platform.h>

#define	HASH_SIZE		111
#define	HASH_BUCKET_SIZE	10
#define	DELETES_PER_CLEANUP	5


typedef struct _version_list		version_list_t;

struct _version_list
{
	extit_iv_t		version;
	void *			value;
	version_list_t *	next;
};


typedef struct _hash_bucket_entry	hash_bucket_entry_t;

struct _hash_bucket_entry
{
	char *			id;
	unsigned int		hash;
	version_list_t *	version_list;
};


typedef struct _hash_bucket		hash_bucket_t;

struct _hash_bucket
{
	hash_bucket_entry_t	entries[HASH_BUCKET_SIZE];
	size_t			count;
	hash_bucket_t *		next;
};


struct _extit_ir
{
	hash_bucket_t *		buckets[HASH_SIZE];
	unsigned int		flags;
	unsigned int		num_deletes;
};


static
unsigned int
hashstring(const char *str);

static
version_list_t *
vlist_create();

static
void
vlist_destroy(version_list_t *vlist);

static
void
vlist_free(version_list_t *vlist);

static
void *
vlist_get(const version_list_t *vlist, extit_iv_t version);

static
extit_iv_t
vlist_query(const version_list_t *vlist, extit_iv_t base_version);

static
extit_status_t
vlist_remove(version_list_t **vlistp, extit_iv_t version, void **old_valuep);

static
extit_status_t
vlist_set(version_list_t **vlistp, extit_iv_t version, void *value, void **old_valuep);


/* ************************************************************ */

static
unsigned int
hashstring(const char *str)
{
	unsigned int	hv;
	char		ch;


	hv = 0;

	while((ch = *str) != '\0')
	{
		hv = (hv << 1) ^ (hv >> 10) ^ tolower(ch);
		str++;
	}

	return hv;
}


static
version_list_t *
vlist_create()
{
	return calloc(1, sizeof(version_list_t));
}


static
void
vlist_destroy(version_list_t *vlist)
{
	version_list_t *	vlist_next;


	while(vlist != NULL)
	{
		vlist_next = vlist->next;
		vlist_free(vlist);
		vlist = vlist_next;
	}
}


static
void
vlist_free(version_list_t *vlist)
{
	free(vlist);
}


static
void *
vlist_get(const version_list_t *vlist, extit_iv_t version)
{
	unsigned int		version_major;
	extit_iv_t		vlist_version;


	version_major = EXTIT_IV_MAJOR(version);

	while(vlist != NULL)
	{
		vlist_version = vlist->version;

		/*
		 * Matching version?
		 */
		if(vlist_version == version)
			return vlist->value;

		if(vlist_version > version)
		{
			/*
			 * For non 0.x, take the first higher minor version
			 */
			if((version_major != 0)
			 && (EXTIT_IV_MAJOR(vlist_version) == version_major))
			{
				return vlist->value;
			}

			/*
			 * Not found
			 */
			return NULL;
		}

		vlist = vlist->next;
	}

	return NULL;
}


static
extit_iv_t
vlist_query(const version_list_t *vlist, extit_iv_t base_version)
{
	unsigned int		base_version_major;
	extit_iv_t		result;
	extit_iv_t		vlist_version;


	base_version_major = EXTIT_IV_MAJOR(base_version);
	result = EXTIT_IV_NONE;

	while(vlist != NULL)
	{
		vlist_version = vlist->version;

		if(EXTIT_IV_MAJOR(vlist_version) == base_version_major)
		{
			if(vlist_version == base_version)
			{
				result = vlist_version;
			}
			else if((base_version_major != 0)
			 && (vlist_version > base_version))
			{
				result = vlist_version;
			}
		}
		else if(EXTIT_IV_MAJOR(vlist_version) > base_version_major)
		{
			/*
			 * Passed it, so we are done
			 */
			break;
		}

		vlist = vlist->next;
	}

	return result;
}


static
extit_status_t
vlist_remove(version_list_t **vlistp, extit_iv_t version, void **old_valuep)
{
	version_list_t *	vlist;
	extit_iv_t		vlist_version;


	while((vlist = *vlistp) != NULL)
	{
		vlist_version = vlist->version;

		if(vlist_version == version)
		{
			*old_valuep = vlist->value;

			*vlistp = vlist->next;
			vlist_free(vlist);

			return EXTIT_STATUS_OK;
		}
		else if(vlist_version > version)
		{
			/*
			 * Not found
			 */
			break;
		}

		vlistp = &vlist->next;
	}

	return EXTIT_STATUS_FAIL;
}


static
extit_status_t
vlist_set(version_list_t **vlistp, extit_iv_t version, void *value, void **old_valuep)
{
	version_list_t *	vlist;
	extit_iv_t		vlist_version;
	version_list_t *	vlist_new;


	while((vlist = *vlistp) != NULL)
	{
		vlist_version = vlist->version;

		if(vlist_version == version)
		{
			/*
			 * Just replace the existing entry
			 */
			*old_valuep = vlist->value;
			vlist->value = value;

			return EXTIT_STATUS_OK;
		}

		if(vlist_version > version)
			break;

		vlistp = &vlist->next;
	}

	/*
	 * New entry
	 */
	if((vlist_new = vlist_create()) == NULL)
		return EXTIT_STATUS_NOMEM;

	vlist_new->version = version;
	vlist_new->value = value;

	vlist_new->next = *vlistp;
	*vlistp = vlist_new;

	*old_valuep = NULL;

	return EXTIT_STATUS_OK;
}


static
hash_bucket_t *
bucket_create()
{
	return calloc(1, sizeof(hash_bucket_t));
}


static
void
bucket_cleanup(hash_bucket_t **bucketp, unsigned int flags)
{
	size_t			count;
	size_t			idx;
	hash_bucket_t *		bucket;
	hash_bucket_entry_t *	entry;


	while((bucket = *bucketp) != NULL)
	{
		count = bucket->count;

		for(idx = 0; idx < count; idx++)
		{
			entry = &bucket->entries[idx];

			if(entry->version_list == NULL)
			{
#ifdef	EXTIT_DEBUG
				if((flags & EXTIT_FLAG_LOG)
				 >= EXTIT_FLAG_LOG_DEBUG)
				{
					fprintf(stderr,
				"[extit:ir] Removing interface [%s].\n",
						entry->id);
				}
#endif	/* EXTIT_DEBUG */

				free(entry->id);

				if(--count > idx)
				{
					/*
					 * Move the last one to this slot
					 */
					bucket->entries[idx] =
						bucket->entries[count];
				}
			}
		}

		if(count == 0)
		{
#ifdef	EXTIT_DEBUG
			if((flags & EXTIT_FLAG_LOG)
			 >= EXTIT_FLAG_LOG_TRACE)
			{
				fprintf(stderr,
				 "[extit:ir] Removing empty bucket.\n");
			}
#endif	/* EXTIT_DEBUG */

			*bucketp = bucket->next;
			free(bucket);
		}
		else
		{
			bucket->count = count;
			bucketp = &bucket->next;
		}
	}
}


static
void
bucket_destroy(hash_bucket_t *bucket, unsigned int flags)
{
	size_t			count;
	size_t			idx;
	hash_bucket_entry_t *	entry;
	hash_bucket_t *		bucket_next;


	while(bucket != NULL)
	{
		count = bucket->count;

		for(idx = 0; idx < count; idx++)
		{
			entry = &bucket->entries[idx];

#ifdef	EXTIT_DEBUG
			if((flags & EXTIT_FLAG_LOG)
			 >= EXTIT_FLAG_LOG_TRACE)
			{
				fprintf(stderr,
				 "[extit:ir] Destroying interface [%s].\n",
					entry->id);
			}
#endif	/* EXTIT_DEBUG */

			free(entry->id);
			vlist_destroy(entry->version_list);
		}

		bucket_next = bucket->next;
		free(bucket);
		bucket = bucket_next;
	}
}


static
version_list_t **
bucket_get_vlistp(const hash_bucket_t *bucket, const char *id, unsigned int hash)
{
	size_t			count;
	size_t			idx;
	hash_bucket_entry_t *	entry;


	while(bucket != NULL)
	{
		count = bucket->count;

		for(idx = 0; idx < count; idx++)
		{
			entry = (hash_bucket_entry_t *) &bucket->entries[idx];

			if((entry->hash == hash)
			 && (EXTIT_STRCASECMP(entry->id, id) == 0))
			{
				return &entry->version_list;
			}
		}

		bucket = bucket->next;
	}

	return NULL;
}


static
void *
bucket_get(const hash_bucket_t *bucket, const char *id, unsigned int hash, extit_iv_t version)
{
	version_list_t **	vlistp;


	if((vlistp = bucket_get_vlistp(bucket, id, hash)) == NULL)
		return NULL;

	return vlist_get(*vlistp, version);
}


static
extit_iv_t
bucket_query(const hash_bucket_t *bucket, const char *id, unsigned int hash, extit_iv_t base_version)
{
	version_list_t **	vlistp;


	if((vlistp = bucket_get_vlistp(bucket, id, hash)) == NULL)
		return EXTIT_IV_NONE;

	return vlist_query(*vlistp, base_version);
}


static
extit_status_t
bucket_remove(hash_bucket_t **bucketp, const char *id, unsigned int hash, extit_iv_t version, void **old_valuep)
{
	version_list_t **	vlistp;


	if((vlistp = bucket_get_vlistp(*bucketp, id, hash)) == NULL)
		return EXTIT_STATUS_FAIL;

	return vlist_remove(vlistp, version, old_valuep);
}


static
extit_status_t
bucket_set(hash_bucket_t **bucketp, const char *id, unsigned int hash, extit_iv_t version, void *value, void **old_valuep)
{
	hash_bucket_t *		available;
	hash_bucket_t *		bucket;
	size_t			count;
	size_t			idx;
	hash_bucket_entry_t *	entry;


	bucket = *bucketp;
	available = NULL;

	while(bucket != NULL)
	{
		count = bucket->count;

		if((available == NULL) && (bucket->count < HASH_BUCKET_SIZE))
			available = bucket;

		for(idx = 0; idx < count; idx++)
		{
			entry = &bucket->entries[idx];

			if((entry->hash == hash)
			 && (EXTIT_STRCASECMP(entry->id, id) == 0))
			{
				return vlist_set(
					&entry->version_list,
					version,
					value,
					old_valuep);
			}
		}

		bucket = bucket->next;
	}

	if(available == NULL)
	{
		/*
		 * No existing available space
		 */
		available = bucket_create();

		available->next = *bucketp;
		*bucketp = available;
	}

	entry = &available->entries[available->count];

	if((entry->id = malloc(strlen(id + 1))) == NULL)
		return EXTIT_STATUS_NOMEM;

	strcpy(entry->id, id);

	entry->hash = hash;
	entry->version_list = NULL;

	available->count++;

	return vlist_set(&entry->version_list, version, value, old_valuep);
}


/**
 ** Interface Repository (v1.0)
 **/

EXTIT_EXPORT
void
EXTIT_DECL
extit_ir_cleanup(extit_ir_t *ir)
{
	size_t		idx;
	unsigned int	flags;


	flags = ir->flags;

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		fprintf(stderr, "[extit:ir] {%p} Cleanup.\n", (void *) ir);
#endif	/* EXTIT_DEBUG */

	for(idx = 0; idx < HASH_SIZE; idx++)
		bucket_cleanup(&ir->buckets[idx], flags);

	ir->num_deletes = 0;
}


EXTIT_EXPORT
extit_ir_t *
EXTIT_DECL
extit_ir_create(unsigned int flags)
{
	extit_ir_t *	ir;


	ir = calloc(1, sizeof(extit_ir_t));

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		fprintf(stderr, "[extit:ir] {%p} Create.\n", (void *) ir);
#endif	/* EXTIT_DEBUG */

	ir->flags = flags;

	return ir;
}


EXTIT_EXPORT
void
EXTIT_DECL
extit_ir_destroy(extit_ir_t *ir)
{
	size_t		idx;
	unsigned int	flags;


	flags = ir->flags;

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
		fprintf(stderr, "[extit:ir] {%p} Destroy.\n", (void *) ir);
#endif	/* EXTIT_DEBUG */

	for(idx = 0; idx < HASH_SIZE; idx++)
		bucket_destroy(ir->buckets[idx], flags);
}


EXTIT_EXPORT
unsigned int
EXTIT_DECL
extit_ir_getFlags(const extit_ir_t *ir)
{
	return ir->flags;
}


EXTIT_EXPORT
void *
EXTIT_DECL
extit_ir_getInterface(const extit_ir_t *ir, const char *id, extit_iv_t version)
{
	unsigned int	hash;
	unsigned int	flags;


	if(id == NULL)
		return NULL;

	flags = ir->flags;

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
	{
		fprintf(stderr,
			"[extit:ir] {%p} Get interface [%s@%d.%d].\n",
			(void *) ir,
			id,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
#endif	/* EXTIT_DEBUG */

	if(version == EXTIT_IV_NONE)
		return NULL;

	hash = hashstring(id);

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
		fprintf(stderr, "[extit:ir] Hash [%s] = %u.\n", id, hash);
#endif	/* EXTIT_DEBUG */

	return bucket_get(ir->buckets[hash % HASH_SIZE], id, hash, version);
}


EXTIT_EXPORT
extit_iv_t
EXTIT_DECL
extit_ir_queryInterface(const extit_ir_t *ir, const char *id, extit_iv_t base_version)
{
	unsigned int	hash;
	unsigned int	flags;


	if(id == NULL)
		return EXTIT_STATUS_INVALID;

	flags = ir->flags;

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
	{
		fprintf(stderr,
			"[extit:ir] {%p} Query interface [%s@%d.%d].\n",
			(void *) ir,
			id,
			EXTIT_IV_MAJOR(base_version),
			EXTIT_IV_MINOR(base_version));
	}
#endif	/* EXTIT_DEBUG */

	if(base_version == EXTIT_IV_NONE)
		return EXTIT_STATUS_INVALID;

	hash = hashstring(id);

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:ir] Hash [%s] = %u.\n", id, hash);
	}
#endif	/* EXTIT_DEBUG */

	return bucket_query(
		ir->buckets[hash % HASH_SIZE], id, hash, base_version);
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_ir_removeInterface(extit_ir_t *ir, const char *id, extit_iv_t version, void *old_valuep)
{
	unsigned int	flags;
	void *		old_value;
	unsigned int	hash;
	extit_status_t	status;


	if(id == NULL)
		return EXTIT_STATUS_INVALID;

	flags = ir->flags;

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
	{
		fprintf(stderr,
			"[extit:ir] {%p} Remove interface [%s@%d.%d].\n",
			(void *) ir,
			id,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
#endif	/* EXTIT_DEBUG */

	if(version == EXTIT_IV_NONE)
		return EXTIT_STATUS_INVALID;

	if(old_valuep == NULL)
		old_valuep = &old_value;

	hash = hashstring(id);

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:ir] Hash [%s] = %u.\n", id, hash);
	}
#endif	/* EXTIT_DEBUG */

	status = bucket_remove(
		&ir->buckets[hash % HASH_SIZE],
		id,
		hash,
		version,
		old_valuep);

	if(status == EXTIT_STATUS_OK)
	{
		if(++ir->num_deletes >= DELETES_PER_CLEANUP)
			extit_ir_cleanup(ir);
	}

	return status;
}


EXTIT_EXPORT
void
EXTIT_DECL
extit_ir_setFlags(extit_ir_t *ir, unsigned int flags)
{
	ir->flags = flags;
}


EXTIT_EXPORT
extit_status_t
EXTIT_DECL
extit_ir_setInterface(extit_ir_t *ir, const char *id, extit_iv_t version, void *value, void *old_valuep)
{
	unsigned int	flags;
	unsigned int	hash;
	void *		old_value;


	if(id == NULL)
		return EXTIT_STATUS_INVALID;

	/*
	 * Can't 'unset' this way
	 */
	if(value == NULL)
		return EXTIT_STATUS_INVALID;

	flags = ir->flags;

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_DEBUG)
	{
		fprintf(stderr,
			"[extit:ir] {%p} Set interface [%s@%d.%d].\n",
			(void *) ir,
			id,
			EXTIT_IV_MAJOR(version),
			EXTIT_IV_MINOR(version));
	}
#endif	/* EXTIT_DEBUG */

	if(version == EXTIT_IV_NONE)
		return EXTIT_STATUS_INVALID;

	if(old_valuep == NULL)
		old_valuep = &old_value;

	hash = hashstring(id);

#ifdef	EXTIT_DEBUG
	if((flags & EXTIT_FLAG_LOG) >= EXTIT_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[extit:ir] Hash [%s] = %u.\n", id, hash);
	}
#endif	/* EXTIT_DEBUG */

	return bucket_set(
		&ir->buckets[hash % HASH_SIZE],
		id,
		hash,
		version,
		value,
		old_valuep);
}


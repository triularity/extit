/*
 * @(#) extit/src/iv/repository.c
 *
 * Interface Versioning Repository implementation.
 *
 * Copyright (c) 2015, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <iv/base.h>
#include <iv/repository.h>

#define	HASH_SIZE		111
#define	HASH_BUCKET_SIZE	10
#define	DELETES_PER_CLEANUP	5


static unsigned int		_iv_repository_defaultFlags = \
					IV_REPOSITORY_FLAG_LOG_NORMAL;


typedef struct _version_list		version_list_t;

struct _version_list
{
	iv_version_t		version;
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


struct _iv_repository
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
vlist_get(const version_list_t *vlist, iv_version_t version);

static
iv_version_t
vlist_query(const version_list_t *vlist, iv_version_t base_version);

static
iv_repository_status_t
vlist_remove(version_list_t **vlistp, iv_version_t version, void **old_valuep);

static
iv_repository_status_t
vlist_set(version_list_t **vlistp, iv_version_t version, void *value, void **old_valuep);


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
		hv = (hv << 1) ^ (hv >> 10) ^ ch;
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
vlist_get(const version_list_t *vlist, iv_version_t version)
{
	unsigned int		version_major;
	iv_version_t		vlist_version;


	version_major = IV_VERSION_MAJOR(version);

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
			 && (IV_VERSION_MAJOR(vlist_version) == version_major))
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
iv_version_t
vlist_query(const version_list_t *vlist, iv_version_t base_version)
{
	unsigned int		base_version_major;
	iv_version_t		result;
	iv_version_t		vlist_version;


	base_version_major = IV_VERSION_MAJOR(base_version);
	result = IV_VERSION_NONE;

	while(vlist != NULL)
	{
		vlist_version = vlist->version;

		if(IV_VERSION_MAJOR(vlist_version) == base_version_major)
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
		else if(IV_VERSION_MAJOR(vlist_version) > base_version_major)
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
iv_repository_status_t
vlist_remove(version_list_t **vlistp, iv_version_t version, void **old_valuep)
{
	version_list_t *	vlist;
	iv_version_t		vlist_version;


	while((vlist = *vlistp) != NULL)
	{
		vlist_version = vlist->version;

		if(vlist_version == version)
		{
			*old_valuep = vlist->value;

			*vlistp = vlist->next;
			vlist_free(vlist);

			return IV_REPOSITORY_STATUS_OK;
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

	return IV_REPOSITORY_STATUS_FAIL;
}


static
iv_repository_status_t
vlist_set(version_list_t **vlistp, iv_version_t version, void *value, void **old_valuep)
{
	version_list_t *	vlist;
	iv_version_t		vlist_version;
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

			return IV_REPOSITORY_STATUS_OK;
		}

		if(vlist_version > version)
			break;

		vlistp = &vlist->next;
	}

	/*
	 * New entry
	 */
	if((vlist_new = vlist_create()) == NULL)
		return IV_REPOSITORY_STATUS_NOMEM;

	vlist_new->version = version;
	vlist_new->value = value;

	vlist_new->next = *vlistp;
	*vlistp = vlist_new;

	*old_valuep = NULL;

	return IV_REPOSITORY_STATUS_OK;
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
#ifdef	IV_REPOSITORY_DEBUG
				if((flags & IV_REPOSITORY_FLAG_LOG)
				 >= IV_REPOSITORY_FLAG_LOG_DEBUG)
				{
					fprintf(stderr,
				"[iv:repository] Removing interface [%s].\n",
						entry->id);
				}
#endif	/* IV_REPOSITORY_DEBUG */

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
#ifdef	IV_REPOSITORY_DEBUG
			if((flags & IV_REPOSITORY_FLAG_LOG)
			 >= IV_REPOSITORY_FLAG_LOG_TRACE)
			{
				fprintf(stderr,
				 "[iv:repository] Removing empty bucket.\n");
			}
#endif	/* IV_REPOSITORY_DEBUG */

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

#ifdef	IV_REPOSITORY_DEBUG
			if((flags & IV_REPOSITORY_FLAG_LOG)
			 >= IV_REPOSITORY_FLAG_LOG_TRACE)
			{
				fprintf(stderr,
				 "[iv:repository] Destroying interface [%s].\n",
					entry->id);
			}
#endif	/* IV_REPOSITORY_DEBUG */

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
			 && (strcmp(entry->id, id) == 0))
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
bucket_get(const hash_bucket_t *bucket, const char *id, unsigned int hash, iv_version_t version)
{
	version_list_t **	vlistp;


	if((vlistp = bucket_get_vlistp(bucket, id, hash)) == NULL)
		return NULL;

	return vlist_get(*vlistp, version);
}


static
iv_version_t
bucket_query(const hash_bucket_t *bucket, const char *id, unsigned int hash, iv_version_t base_version)
{
	version_list_t **	vlistp;


	if((vlistp = bucket_get_vlistp(bucket, id, hash)) == NULL)
		return IV_VERSION_NONE;

	return vlist_query(*vlistp, base_version);
}


static
iv_repository_status_t
bucket_remove(hash_bucket_t **bucketp, const char *id, unsigned int hash, iv_version_t version, void **old_valuep)
{
	version_list_t **	vlistp;


	if((vlistp = bucket_get_vlistp(*bucketp, id, hash)) == NULL)
		return IV_REPOSITORY_STATUS_FAIL;

	return vlist_remove(vlistp, version, old_valuep);
}


static
iv_repository_status_t
bucket_set(hash_bucket_t **bucketp, const char *id, unsigned int hash, iv_version_t version, void *value, void **old_valuep)
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

		if((available == NULL) && (count < HASH_BUCKET_SIZE))
			available = bucket;

		for(idx = 0; idx < count; idx++)
		{
			entry = &bucket->entries[idx];

			if((entry->hash == hash)
			 && (strcmp(entry->id, id) == 0))
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

	if((entry->id = malloc(strlen(id) + 1)) == NULL)
		return IV_REPOSITORY_STATUS_NOMEM;

	strcpy(entry->id, id);

	entry->hash = hash;
	entry->version_list = NULL;

	available->count++;

	return vlist_set(&entry->version_list, version, value, old_valuep);
}


/**
 ** Public API (v1.0)
 **/

IV_EXPORT
void
IV_DECL
iv_repository_cleanup(iv_repository_t *ivr)
{
	size_t		idx;
	unsigned int	flags;


	flags = ivr->flags;

#ifdef	IV_REPOSITORY_DEBUG
	if((flags & IV_REPOSITORY_FLAG_LOG) >= IV_REPOSITORY_FLAG_LOG_DEBUG)
	{
		fprintf(stderr, "[iv:repository] {%p} Cleanup.\n",
			(void *) ivr);
	}
#endif	/* IV_REPOSITORY_DEBUG */

	for(idx = 0; idx < HASH_SIZE; idx++)
		bucket_cleanup(&ivr->buckets[idx], flags);

	ivr->num_deletes = 0;
}


IV_EXPORT
iv_repository_t *
IV_DECL
iv_repository_create()
{
	unsigned int		flags;
	iv_repository_t *	ivr;


	flags = _iv_repository_defaultFlags;

	ivr = calloc(1, sizeof(iv_repository_t));

#ifdef	IV_REPOSITORY_DEBUG
	if((flags & IV_REPOSITORY_FLAG_LOG) >= IV_REPOSITORY_FLAG_LOG_DEBUG)
	{
		fprintf(stderr, "[iv:repository] {%p} Create.\n",
			(void *) ivr);
	}
#endif	/* IV_REPOSITORY_DEBUG */

	ivr->flags = flags;

	return ivr;
}


IV_EXPORT
void
IV_DECL
iv_repository_destroy(iv_repository_t *ivr)
{
	size_t		idx;
	unsigned int	flags;


	flags = ivr->flags;

#ifdef	IV_REPOSITORY_DEBUG
	if((flags & IV_REPOSITORY_FLAG_LOG) >= IV_REPOSITORY_FLAG_LOG_DEBUG)
	{
		fprintf(stderr, "[iv:repository] {%p} Destroy.\n",
			(void *) ivr);
	}
#endif	/* IV_REPOSITORY_DEBUG */

	for(idx = 0; idx < HASH_SIZE; idx++)
		bucket_destroy(ivr->buckets[idx], flags);

	free(ivr);
}


IV_EXPORT
void *
IV_DECL
iv_repository_get(const iv_repository_t *ivr, const char *id, iv_version_t version)
{
	unsigned int	hash;
	unsigned int	flags;


	if(id == NULL)
		return NULL;

	flags = ivr->flags;

#ifdef	IV_REPOSITORY_DEBUG
	if((flags & IV_REPOSITORY_FLAG_LOG) >= IV_REPOSITORY_FLAG_LOG_DEBUG)
	{
		fprintf(stderr,
			"[iv:repository] {%p} Get interface [%s@%d.%d].\n",
			(void *) ivr,
			id,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
#endif	/* IV_REPOSITORY_DEBUG */

	if(version == IV_VERSION_NONE)
		return NULL;

	hash = hashstring(id);

#ifdef	IV_REPOSITORY_DEBUG
	if((flags & IV_REPOSITORY_FLAG_LOG) >= IV_REPOSITORY_FLAG_LOG_TRACE)
		fprintf(stderr, "[iv:repository] Hash [%s] = %u.\n", id, hash);
#endif	/* IV_REPOSITORY_DEBUG */

	return bucket_get(ivr->buckets[hash % HASH_SIZE], id, hash, version);
}


IV_EXPORT
unsigned int
IV_DECL
iv_repository_getDefaultFlags()
{
	return _iv_repository_defaultFlags;
}


IV_EXPORT
unsigned int
IV_DECL
iv_repository_getFlags(const iv_repository_t *ivr)
{
	return ivr->flags;
}


IV_EXPORT
iv_version_t
IV_DECL
iv_repository_query(const iv_repository_t *ivr, const char *id, iv_version_t base_version)
{
	unsigned int	hash;
	unsigned int	flags;


	if(id == NULL)
		return IV_REPOSITORY_STATUS_INVALID;

	flags = ivr->flags;

#ifdef	IV_REPOSITORY_DEBUG
	if((flags & IV_REPOSITORY_FLAG_LOG) >= IV_REPOSITORY_FLAG_LOG_DEBUG)
	{
		fprintf(stderr,
			"[iv:repository] {%p} Query interface [%s@%d.%d].\n",
			(void *) ivr,
			id,
			IV_VERSION_MAJOR(base_version),
			IV_VERSION_MINOR(base_version));
	}
#endif	/* IV_REPOSITORY_DEBUG */

	if(base_version == IV_VERSION_NONE)
		return IV_REPOSITORY_STATUS_INVALID;

	hash = hashstring(id);

#ifdef	IV_REPOSITORY_DEBUG
	if((flags & IV_REPOSITORY_FLAG_LOG) >= IV_REPOSITORY_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[iv:repository] Hash [%s] = %u.\n", id, hash);
	}
#endif	/* IV_REPOSITORY_DEBUG */

	return bucket_query(
		ivr->buckets[hash % HASH_SIZE], id, hash, base_version);
}


IV_EXPORT
iv_repository_status_t
IV_DECL
iv_repository_remove(iv_repository_t *ivr, const char *id, iv_version_t version, void *old_valuep)
{
	unsigned int	flags;
	void *		old_value;
	unsigned int	hash;
	iv_repository_status_t	status;


	if(id == NULL)
		return IV_REPOSITORY_STATUS_INVALID;

	flags = ivr->flags;

#ifdef	IV_REPOSITORY_DEBUG
	if((flags & IV_REPOSITORY_FLAG_LOG) >= IV_REPOSITORY_FLAG_LOG_DEBUG)
	{
		fprintf(stderr,
			"[iv:repository] {%p} Remove interface [%s@%d.%d].\n",
			(void *) ivr,
			id,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
#endif	/* IV_REPOSITORY_DEBUG */

	if(version == IV_VERSION_NONE)
		return IV_REPOSITORY_STATUS_INVALID;

	if(old_valuep == NULL)
		old_valuep = &old_value;

	hash = hashstring(id);

#ifdef	IV_REPOSITORY_DEBUG
	if((flags & IV_REPOSITORY_FLAG_LOG) >= IV_REPOSITORY_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[iv:repository] Hash [%s] = %u.\n", id, hash);
	}
#endif	/* IV_REPOSITORY_DEBUG */

	status = bucket_remove(
		&ivr->buckets[hash % HASH_SIZE],
		id,
		hash,
		version,
		old_valuep);

	if(status == IV_REPOSITORY_STATUS_OK)
	{
		if(++ivr->num_deletes >= DELETES_PER_CLEANUP)
			iv_repository_cleanup(ivr);
	}

	return status;
}


IV_EXPORT
iv_repository_status_t
IV_DECL
iv_repository_set(iv_repository_t *ivr, const char *id, iv_version_t version, void *value, void *old_valuep)
{
	unsigned int	flags;
	unsigned int	hash;
	void *		old_value;


	if(id == NULL)
		return IV_REPOSITORY_STATUS_INVALID;

	/*
	 * Can't 'unset' this way
	 */
	if(value == NULL)
		return IV_REPOSITORY_STATUS_INVALID;

	flags = ivr->flags;

#ifdef	IV_REPOSITORY_DEBUG
	if((flags & IV_REPOSITORY_FLAG_LOG) >= IV_REPOSITORY_FLAG_LOG_DEBUG)
	{
		fprintf(stderr,
			"[iv:repository] {%p} Set interface [%s@%d.%d].\n",
			(void *) ivr,
			id,
			IV_VERSION_MAJOR(version),
			IV_VERSION_MINOR(version));
	}
#endif	/* IV_REPOSITORY_DEBUG */

	if(version == IV_VERSION_NONE)
		return IV_REPOSITORY_STATUS_INVALID;

	if(old_valuep == NULL)
		old_valuep = &old_value;

	hash = hashstring(id);

#ifdef	IV_REPOSITORY_DEBUG
	if((flags & IV_REPOSITORY_FLAG_LOG) >= IV_REPOSITORY_FLAG_LOG_TRACE)
	{
		fprintf(stderr,
			"[iv:repository] Hash [%s] = %u.\n", id, hash);
	}
#endif	/* IV_REPOSITORY_DEBUG */

	return bucket_set(
		&ivr->buckets[hash % HASH_SIZE],
		id,
		hash,
		version,
		value,
		old_valuep);
}


IV_EXPORT
void
IV_DECL
iv_repository_setDefaultFlags(unsigned int flags)
{
	_iv_repository_defaultFlags = flags;
}


IV_EXPORT
void
IV_DECL
iv_repository_setFlags(iv_repository_t *ivr, unsigned int flags)
{
	ivr->flags = flags;
}

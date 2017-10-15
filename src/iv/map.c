/*
 * @(#) extit/src/iv/map.c
 *
 * Interface versioning ID map.
 *
 * Copyright (c) 2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <iv/base.h>
#include <iv/map.h>
#include <iv/util.h>

#define	DEFAULT_HASH_SIZE	29
#define	BUCKET_SIZE		10


typedef struct _bucket_entry
{
	char *			nid;
	char *			iid;
	uint32_t		hashval;
	void *			value;
} bucket_entry_t;


typedef struct _bucket		bucket_t;

struct _bucket
{
	bucket_entry_t		entries[BUCKET_SIZE];
	size_t			count;
	bucket_t *		next;
};


struct _iv_map
{
	bucket_t **		buckets;
	uint32_t		hashsize;
	void			(*free_func)(void *);
};


/*
 * Compute a hash value for a string.
 */
static
uint32_t
calchash(const char *buf)
{
	uint32_t	hv;
	uint32_t	len;


	hv = 0;
	len = 0;

	while(len-- != 0)
	{
		hv = (hv << 1) ^ (hv >> 31) ^ *buf;
		buf++;
		len++;
	}

	return hv ^ len;
}


static
bucket_t *
bucket_create(void)
{
	bucket_t *	bucket;


	if((bucket = malloc(sizeof(bucket_t))) != NULL)
	{
		bucket->count = 0;
		bucket->next = NULL;
	}

	return bucket;
}


static
void **
bucket_acquire_valueptr
(
	bucket_t **bucketp,
	const char *nid,
	const char *iid,
	uint32_t hashval,
	const char **internal_nidp,
	const char **internal_iidp
)
{
	bucket_t *		available;
	bucket_t *		bucket;
	size_t			count;
	size_t			idx;
	bucket_entry_t *	entry;
	char *			key;
	size_t			nidlen;
	size_t			keylen;


	bucket = *bucketp;
	available = NULL;

	while(bucket != NULL)
	{
		count = bucket->count;

		if((available == NULL) && (count < BUCKET_SIZE))
			available = bucket;

		for(idx = 0; idx < count; idx++)
		{
			entry = &bucket->entries[idx];

			if((entry->hashval == hashval)
			 && (IV_IID_STRCMP(entry->iid, iid) == 0)
			 && (strcmp(entry->nid, nid) == 0))
			{
				if(internal_nidp != NULL)
					*internal_nidp = entry->nid;

				if(internal_iidp != NULL)
					*internal_iidp = entry->iid;

				return &entry->value;
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

	nidlen = strlen(nid) + 1;
	keylen = nidlen + strlen(iid) + 1;

	if((key = malloc(keylen)) == NULL)
		return NULL;

	strcpy(key, nid);
	entry->nid = key;

	key += nidlen;

	strcpy(key, iid);
	entry->iid = key;

	entry->hashval = hashval;
	entry->value = NULL;

	available->count++;

	if(internal_nidp != NULL)
		*internal_nidp = entry->nid;

	if(internal_iidp != NULL)
		*internal_iidp = entry->iid;

	return &entry->value;
}


static
void
bucket_cleanup
(
	bucket_t **bucketp,
	void (*value_cleaner)(void **valueptr)
)
{
	size_t			count;
	size_t			idx;
	bucket_t *		bucket;
	bucket_entry_t *	entry;


	while((bucket = *bucketp) != NULL)
	{
		count = bucket->count;

		for(idx = 0; idx < count; idx++)
		{
			entry = &bucket->entries[idx];

			if((entry->value != NULL) && (value_cleaner != NULL))
				value_cleaner(&entry->value);

			if(entry->value == NULL)
			{
				free(entry->nid);

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
bucket_destroy
(
	bucket_t *bucket,
	void (*free_func)(void *value)
)
{
	size_t			count;
	size_t			idx;
	bucket_entry_t *	entry;
	bucket_t *		bucket_next;


	while(bucket != NULL)
	{
		count = bucket->count;

		for(idx = 0; idx < count; idx++)
		{
			entry = &bucket->entries[idx];

			free(entry->nid);

			if((entry->value != NULL) && (free_func != NULL))
				free_func(entry->value);
		}

		bucket_next = bucket->next;
		free(bucket);

		bucket = bucket_next;
	}
}


static
bucket_entry_t *
bucket_get
(
	const bucket_t *bucket,
	const char *nid,
	const char *iid,
	uint32_t hashval
)
{
	size_t			count;
	size_t			idx;
	bucket_entry_t *	entry;


	while(bucket != NULL)
	{
		count = bucket->count;

		for(idx = 0; idx < count; idx++)
		{
			entry = (bucket_entry_t *) &bucket->entries[idx];

			if((entry->hashval == hashval)
			 && (IV_IID_STRCMP(entry->iid, iid) == 0)
			 && (strcmp(entry->nid, nid) == 0))
			{
				return entry;
			}
		}

		bucket = bucket->next;
	}

	return NULL;
}


static
void **
bucket_get_valueptr
(
	const bucket_t *bucket,
	const char *nid,
	const char *iid,
	uint32_t hashval
)
{
	bucket_entry_t *	entry;


	if((entry = bucket_get(bucket, nid, iid, hashval)) == NULL)
		return NULL;

	return &entry->value;
}



iv_map_t *
IV_DECL
iv_map_create
(
	uint32_t hashsize,
	void (*free_func)(void *value)
)
{
	iv_map_t *	map;


	if(hashsize == 0)
		hashsize = DEFAULT_HASH_SIZE;

	if((map = calloc(
	 1, sizeof(iv_map_t) + (sizeof(bucket_t *) * hashsize))) != NULL)
	{
		map->buckets = (bucket_t **) &map[1];
		map->hashsize = hashsize;
		map->free_func = free_func;
	}

	return map;
}


void **
IV_DECL
iv_map_acquire_valueptr
(
	iv_map_t *map,
	const char *nid,
	const char *iid,
	const char **internal_nidp,
	const char **internal_iidp
)
{
	uint32_t	hashval;


#ifdef	IV_PARANOID
	if(nid == NULL)
		return NULL;

	if(iid == NULL)
		return NULL;
#endif	/* IV_PARANOID */

	hashval = (calchash(nid) << 4) ^ calchash(iid);

	return bucket_acquire_valueptr(
		&map->buckets[hashval % map->hashsize],
		nid,
		iid,
		hashval,
		internal_nidp,
		internal_iidp);
}


void
IV_DECL
iv_map_cleanup
(
	iv_map_t *map,
	void (*value_cleaner)(void **valueptr)
)
{
	size_t		i;


	for(i = 0; i < map->hashsize; i++)
		bucket_cleanup(&map->buckets[i], value_cleaner);
}


void
IV_DECL
iv_map_destroy
(
	iv_map_t *map
)
{
	size_t		i;
	bucket_t *	bucket;


	for(i = 0; i < map->hashsize; i++)
	{
		if((bucket = map->buckets[i]) != NULL)
			bucket_destroy(bucket, map->free_func);
	}
}


void *
IV_DECL
iv_map_get
(
	iv_map_t *map,
	const char *nid,
	const char *iid
)
{
	uint32_t		hashval;
	bucket_entry_t *	entry;


#ifdef	IV_PARANOID
	if(nid == NULL)
		return NULL;

	if(iid == NULL)
		return NULL;
#endif	/* IV_PARANOID */

	hashval = (calchash(nid) << 4) ^ calchash(iid);

	entry = bucket_get(
		map->buckets[hashval % map->hashsize],
		nid,
		iid,
		hashval);

	if(entry == NULL)
		return NULL;

	return entry->value;
}


void **
IV_DECL
iv_map_get_valueptr
(
	iv_map_t *map,
	const char *nid,
	const char *iid
)
{
	uint32_t	hashval;


#ifdef	IV_PARANOID
	if(nid == NULL)
		return NULL;

	if(iid == NULL)
		return NULL;
#endif	/* IV_PARANOID */

	hashval = (calchash(nid) << 4) ^ calchash(iid);

	return bucket_get_valueptr(
		map->buckets[hashval % map->hashsize],
		nid,
		iid,
		hashval);
}


const char *
IV_DECL
iv_map_intern_interfaceid
(
	iv_map_t *map,
	const char *nid,
	const char *iid
)
{
	uint32_t		hashval;
	bucket_entry_t *	entry;


#ifdef	IV_PARANOID
	if(nid == NULL)
		return NULL;

	if(iid == NULL)
		return NULL;
#endif	/* IV_PARANOID */

	hashval = (calchash(nid) << 4) ^ calchash(iid);

	entry = bucket_get(
		map->buckets[hashval % map->hashsize],
		nid,
		iid,
		hashval);

	if(entry == NULL)
		return NULL;

	return entry->iid;
}


const char *
IV_DECL
iv_map_intern_nameid
(
	iv_map_t *map,
	const char *nid,
	const char *iid
)
{
	uint32_t		hashval;
	bucket_entry_t *	entry;


#ifdef	IV_PARANOID
	if(nid == NULL)
		return NULL;

	if(iid == NULL)
		return NULL;
#endif	/* IV_PARANOID */

	hashval = (calchash(nid) << 4) ^ calchash(iid);

	entry = bucket_get(
		map->buckets[hashval % map->hashsize],
		nid,
		iid,
		hashval);

	if(entry == NULL)
		return NULL;

	return entry->nid;
}

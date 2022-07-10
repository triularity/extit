/*
 * @(#) util/keymap.c
 *
 * Interface versioning ID map.
 *
 * Copyright (c) 2016-2017, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <iv/base.h>
#include <iv/util.h>

#define	DEFAULT_HASH_SIZE	29
#define	BUCKET_SIZE		10


typedef struct _bucket_entry
{
	unsigned char *		key;
	size_t			keylen;
	uint32_t		key_hashval;
	void *			value;
} bucket_entry_t;


typedef struct _bucket		bucket_t;

struct _bucket
{
	bucket_entry_t		entries[BUCKET_SIZE];
	size_t			count;
	bucket_t *		next;
};


struct _iv_keymap
{
	bucket_t **		buckets;
	uint32_t		hashsize;
	void			(*free_func)(void *);
};


/*
 * Compute a hash value for a byte array.
 */
static
uint32_t
calchash(const unsigned char *buf, size_t len)
{
	uint32_t	hv;


	hv = 0;

	while(len-- != 0)
	{
		hv = (hv << 1) ^ (hv >> 31) ^ *buf;
		buf++;
	}

	return hv ^ (uint32_t) len;
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
	const unsigned char *key,
	size_t keylen,
	uint32_t hashval,
	const unsigned char **internal_keyp
)
{
	bucket_t *		available;
	bucket_t *		bucket;
	size_t			count;
	size_t			idx;
	bucket_entry_t *	entry;


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

			if((entry->key_hashval == hashval)
			 && (entry->keylen == keylen)
			 && (memcmp(entry->key, key, keylen) == 0))
			{
				if(internal_keyp != NULL)
					*internal_keyp = entry->key;

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

	if((entry->key = malloc(keylen)) == NULL)
		return NULL;

	memcpy(entry->key, key, keylen);
	entry->keylen = keylen;

	entry->key_hashval = hashval;
	entry->value = NULL;

	available->count++;

	if(internal_keyp != NULL)
		*internal_keyp = entry->key;

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
				free(entry->key);

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

			free(entry->key);

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
	const unsigned char *key,
	size_t keylen,
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

			if((entry->key_hashval == hashval)
			 && (entry->keylen == keylen)
			 && (memcmp(entry->key, key, keylen) == 0))
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
	const unsigned char *key,
	size_t keylen,
	uint32_t hashval
)
{
	bucket_entry_t *	entry;


	if((entry = bucket_get(bucket, key, keylen, hashval)) == NULL)
		return NULL;

	return &entry->value;
}



iv_keymap_t *
IV_DECL
iv_keymap_create
(
	uint32_t hashsize,
	void (*free_func)(void *value)
)
{
	iv_keymap_t *	keymap;


	if(hashsize == 0)
		hashsize = DEFAULT_HASH_SIZE;

	if((keymap = calloc(
	 1, sizeof(iv_keymap_t) + (sizeof(bucket_t *) * hashsize))) != NULL)
	{
		keymap->buckets = (bucket_t **) &keymap[1];
		keymap->hashsize = hashsize;
		keymap->free_func = free_func;
	}

	return keymap;
}


void **
IV_DECL
iv_keymap_acquire_valueptr
(
	iv_keymap_t *keymap,
	const unsigned char *key,
	size_t keylen,
	const unsigned char **internal_keyp
)
{
	uint32_t	hashval;


	hashval = calchash(key, keylen);

	return bucket_acquire_valueptr(
		&keymap->buckets[hashval % keymap->hashsize],
		key,
		keylen,
		hashval,
		internal_keyp);
}


void
IV_DECL
iv_keymap_cleanup
(
	iv_keymap_t *keymap,
	void (*value_cleaner)(void **valueptr)
)
{
	size_t		i;


	for(i = 0; i < keymap->hashsize; i++)
		bucket_cleanup(&keymap->buckets[i], value_cleaner);
}


void
IV_DECL
iv_keymap_destroy
(
	iv_keymap_t *keymap
)
{
	size_t		i;
	bucket_t *	bucket;


	for(i = 0; i < keymap->hashsize; i++)
	{
		if((bucket = keymap->buckets[i]) != NULL)
			bucket_destroy(bucket, keymap->free_func);
	}
}


void *
IV_DECL
iv_keymap_get
(
	iv_keymap_t *keymap,
	const unsigned char *key,
	size_t keylen
)
{
	uint32_t		hashval;
	bucket_entry_t *	entry;


	hashval = calchash(key, keylen);

	entry = bucket_get(
		keymap->buckets[hashval % keymap->hashsize],
		key,
		keylen,
		hashval);

	if(entry == NULL)
		return NULL;

	return entry->value;
}


void **
IV_DECL
iv_keymap_get_valueptr
(
	iv_keymap_t *keymap,
	const unsigned char *key,
	size_t keylen
)
{
	uint32_t	hashval;


	hashval = calchash(key, keylen);

	return bucket_get_valueptr(
		keymap->buckets[hashval % keymap->hashsize],
		key,
		keylen,
		hashval);
}


const unsigned char *
IV_DECL
iv_keymap_intern_key
(
	iv_keymap_t *keymap,
	const unsigned char *key,
	size_t keylen
)
{
	uint32_t		hashval;
	bucket_entry_t *	entry;


	hashval = calchash(key, keylen);

	entry = bucket_get(
		keymap->buckets[hashval % keymap->hashsize],
		key,
		keylen,
		hashval);

	if(entry == NULL)
		return NULL;

	return entry->key;
}

/*
 * @(#) recipe.h
 *
 * This file is in the Public Domain.
 */

#ifndef	__recipe_h
#define	__recipe_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	RECIPE_INTERFACE_NAME		"recipe"
#define	RECIPE_INTERFACE_VERSION	IV_VERSION(1,0)

typedef struct _recipe
{
	const char *	name;
	unsigned int	prep_time;
	unsigned int	total_time;
	void 		(EXTIT_DECL *prepare)(void *ctx);
} recipe_t;

#ifdef	__cplusplus
}
#endif

#endif	/* !__recipe_h */

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

#define	RECIPE_INTERFACE_ID		"recipe"
#define	RECIPE_INTERFACE_VERSION	IV_VERSION(1,0)

typedef struct _recipe	recipe_t;

struct _recipe
{
	const char *	name;
	unsigned int	prep_time;
	unsigned int	total_time;

	/* Could be in a recipe_ops_t struct if there was man functions */
	void 		(EXTIT_DECL *prepare)(recipe_t *recipe);
};

#ifdef	__cplusplus
}
#endif

#endif	/* !__recipe_h */

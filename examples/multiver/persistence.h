/*
 * @(#) persistence.h
 *
 * A simple persistence manager interface.
 *
 * This file is in the Public Domain.
 */

#ifndef	__persistence_h
#define	__persistence_h

#include <iv/base.h>
#include <extit/base.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	PERSISTENCE_IID			"persistence"

#define	PERSISTENCE_ABI_1_0		IV_VERSION(1,0)
#define	PERSISTENCE_ABI_1_1		IV_VERSION(1,1)
#define	PERSISTENCE_ABI_1_2		IV_VERSION(1,2)


#ifndef	PERSISTENCE_ABI_TARGET
#define	PERSISTENCE_ABI_TARGET		PERSISTENCE_ABI_1_2
#endif

typedef enum
{
	PERSISTENCE_STATUS_SUCCESS = 0,		/* No error */
	PERSISTENCE_STATUS_FAILURE = 1,		/* General failure */
	PERSISTENCE_STATUS_INVALID = 2,		/* Invalid argument */
	PERSISTENCE_STATUS_TOOLONG = 3,		/* Value too long for buffer */
	PERSISTENCE_STATUS_NOTFOUND = 4,	/* Value not found */
	PERSISTENCE_STATUS_IOERROR = 5		/* I/O error */
} persistence_status_t;

typedef struct _persistence_ctx * 	persistence_ctx_t;


typedef struct _persistence
{
	/* v1.0 */
	persistence_ctx_t	(EXTIT_DECL *open_ctx)(const char *id);
	void			(EXTIT_DECL *close_ctx)(persistence_ctx_t ctx);

	persistence_status_t	(EXTIT_DECL *set_string)(
					persistence_ctx_t ctx,
					const char *name,
					const char *value);

	persistence_status_t	(EXTIT_DECL *get_string)(
					persistence_ctx_t ctx,
					const char *name,
					char *data,
					unsigned int maxlen);

#if	PERSISTENCE_ABI_TARGET >= PERSISTENCE_ABI_1_1
	/* v1.1 */
	persistence_status_t	(EXTIT_DECL *set_int)(
					persistence_ctx_t ctx,
					const char *name,
					int value);

	persistence_status_t	(EXTIT_DECL *set_double)(
					persistence_ctx_t ctx,
					const char *name,
					double value);

	int			(EXTIT_DECL *get_int)(
					persistence_ctx_t ctx,
					const char *name,
					int defValue);

	double			(EXTIT_DECL *get_double)(
					persistence_ctx_t ctx,
					const char *name,
					double defValue);

#if	PERSISTENCE_ABI_TARGET >= PERSISTENCE_ABI_1_2
	/* v1.2 */
	persistence_status_t	(EXTIT_DECL *set_binary)(
					persistence_ctx_t ctx,
					const char *name,
					const char *data,
					unsigned int length);

	int			(EXTIT_DECL *get_binary)(
					persistence_ctx_t ctx,
					const char *name,
					char *data,
					unsigned int maxlen);
#endif	/* PERSISTENCE_ABI_TARGET >= PERSISTENCE_ABI_1_2 */
#endif	/* PERSISTENCE_ABI_TARGET >= PERSISTENCE_ABI_1_1 */
} persistence_t;

#ifdef	__cplusplus
}
#endif

#endif	/* !__persistence_h */

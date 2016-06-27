/*
 * @(#) extit/plugin_spi.h
 *
 * Plugin SPI.
 *
 * Copyright (c) 2014-2016, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__extit__plugin_spi_h
#define	__extit__plugin_spi_h

#include <extit/base.h>
#include <extit/container.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Plugin SPI Commands
 */
typedef enum _extit_spi_command
{
	/*
	 * v1.0
	 */
	EXTIT_SPI_CMD_PROBE		= 1,
	EXTIT_SPI_CMD_CREATE		= 2,
	EXTIT_SPI_CMD_ACTIVATE		= 3,
	EXTIT_SPI_CMD_DEACTIVATE	= 4,
	EXTIT_SPI_CMD_DESTROY		= 5,
	EXTIT_SPI_CMD_PING		= 6,
	EXTIT_SPI_CMD_GET_INTERFACE	= 7,
	EXTIT_SPI_CMD_QUERY_INTERFACE	= 8,
	EXTIT_SPI_CMD_UNLOAD		= 9,

	EXTIT_SPI_CMD_CUSTOM_BASE	= 0x8000
} extit_spi_command_t;


/*
 * EXTIT_SPI_CMD_CREATE Parameter (v1.0)
 */
typedef struct _extit_spi_param_create_1_0
{
	void *				spi_ctx;		/* OUT */
} extit_spi_param_create_1_0_t;

/*
 * EXTIT_SPI_CMD_ACTIVATE Parameter (v1.0)
 */
typedef struct _extit_spi_param_activate_1_0
{
	void *				spi_ctx;		/* IN */
} extit_spi_param_activate_1_0_t;

/*
 * EXTIT_SPI_CMD_DEACTIVATE Parameter (v1.0)
 */
typedef struct _extit_spi_param_deactivate_1_0
{
	void *				spi_ctx;		/* IN */
} extit_spi_param_deactivate_1_0_t;

/*
 * EXTIT_SPI_CMD_DESTROY Parameter (v1.0)
 */
typedef struct _extit_spi_param_destroy_1_0
{
	void *				spi_ctx;		/* IN */
} extit_spi_param_destroy_1_0_t;

/*
 * EXTIT_SPI_CMD_PING Parameter (v1.0)
 */
typedef struct _extit_spi_param_ping_1_0
{
	void *				spi_ctx;		/* IN */
} extit_spi_param_ping_1_0_t;


/*
 * EXTIT_SPI_CMD_GET_INTERFACE Parameter (v1.0)
 */
typedef struct _extit_spi_param_get_interface_1_0
{
	void *				spi_ctx;		/* IN */
	const char *			id;			/* IN */
	iv_version_t			version;		/* IN */
	void *				interface_ptr;		/* OUT */
} extit_spi_param_get_interface_1_0_t;

/*
 * EXTIT_SPI_CMD_QUERY_INTERFACE Parameter (v1.0)
 */
typedef	struct _extit_spi_param_query_interface_1_0
{
	void *				spi_ctx;		/* IN */
	const char *			id;			/* IN */
	iv_version_t			base_version;		/* IN */
	iv_version_t			version;		/* OUT */
} extit_spi_param_query_interface_1_0_t;


/*
 * Plugin SPI Handler
 */
typedef extit_status_t	(EXTIT_DECL *extit_spi_handler_t)
				(
					iv_version_t		api_version,
					const extit_container_t *
								container,
					extit_spi_command_t	cmd,
					void *			param,
					unsigned int		flags
				);


/*
 * Magic Value for API Descriptor (aka "ExIt")
 */
#define	EXTIT_SPI_MAGIC		0x45784974L

/*
 * Plugin SPI Descriptor (base)
 */
typedef struct _extit_spi_descriptor_base
{
	unsigned int		magic;		/* EXTIT_SPI_MAGIC */
	iv_version_t		extit_version;	/* EXTIT_API_VERSION */
} extit_spi_descriptor_base_t;

/*
 * Plugin SPI Descriptor (v1.0)
 */
typedef struct _extit_spi_descriptor_1_0
{
	unsigned int		magic;		/* EXTIT_SPI_MAGIC */
	iv_version_t		extit_version;	/* EXTIT_API_VERSION */
	const char *		id;		/* Unique ID */
	unsigned int		id_version;	/* Unique ID Relative Version */
	const char *		name;
	const char *		version;
	extit_spi_handler_t	handler;
} extit_spi_descriptor_1_0_t;


/*
 * Aliases for API target
 */
#if	EXTIT_API_TARGET == EXTIT_API_VERSION_1_0
#define	extit_spi_param_create_t \
				extit_spi_param_create_1_0_t

#define	extit_spi_param_activate_t \
				extit_spi_param_activate_1_0_t

#define	extit_spi_param_deactivate_t \
				extit_spi_param_deactivate_1_0_t

#define	extit_spi_param_destroy_t \
				extit_spi_param_destroy_1_0_t

#define	extit_spi_param_ping_t	extit_spi_param_ping_1_0_t

#define	extit_spi_param_get_interface_t \
				extit_spi_param_get_interface_1_0_t

#define	extit_spi_param_query_interface_t \
				extit_spi_param_query_interface_1_0_t

#define	extit_spi_descriptor_t	extit_spi_descriptor_1_0_t
#else
#error	Unsupported API target
#endif


/*
 * Plugin SPI Descriptor Declaration
 */
#define	EXTIT_SPI_DESCRIPTOR_NAME	_extit_SPI_DESCRIPTOR
#define	EXTIT_SPI_DESCRIPTOR_SYMBOL	"_extit_SPI_DESCRIPTOR"

EXTIT_EXPORT
extern extit_spi_descriptor_t	_extit_SPI_DESCRIPTOR;

#define	EXTIT_DECLARE_SPI(uuid, uuid_version, name, version, handler) \
		EXTIT_EXPORT \
		extit_spi_descriptor_t EXTIT_SPI_DESCRIPTOR_NAME = \
		{ \
			EXTIT_SPI_MAGIC, \
			EXTIT_API_VERSION, \
			uuid, \
			uuid_version, \
			name, \
			version, \
			handler \
		}; \

#ifdef	__cplusplus
}
#endif

#endif	/* !__extit__plugin_spi_h */

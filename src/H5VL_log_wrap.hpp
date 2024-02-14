<<<<<<< HEAD
#pragma once

#include <H5VLpublic.h>
#include "H5VL_log_file.hpp"

/* The log VOL wrapper context */
/*
typedef struct H5VL_log_obj_t {
	void *uctx;	  // Under context
	hid_t uvlid;  // Under VolID
	H5VL_log_file_t *fp;
} H5VL_log_obj_t;
*/
=======
/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

#pragma once

#include <H5VLconnector.h>

#include "H5VL_log_file.hpp"

/* The log VOL wrapper context */
typedef struct H5VL_log_wrap_ctx_t {
    hid_t uvlid; /* VOL ID for under VOL */
    void *uo;    /* Object wrapping context for under VOL */
    H5VL_log_file_t *fp;
} H5VL_log_wrap_ctx_t;
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

extern void *H5VL_log_get_object (const void *obj);
extern herr_t H5VL_log_get_wrap_ctx (const void *obj, void **wrap_ctx);
extern void *H5VL_log_wrap_object (void *obj, H5I_type_t obj_type, void *_wrap_ctx);
extern void *H5VL_log_unwrap_object (void *obj);
extern herr_t H5VL_log_free_wrap_ctx (void *_wrap_ctx);
<<<<<<< HEAD


=======
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

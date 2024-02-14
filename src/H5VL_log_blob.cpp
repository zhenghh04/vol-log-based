<<<<<<< HEAD
=======
/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

<<<<<<< HEAD
#include "H5VL_logi.hpp"
#include "H5VL_log_blob.hpp"
#include "H5VL_log_obj.hpp"

const H5VL_blob_class_t H5VL_log_blob_g {
	H5VL_log_blob_put,		/* put       */
	H5VL_log_blob_get,		/* get         */
	H5VL_log_blob_specific, /* specific         */
	H5VL_log_blob_optional, /* optional         */
=======
#include "H5VL_log.h"
#include "H5VL_log_blob.hpp"
#include "H5VL_log_obj.hpp"
#include "H5VL_logi.hpp"

const H5VL_blob_class_t H5VL_log_blob_g {
    H5VL_log_blob_put,      /* put       */
    H5VL_log_blob_get,      /* get         */
    H5VL_log_blob_specific, /* specific         */
    H5VL_log_blob_optional, /* optional         */
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
};

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_blob_put
 *
 * Purpose:     Handles the blob 'put' callback
 *
 * Return:      SUCCEED / FAIL
 *
 *-------------------------------------------------------------------------
 */
herr_t H5VL_log_blob_put (void *obj, const void *buf, size_t size, void *blob_id, void *ctx) {
<<<<<<< HEAD
	H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
#ifdef LOGVOL_VERBOSE_DEBUG
	printf ("H5VL_log_blob_put(%p, %p, %llu, %p, %p)\n", obj, buf, size, blob_id, ctx);
#endif
	return H5VLblob_put (op->uo, op->uvlid, buf, size, blob_id, ctx);
=======
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
#ifdef LOGVOL_DEBUG
    if (H5VL_logi_debug_verbose ()) {
        printf ("H5VL_log_blob_put(%p, %p, %llu, %p, %p)\n", obj, buf,
                ((long long unsigned int)size), blob_id, ctx);
    }
#endif
    return H5VLblob_put (op->uo, op->uvlid, buf, size, blob_id, ctx);
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_blob_put() */

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_blob_get
 *
 * Purpose:     Handles the blob 'get' callback
 *
 * Return:      SUCCEED / FAIL
 *
 *-------------------------------------------------------------------------
 */
herr_t H5VL_log_blob_get (void *obj, const void *blob_id, void *buf, size_t size, void *ctx) {
<<<<<<< HEAD
	H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
#ifdef LOGVOL_VERBOSE_DEBUG
	printf ("H5VL_log_blob_get(%p, %p, %p, %llu, %p)\n", obj, blob_id, buf, size, ctx);
#endif
	return H5VLblob_get (op->uo, op->uvlid, blob_id, buf, size, ctx);
=======
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
#ifdef LOGVOL_DEBUG
    if (H5VL_logi_debug_verbose ()) {
        printf ("H5VL_log_blob_get(%p, %p, %p, %llu, %p)\n", obj, blob_id, buf,
                ((long long unsigned int)size), ctx);
    }
#endif
    return H5VLblob_get (op->uo, op->uvlid, blob_id, buf, size, ctx);
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_blob_get() */

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_blob_specific
 *
 * Purpose:     Handles the blob 'specific' callback
 *
 * Return:      SUCCEED / FAIL
 *
 *-------------------------------------------------------------------------
 */
<<<<<<< HEAD
herr_t H5VL_log_blob_specific (void *obj,
							   void *blob_id,
							   H5VL_blob_specific_t specific_type,
							   va_list arguments) {
	H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
#ifdef LOGVOL_VERBOSE_DEBUG
	char sname[32];
	switch (specific_type) {
		case H5VL_BLOB_DELETE:
			sprintf (sname, "H5VL_BLOB_DELETE");
			break;
		case H5VL_BLOB_GETSIZE:
			sprintf (sname, "H5VL_BLOB_GETSIZE");
			break;
		case H5VL_BLOB_ISNULL:
			sprintf (sname, "H5VL_BLOB_ISNULL");
			break;
		case H5VL_BLOB_SETNULL:
			sprintf (sname, "H5VL_BLOB_SETNULL");
			break;
	}
	printf ("H5VL_log_blob_specific(%p, %p, %s, ...)\n", obj, blob_id, sname);
#endif
	return H5VLblob_specific (op->uo, op->uvlid, blob_id, specific_type, arguments);
=======
herr_t H5VL_log_blob_specific (void *obj, void *blob_id, H5VL_blob_specific_args_t *args) {
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
#ifdef LOGVOL_DEBUG
    if (H5VL_logi_debug_verbose ()) {
        char sname[32];
        switch (args->op_type) {
            case H5VL_BLOB_DELETE:
                sprintf (sname, "H5VL_BLOB_DELETE");
                break;
            case H5VL_BLOB_ISNULL:
                sprintf (sname, "H5VL_BLOB_ISNULL");
                break;
            case H5VL_BLOB_SETNULL:
                sprintf (sname, "H5VL_BLOB_SETNULL");
                break;
        }
        printf ("H5VL_log_blob_specific(%p, %p, %s, ...)\n", obj, blob_id, sname);
    }
#endif
    return H5VLblob_specific (op->uo, op->uvlid, blob_id, args);
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_blob_specific() */

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_blob_optional
 *
 * Purpose:     Handles the blob 'optional' callback
 *
 * Return:      SUCCEED / FAIL
 *
 *-------------------------------------------------------------------------
 */
<<<<<<< HEAD
herr_t H5VL_log_blob_optional (void *obj,
							   void *blob_id,
							   H5VL_blob_optional_t opt_type,
							   va_list arguments) {
	H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
#ifdef LOGVOL_VERBOSE_DEBUG
	printf ("H5VL_log_blob_optional(%p, %p, %d, ...)\n", obj, blob_id, opt_type);
#endif
	return H5VLblob_optional (op->uo, op->uvlid, blob_id, opt_type, arguments);
} /* end H5VL_log_blob_optional() */
=======
herr_t H5VL_log_blob_optional (void *obj, void *blob_id, H5VL_optional_args_t *args) {
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
#ifdef LOGVOL_DEBUG
    if (H5VL_logi_debug_verbose ()) {
        printf ("H5VL_log_blob_optional(%p, %p, %d, ...)\n", obj, blob_id, args->op_type);
    }
#endif
    return H5VLblob_optional (op->uo, op->uvlid, blob_id, args);
} /* end H5VL_log_blob_optional() */
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

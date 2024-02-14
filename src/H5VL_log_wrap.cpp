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
#include "H5VL_log_wrap.hpp"
#include "H5VL_log_dataseti.hpp"
#include "H5VL_log_filei.hpp"
#include "H5VL_log_obj.hpp"
=======
#include "H5VL_log_dataseti.hpp"
#include "H5VL_log_filei.hpp"
#include "H5VL_log_obj.hpp"
#include "H5VL_log_wrap.hpp"
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
#include "H5VL_logi.hpp"

/********************* */
/* Function prototypes */
/********************* */
const H5VL_wrap_class_t H5VL_log_wrap_g {
<<<<<<< HEAD
	H5VL_log_get_object,	/* get */
	H5VL_log_get_wrap_ctx,	/* get ctx */
	H5VL_log_wrap_object,	/* wrap */
	H5VL_log_unwrap_object, /* unwrap */
	H5VL_log_free_wrap_ctx, /* free ctx */
=======
    H5VL_log_get_object,    /* get */
    H5VL_log_get_wrap_ctx,  /* get ctx */
    H5VL_log_wrap_object,   /* wrap */
    H5VL_log_unwrap_object, /* unwrap */
    H5VL_log_free_wrap_ctx, /* free ctx */
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
};

/*---------------------------------------------------------------------------
 * Function:    H5VL_log_get_object
 *
 * Purpose:     Retrieve the 'data' for a VOL object.
 *
 * Return:  Success:    0
 *      Failure:    -1
 *
 *---------------------------------------------------------------------------
 */
void *H5VL_log_get_object (const void *obj) {
<<<<<<< HEAD
	const H5VL_log_obj_t *op = (const H5VL_log_obj_t *)obj;
#ifdef LOGVOL_VERBOSE_DEBUG
	printf ("H5VL_log_get_object(%p)\n", obj);
#endif
	return H5VLget_object (op->uo, op->uvlid);
=======
    const H5VL_log_obj_t *op = (const H5VL_log_obj_t *)obj;

    try {
#ifdef LOGVOL_DEBUG
        if (H5VL_logi_debug_verbose ()) { printf ("H5VL_log_get_object(%p)\n", obj); }
#endif
        return H5VLget_object (op->uo, op->uvlid);
    }
    H5VL_LOGI_EXP_CATCH

err_out:;
    return NULL;
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_get_object() */

/*---------------------------------------------------------------------------
 * Function:    H5VL_log_get_wrap_ctx
 *
 * Purpose:     Retrieve a "wrapper context" for an object
 *
 * Return:  Success:    0
 *      Failure:    -1
 *
 *---------------------------------------------------------------------------
 */
herr_t H5VL_log_get_wrap_ctx (const void *obj, void **wrap_ctx) {
<<<<<<< HEAD
	herr_t err		   = 0;
	H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
	H5VL_log_obj_t *ctx;

#ifdef LOGVOL_VERBOSE_DEBUG
	printf ("H5VL_log_get_wrap_ctx(%p,%p)\n", obj, wrap_ctx);
#endif

	/* Allocate new VOL object wrapping context for the pass through connector */
	ctx = new H5VL_log_obj_t (op, H5I_NTYPES);
	CHECK_PTR (ctx)

	/* Increment reference count on underlying VOL ID, and copy the VOL info */
	err = H5VLget_wrap_ctx (op->uo, op->uvlid, &(ctx->uo));
	CHECK_ERR

	/* Set wrap context to return */
	*wrap_ctx = ctx;

err_out:;
	return err;
=======
    herr_t err         = 0;
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
    H5VL_log_wrap_ctx_t *ctx;

    try {
#ifdef LOGVOL_DEBUG
        if (H5VL_logi_debug_verbose ()) {
            printf ("H5VL_log_get_wrap_ctx(%p,%p)\n", obj, wrap_ctx);
        }
#endif

        /* Allocate new VOL object wrapping context for the pass through connector */
        ctx = new H5VL_log_wrap_ctx_t ();
        CHECK_PTR (ctx)

        /* Increment reference count on underlying VOL ID, and copy the VOL info */
        ctx->uvlid = op->uvlid;
        H5Iinc_ref (ctx->uvlid);
        ctx->fp = op->fp;
        err     = H5VLget_wrap_ctx (op->uo, op->uvlid, &(ctx->uo));
        CHECK_ERR

        /* Set wrap context to return */
        *wrap_ctx = ctx;
    }
    H5VL_LOGI_EXP_CATCH_ERR

err_out:;
    return err;
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

} /* end H5VL_log_get_wrap_ctx() */

/*---------------------------------------------------------------------------
 * Function:    H5VL_log_wrap_object
 *
 * Purpose:     Use a "wrapper context" to wrap a data object
 *
 * Return:      Success:    Pointer to wrapped object
 *              Failure:    NULL
 *
 *---------------------------------------------------------------------------
 */
void *H5VL_log_wrap_object (void *obj, H5I_type_t type, void *_wrap_ctx) {
<<<<<<< HEAD
	H5VL_log_obj_t *ctx = (H5VL_log_obj_t *)_wrap_ctx;
	H5VL_log_obj_t *wop = NULL;
	void *uo;

#ifdef LOGVOL_VERBOSE_DEBUG
	{
		char vname[128];
		ssize_t nsize;

		nsize = H5Iget_name (type, vname, 128);
		if (nsize == 0) {
			sprintf (vname, "Unnamed_Object");
		} else if (nsize < 0) {
			sprintf (vname, "Unknown_Object");
		}

		printf ("H5VL_log_wrap_object(%p, %s, %p)\n", obj, vname, _wrap_ctx);
	}
#endif

	/* Wrap the object with the underlying VOL */
	uo = H5VLwrap_object (obj, type, ctx->uvlid, ctx->uo);
	if (uo) {
		if (type == H5I_DATASET) {
			wop = (H5VL_log_obj_t *)H5VL_log_dataseti_wrap (uo, ctx);
		} else if (type == H5I_FILE) {
			wop = (H5VL_log_obj_t *)H5VL_log_filei_wrap (uo, ctx);
		}else {
			wop = new H5VL_log_obj_t (ctx, type, uo);
		}
	} else
		wop = NULL;

	return wop;
=======
    H5VL_log_wrap_ctx_t *ctx = (H5VL_log_wrap_ctx_t *)_wrap_ctx;
    H5VL_log_obj_t *wop      = NULL;
    void *uo;

    try {
#ifdef LOGVOL_DEBUG
        if (H5VL_logi_debug_verbose ()) {
            printf ("H5VL_log_wrap_object(%p, type, %p)\n", obj, _wrap_ctx);
        }
#endif

        /* Wrap the object with the underlying VOL */
        uo = H5VLwrap_object (obj, type, ctx->uvlid, ctx->uo);
        if (!ctx->fp->is_log_based_file) {
            wop = new H5VL_log_obj_t (ctx->fp, type, uo);
        } else if (uo) {
            if (type == H5I_DATASET) {
                wop = (H5VL_log_obj_t *)H5VL_log_dataseti_wrap (uo, ctx->fp);
            } else if (type == H5I_FILE) {
                wop                  = (H5VL_log_obj_t *)H5VL_log_filei_wrap (uo, ctx->fp);
                wop->fp->wrapped_obj = obj;
            } else {
                wop = new H5VL_log_obj_t (ctx->fp, type, uo);
            }
        } else
            wop = NULL;
    }
    H5VL_LOGI_EXP_CATCH

err_out:;
    return wop;
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_wrap_object() */

/*---------------------------------------------------------------------------
 * Function:    H5VL_log_wrap_object
 *
 * Purpose:     Use a "wrapper context" to wrap a data object
 *
 * Return:  Success:    0
 *      Failure:    -1
 *
 *---------------------------------------------------------------------------
 */
void *H5VL_log_unwrap_object (void *obj) {
<<<<<<< HEAD
	H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
	void *uo;

#ifdef LOGVOL_VERBOSE_DEBUG
	printf ("H5VL_log_unwrap_object(%p)\n", obj);
#endif

	/* Unrap the object with the underlying VOL */
	uo = H5VLunwrap_object (op->uo, op->uvlid);

	if (uo) {
		hid_t err_id;

		err_id = H5Eget_current_stack ();
		delete op;
		H5Eset_current_stack (err_id);
	}

	return uo;
=======
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
    void *uo           = NULL;

    try {
#ifdef LOGVOL_DEBUG
        if (H5VL_logi_debug_verbose ()) { printf ("H5VL_log_unwrap_object(%p)\n", obj); }
#endif
        if (!op->fp->is_log_based_file) {
            if (op->fp != op) {
                uo = H5VLunwrap_object (op->uo, op->uvlid);
                delete op;
            } else {
                uo = op->fp->wrapped_obj;
            }
        } else if (op->fp != op) {
            uo = H5VLunwrap_object (op->uo, op->uvlid);
            delete op;
        } else {
            uo = op->fp->wrapped_obj;
        }
    }
    H5VL_LOGI_EXP_CATCH

err_out:;
    return uo;
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_wrap_object() */

/*---------------------------------------------------------------------------
 * Function:    H5VL_log_free_wrap_ctx
 *
 * Purpose:     Release a "wrapper context" for an object
 *
 * Return:  Success:    0
 *      Failure:    -1
 *
 *---------------------------------------------------------------------------
 */
herr_t H5VL_log_free_wrap_ctx (void *_wrap_ctx) {
<<<<<<< HEAD
	herr_t err			= 0;
	H5VL_log_obj_t *ctx = (H5VL_log_obj_t *)_wrap_ctx;
	hid_t err_id;
#ifdef LOGVOL_VERBOSE_DEBUG
	printf ("H5VL_log_free_wrap_ctx(%p)\n", _wrap_ctx);
#endif
	err_id = H5Eget_current_stack ();

	/* Release underlying VOL ID and wrap context */
	if (ctx->uo) err = H5VLfree_wrap_ctx (ctx->uo, ctx->uvlid);
	CHECK_ERR

	H5Eset_current_stack (err_id);

	/* Free pass through wrap context object itself */
	delete ctx;

err_out:;
	return err;
=======
    herr_t err               = 0;
    H5VL_log_wrap_ctx_t *ctx = (H5VL_log_wrap_ctx_t *)_wrap_ctx;
    hid_t err_id;

    try {
#ifdef LOGVOL_DEBUG
        if (H5VL_logi_debug_verbose ()) { printf ("H5VL_log_free_wrap_ctx(%p)\n", _wrap_ctx); }
#endif
        err_id = H5Eget_current_stack ();

        /* Release underlying VOL ID and wrap context */
        if (ctx->uo) err = H5VLfree_wrap_ctx (ctx->uo, ctx->uvlid);
        CHECK_ERR
        H5Idec_ref (ctx->uvlid);

        H5Eset_current_stack (err_id);

        /* Free pass through wrap context object itself */
        delete ctx;
    }
    H5VL_LOGI_EXP_CATCH_ERR

err_out:;
    return err;
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_free_wrap_ctx() */

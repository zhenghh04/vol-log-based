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

#include <hdf5.h>

#include "H5VL_log_filei.hpp"
#include "H5VL_log_group.hpp"
#include "H5VL_log_obj.hpp"
#include "H5VL_log_req.hpp"
#include "H5VL_logi.hpp"
#include "H5VL_logi_err.hpp"
<<<<<<< HEAD
=======
#include "H5VL_logi_util.hpp"
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

/********************* */
/* Function prototypes */
/********************* */
const H5VL_group_class_t H5VL_log_group_g {
<<<<<<< HEAD
	H5VL_log_group_create,	 /* create       */
	H5VL_log_group_open,	 /* open       */
	H5VL_log_group_get,		 /* get          */
	H5VL_log_group_specific, /* specific     */
	H5VL_log_group_optional, /* optional     */
	H5VL_log_group_close	 /* close        */
=======
    H5VL_log_group_create,   /* create       */
    H5VL_log_group_open,     /* open       */
    H5VL_log_group_get,      /* get          */
    H5VL_log_group_specific, /* specific     */
    H5VL_log_group_optional, /* optional     */
    H5VL_log_group_close     /* close        */
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
};

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_group_create
 *
 * Purpose:     Creates a group inside a container
 *
 * Return:      Success:    Pointer to a group object
 *              Failure:    NULL
 *
 *-------------------------------------------------------------------------
 */
void *H5VL_log_group_create (void *obj,
<<<<<<< HEAD
							 const H5VL_loc_params_t *loc_params,
							 const char *name,
							 hid_t lcpl_id,
							 hid_t gcpl_id,
							 hid_t gapl_id,
							 hid_t dxpl_id,
							 void **req) {
	H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
	H5VL_log_obj_t *gp;
	H5VL_log_req_t *rp;
	void **ureqp, *ureq;
	H5VL_LOGI_PROFILING_TIMER_START;

	/* Check arguments */
	if (loc_params->type != H5VL_OBJECT_BY_SELF)
		ERR_OUT ("loc_params->type is not H5VL_OBJECT_BY_SELF")

	gp = new H5VL_log_obj_t (op, H5I_GROUP);

	if (req) {
		rp	  = new H5VL_log_req_t ();
		ureqp = &ureq;
	} else {
		ureqp = NULL;
	}

	H5VL_LOGI_PROFILING_TIMER_START;
	gp->uo = H5VLgroup_create (op->uo, loc_params, op->uvlid, name, lcpl_id, gcpl_id, gapl_id,
							   dxpl_id, ureqp);
	CHECK_PTR (gp->uo)
	H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VLGROUP_CREATE);

	if (req) {
		rp->append (ureq);
		*req = rp;
	}

	H5VL_LOGI_PROFILING_TIMER_STOP (gp->fp, TIMER_H5VL_LOG_GROUP_CREATE);

	return (void *)gp;

err_out:;
	delete gp;

	return NULL;
=======
                             const H5VL_loc_params_t *loc_params,
                             const char *name,
                             hid_t lcpl_id,
                             hid_t gcpl_id,
                             hid_t gapl_id,
                             hid_t dxpl_id,
                             void **req) {
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
    H5VL_log_obj_t *gp = NULL;
    H5VL_log_req_t *rp;
    void **ureqp, *ureq;
    char *iname = NULL;  // Internal name of object

    try {
        H5VL_LOGI_PROFILING_TIMER_START;

        /* Check arguments */
        if (op->fp->is_log_based_file) {
            if (loc_params->type != H5VL_OBJECT_BY_SELF)
                ERR_OUT ("loc_params->type is not H5VL_OBJECT_BY_SELF")
            /* Rename user objects to avoid conflict with internal object */
            iname = H5VL_logi_name_remap (name);
        } else {
            iname = (char *)name;
        }
        gp = new H5VL_log_obj_t (op, H5I_GROUP);

        if (req) {
            rp    = new H5VL_log_req_t ();
            ureqp = &ureq;
        } else {
            ureqp = NULL;
        }

        H5VL_LOGI_PROFILING_TIMER_START;
        gp->uo = H5VLgroup_create (op->uo, loc_params, op->uvlid, iname, lcpl_id, gcpl_id, gapl_id,
                                   dxpl_id, ureqp);
        CHECK_PTR (gp->uo)
        H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VLGROUP_CREATE);

        if (req) {
            rp->append (ureq);
            *req = rp;
        }

        H5VL_LOGI_PROFILING_TIMER_STOP (gp->fp, TIMER_H5VL_LOG_GROUP_CREATE);
    }
    H5VL_LOGI_EXP_CATCH

    if (iname && iname != name) { free (iname); }

    return (void *)gp;

err_out:;
    if (gp) { delete gp; }
    if (iname && iname != name) { free (iname); }

    return NULL;
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_group_create() */

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_group_open
 *
 * Purpose:     Opens a group inside a container
 *
 * Return:      Success:    Pointer to a group object
 *              Failure:    NULL
 *
 *-------------------------------------------------------------------------
 */
void *H5VL_log_group_open (void *obj,
<<<<<<< HEAD
						   const H5VL_loc_params_t *loc_params,
						   const char *name,
						   hid_t gapl_id,
						   hid_t dxpl_id,
						   void **req) {
	H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
	H5VL_log_obj_t *gp;
	H5VL_log_req_t *rp;
	void **ureqp, *ureq;
	H5VL_LOGI_PROFILING_TIMER_START;

	/* Check arguments */
	if (loc_params->type != H5VL_OBJECT_BY_SELF)
		ERR_OUT ("loc_params->type is not H5VL_OBJECT_BY_SELF")

	gp = new H5VL_log_obj_t (op, H5I_GROUP);

	if (req) {
		rp	  = new H5VL_log_req_t ();
		ureqp = &ureq;
	} else {
		ureqp = NULL;
	}

	H5VL_LOGI_PROFILING_TIMER_START;
	gp->uo = H5VLgroup_open (op->uo, loc_params, op->uvlid, name, gapl_id, dxpl_id, ureqp);
	CHECK_PTR (gp->uo)
	H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VLGROUP_OPEN);

	if (req) {
		rp->append (ureq);
		*req = rp;
	}

	H5VL_LOGI_PROFILING_TIMER_STOP (gp->fp, TIMER_H5VL_LOG_GROUP_OPEN);

	return (void *)gp;
err_out:;
	delete gp;
	return NULL;
=======
                           const H5VL_loc_params_t *loc_params,
                           const char *name,
                           hid_t gapl_id,
                           hid_t dxpl_id,
                           void **req) {
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
    H5VL_log_obj_t *gp = NULL;
    H5VL_log_req_t *rp;
    void **ureqp, *ureq;
    char *iname = NULL;  // Internal name of object

    try {
        H5VL_LOGI_PROFILING_TIMER_START;

        /* Check arguments */
        if (op->fp->is_log_based_file) {
            if (loc_params->type != H5VL_OBJECT_BY_SELF)
                ERR_OUT ("loc_params->type is not H5VL_OBJECT_BY_SELF")
            /* Rename user objects to avoid conflict with internal object */
            iname = H5VL_logi_name_remap (name);
        } else {
            iname = (char *)name;
        }

        gp = new H5VL_log_obj_t (op, H5I_GROUP);

        if (req) {
            rp    = new H5VL_log_req_t ();
            ureqp = &ureq;
        } else {
            ureqp = NULL;
        }

        H5VL_LOGI_PROFILING_TIMER_START;
        gp->uo = H5VLgroup_open (op->uo, loc_params, op->uvlid, iname, gapl_id, dxpl_id, ureqp);
        CHECK_PTR (gp->uo)
        H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VLGROUP_OPEN);

        if (req) {
            rp->append (ureq);
            *req = rp;
        }

        H5VL_LOGI_PROFILING_TIMER_STOP (gp->fp, TIMER_H5VL_LOG_GROUP_OPEN);
    }
    H5VL_LOGI_EXP_CATCH

    if (iname && iname != name) { free (iname); }

    return (void *)gp;

err_out:;
    if (gp) { delete gp; }
    if (iname && iname != name) { free (iname); }

    return NULL;
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_group_open() */

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_group_get
 *
 * Purpose:     Get info about a group
 *
 * Return:      Success:    0
 *              Failure:    -1
 *
 *-------------------------------------------------------------------------
 */
<<<<<<< HEAD
herr_t H5VL_log_group_get (
	void *obj, H5VL_group_get_t get_type, hid_t dxpl_id, void **req, va_list arguments) {
	H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
	herr_t err		   = 0;
	H5VL_log_req_t *rp;
	void **ureqp, *ureq;
	H5VL_LOGI_PROFILING_TIMER_START;

	if (req) {
		rp	  = new H5VL_log_req_t ();
		ureqp = &ureq;
	} else {
		ureqp = NULL;
	}

	H5VL_LOGI_PROFILING_TIMER_START;
	err = H5VLgroup_get (op->uo, op->uvlid, get_type, dxpl_id, ureqp, arguments);
	H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VLGROUP_GET);

	if (req) {
		rp->append (ureq);
		*req = rp;
	}

	H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VL_LOG_GROUP_GET);
	return err;
=======
herr_t H5VL_log_group_get (void *obj, H5VL_group_get_args_t *args, hid_t dxpl_id, void **req) {
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
    herr_t err         = 0;
    H5VL_log_req_t *rp;
    void **ureqp, *ureq;

    try {
        H5VL_LOGI_PROFILING_TIMER_START;

        if (req) {
            rp    = new H5VL_log_req_t ();
            ureqp = &ureq;
        } else {
            ureqp = NULL;
        }

        H5VL_LOGI_PROFILING_TIMER_START;
        err = H5VLgroup_get (op->uo, op->uvlid, args, dxpl_id, ureqp);
        H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VLGROUP_GET);

        if (req) {
            rp->append (ureq);
            *req = rp;
        }

        H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VL_LOG_GROUP_GET);
    }
    H5VL_LOGI_EXP_CATCH_ERR

err_out:;
    return err;
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_group_get() */

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_group_specific
 *
 * Purpose:     Specific operation on a group
 *
 * Return:      Success:    0
 *              Failure:    -1
 *
 *-------------------------------------------------------------------------
 */
<<<<<<< HEAD
herr_t H5VL_log_group_specific (
	void *obj, H5VL_group_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments) {
	herr_t err		   = 0;
	H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
	H5VL_log_req_t *rp;
	void **ureqp, *ureq;
	H5VL_LOGI_PROFILING_TIMER_START;

	if (req) {
		rp	  = new H5VL_log_req_t ();
		ureqp = &ureq;
	} else {
		ureqp = NULL;
	}

	H5VL_LOGI_PROFILING_TIMER_START;
	err = H5VLgroup_specific (op->uo, op->uvlid, specific_type, dxpl_id, ureqp, arguments);
	H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VLGROUP_SPECIFIC);

	if (req) {
		rp->append (ureq);
		*req = rp;
	}

	H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VL_LOG_GROUP_SPECIFIC);
	return err;
=======
herr_t H5VL_log_group_specific (void *obj,
                                H5VL_group_specific_args_t *args,
                                hid_t dxpl_id,
                                void **req) {
    herr_t err         = 0;
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
    H5VL_log_req_t *rp;
    void **ureqp, *ureq;

    try {
        H5VL_LOGI_PROFILING_TIMER_START;

        if (req) {
            rp    = new H5VL_log_req_t ();
            ureqp = &ureq;
        } else {
            ureqp = NULL;
        }

        H5VL_LOGI_PROFILING_TIMER_START;
        err = H5VLgroup_specific (op->uo, op->uvlid, args, dxpl_id, ureqp);
        H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VLGROUP_SPECIFIC);

        if (req) {
            rp->append (ureq);
            *req = rp;
        }

        H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VL_LOG_GROUP_SPECIFIC);
    }
    H5VL_LOGI_EXP_CATCH_ERR

err_out:;
    return err;
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_group_specific() */

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_group_optional
 *
 * Purpose:     Perform a connector-specific operation on a group
 *
 * Return:      Success:    0
 *              Failure:    -1
 *
 *-------------------------------------------------------------------------
 */
<<<<<<< HEAD
herr_t H5VL_log_group_optional (
	void *obj, H5VL_group_optional_t opt_type, hid_t dxpl_id, void **req, va_list arguments) {
	H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
	herr_t err		   = 0;
	H5VL_log_req_t *rp;
	void **ureqp, *ureq;
	H5VL_LOGI_PROFILING_TIMER_START;

	if (req) {
		rp	  = new H5VL_log_req_t ();
		ureqp = &ureq;
	} else {
		ureqp = NULL;
	}

	H5VL_LOGI_PROFILING_TIMER_START;
	err = H5VLgroup_optional (op->uo, op->uvlid, opt_type, dxpl_id, ureqp, arguments);
	H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VLGROUP_OPTIONAL);

	if (req) {
		rp->append (ureq);
		*req = rp;
	}

	H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VL_LOG_GROUP_OPTIONAL);
	return err;
=======
herr_t H5VL_log_group_optional (void *obj, H5VL_optional_args_t *args, hid_t dxpl_id, void **req) {
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
    herr_t err         = 0;
    H5VL_log_req_t *rp;
    void **ureqp, *ureq;

    try {
        H5VL_LOGI_PROFILING_TIMER_START;

        if (req) {
            rp    = new H5VL_log_req_t ();
            ureqp = &ureq;
        } else {
            ureqp = NULL;
        }

        H5VL_LOGI_PROFILING_TIMER_START;
        err = H5VLgroup_optional (op->uo, op->uvlid, args, dxpl_id, ureqp);
        H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VLGROUP_OPTIONAL);

        if (req) {
            rp->append (ureq);
            *req = rp;
        }

        H5VL_LOGI_PROFILING_TIMER_STOP (op->fp, TIMER_H5VL_LOG_GROUP_OPTIONAL);
    }
    H5VL_LOGI_EXP_CATCH_ERR

err_out:;
    return err;
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
} /* end H5VL_log_group_optional() */

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_group_close
 *
 * Purpose:     Closes a group.
 *
 * Return:      Success:    0
 *              Failure:    -1, group not closed.
 *
 *-------------------------------------------------------------------------
 */
herr_t H5VL_log_group_close (void *grp, hid_t dxpl_id, void **req) {
<<<<<<< HEAD
	H5VL_log_obj_t *gp = (H5VL_log_obj_t *)grp;
	herr_t err		   = 0;
	H5VL_log_req_t *rp;
	void **ureqp, *ureq;
	H5VL_LOGI_PROFILING_TIMER_START;

	if (req) {
		rp	  = new H5VL_log_req_t ();
		ureqp = &ureq;
	} else {
		ureqp = NULL;
	}

	H5VL_LOGI_PROFILING_TIMER_START;
	err = H5VLgroup_close (gp->uo, gp->uvlid, dxpl_id, ureqp);
	CHECK_ERR
	H5VL_LOGI_PROFILING_TIMER_STOP (gp->fp, TIMER_H5VLGROUP_CLOSE);

	if (req) {
		rp->append (ureq);
		*req = rp;
	}

	H5VL_LOGI_PROFILING_TIMER_STOP (gp->fp, TIMER_H5VL_LOG_GROUP_CLOSE);

	delete gp;

err_out:;
	return err;
} /* end H5VL_log_group_close() */
=======
    H5VL_log_obj_t *gp = (H5VL_log_obj_t *)grp;
    herr_t err         = 0;
    H5VL_log_req_t *rp;
    void **ureqp, *ureq;

    try {
        H5VL_LOGI_PROFILING_TIMER_START;

        if (req) {
            rp    = new H5VL_log_req_t ();
            ureqp = &ureq;
        } else {
            ureqp = NULL;
        }

        H5VL_LOGI_PROFILING_TIMER_START;
        err = H5VLgroup_close (gp->uo, gp->uvlid, dxpl_id, ureqp);
        CHECK_ERR
        H5VL_LOGI_PROFILING_TIMER_STOP (gp->fp, TIMER_H5VLGROUP_CLOSE);

        if (req) {
            rp->append (ureq);
            *req = rp;
        }

        H5VL_LOGI_PROFILING_TIMER_STOP (gp->fp, TIMER_H5VL_LOG_GROUP_CLOSE);

        delete gp;
    }
    H5VL_LOGI_EXP_CATCH_ERR

err_out:;
    return err;
} /* end H5VL_log_group_close() */
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

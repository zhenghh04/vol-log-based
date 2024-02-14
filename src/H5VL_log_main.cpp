<<<<<<< HEAD
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "H5VL_logi.hpp"
#include "H5VL_log.h"
#include "H5VL_log_main.hpp"
#include "H5VL_log_info.hpp"
#include "H5VL_logi.hpp"
#include <hdf5.h>

/*******************/
/* Local variables */
/*******************/

/* PNC VOL connector class struct */
const H5VL_class_t H5VL_log_g = {H5VL_log_VERSION,					 /* version      */
								 (H5VL_class_value_t)H5VL_log_VALUE, /* value        */
								 H5VL_log_NAME,						 /* name         */
								 0,									 /* capability flags */
								 H5VL_log_init,						 /* initialize   */
								 H5VL_log_obj_term,					 /* terminate    */
								 H5VL_log_info_g,
								 H5VL_log_wrap_g,
								 H5VL_log_attr_g,
								 H5VL_log_dataset_g,
								 H5VL_log_datatype_g,
								 H5VL_log_file_g,  /* file_cls */
								 H5VL_log_group_g, /* group_cls */
								 H5VL_log_link_g,
								 H5VL_log_object_g,
								 H5VL_log_introspect_g,
								 {
									 /* request_cls */
									 NULL, /* wait */
									 NULL, /* notify */
									 NULL, /* cancel */
									 NULL, /* specific */
									 NULL, /* optional */
									 NULL  /* free */
								 },
								 H5VL_log_blob_g,
								 H5VL_log_token_g,
								 H5VL_log_optional};

H5PL_type_t H5PLget_plugin_type (void) { return H5PL_TYPE_VOL; }
const void *H5PLget_plugin_info (void) { return &H5VL_log_g; }

int mpi_inited;

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_init
 *
 * Purpose:     Initialize this VOL connector, performing any necessary
 *      operations for the connector that will apply to all containers
 *              accessed with the connector.
 *
 * Return:  Success:    0
 *      Failure:    -1
 *
 *-------------------------------------------------------------------------
 */
herr_t H5VL_log_init (hid_t vipl_id) {
	herr_t err = 0;
	int mpierr;
	H5VL_log_req_type_t blocking = H5VL_LOG_REQ_BLOCKING;
	ssize_t infty				 = LOG_VOL_BSIZE_UNLIMITED;
	htri_t exist;

	mpierr = MPI_Initialized (&mpi_inited);
	CHECK_MPIERR
	if (!mpi_inited) { MPI_Init (NULL, NULL); }

	/* SID no longer recognized at this stage, move to file close
	if(H5VL_log_dataspace_contig==H5I_INVALID_HID){
		H5VL_log_dataspace_contig = H5Screate(H5S_SCALAR);
		CHECK_ID(H5VL_log_dataspace_contig);
	}
	*/

	/* Default pclass should not be changed, insert property to plist instead
	exist = H5Pexist (H5P_DATASET_XFER, "nonblocking");
	CHECK_ID (exist)
	if (!exist) {
		err = H5Pregister2 (H5P_DATASET_XFER, "nonblocking", sizeof (H5VL_log_req_type_t),
							&blocking, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		CHECK_ERR
	}

	exist = H5Pexist (H5P_FILE_ACCESS, "nb_buffer_size");
	CHECK_ID (exist)
	if (!exist) {
		err = H5Pregister2 (H5P_FILE_ACCESS, "nb_buffer_size", sizeof (ssize_t), &infty, NULL, NULL,
							NULL, NULL, NULL, NULL, NULL);
		CHECK_ERR
	}
	*/

err_out:;
	return err;
} /* end H5VL_log_init() */

/*---------------------------------------------------------------------------
 * Function:    H5VL_log_obj_term
 *
 * Purpose:     Terminate this VOL connector, performing any necessary
 *      operations for the connector that release connector-wide
 *      resources (usually created / initialized with the 'init'
 *      callback).
 *
 * Return:  Success:    0
 *      Failure:    (Can't fail)
 *
 *---------------------------------------------------------------------------
 */
herr_t H5VL_log_obj_term (void) {
	herr_t err = 0;
	int mpierr;

	/* SID no longer recognized at this stage, move to file close
	if(H5VL_log_dataspace_contig!=H5I_INVALID_HID){
		H5VL_log_dataspace_contig=H5I_INVALID_HID;
	}
	*/

	if (!mpi_inited) {
		mpierr = MPI_Initialized (&mpi_inited);
		CHECK_MPIERR
		if (mpi_inited) { MPI_Finalize (); }
	}

err_out:;
	return err;
} /* end H5VL_log_obj_term() */

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_optional
 *
 * Purpose:     Handles the generic 'optional' callback
 *
 * Return:      SUCCEED / FAIL
 *
 *-------------------------------------------------------------------------
 */
herr_t H5VL_log_optional (void *obj, int op_type, hid_t dxpl_id, void **req, va_list arguments) {
	H5VL_log_obj_t *o = (H5VL_log_obj_t *)obj;
	herr_t ret_value;

#ifdef LOGVOL_VERBOSE_DEBUG
	{
		char vname[128];
		ssize_t nsize;

		nsize = H5Iget_name (dxpl_id, vname, 128);
		if (nsize == 0) {
			sprintf (vname, "Unnamed_Object");
		} else if (nsize < 0) {
			sprintf (vname, "Unknown_Object");
		}
		printf ("H5VL_log_optional(%p,%d,%s,%p,...\n", obj, op_type, vname, req);
	}
#endif

	ret_value = H5VLoptional (o->uo, o->uvlid, op_type, dxpl_id, req, arguments);

	return ret_value;
} /* end H5VL_log_optional() */
=======
/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <hdf5.h>
#include <mpi.h>

#include "H5VL_log.h"
#include "H5VL_log_dataset.hpp"
#include "H5VL_log_info.hpp"
#include "H5VL_log_main.hpp"
#include "H5VL_logi.hpp"

/*******************/
/* Local variables */
/*******************/

/* PNC VOL connector class struct */
const H5VL_class_t H5VL_log_g = {H5VL_log_APIVER,                    /* version      */
                                 (H5VL_class_value_t)H5VL_log_REGID, /* value        */
                                 H5VL_log_NAME,                      /* name         */
                                 0,                 /* Version # of connector                   */
                                 0,                 /* capability flags */
                                 H5VL_log_init,     /* initialize   */
                                 H5VL_log_obj_term, /* terminate    */
                                 H5VL_log_info_g,
                                 H5VL_log_wrap_g,
                                 H5VL_log_attr_g,
                                 H5VL_log_dataset_g,
                                 H5VL_log_datatype_g,
                                 H5VL_log_file_g,  /* file_cls */
                                 H5VL_log_group_g, /* group_cls */
                                 H5VL_log_link_g,
                                 H5VL_log_object_g,
                                 H5VL_log_introspect_g,
                                 {
                                     /* request_cls */
                                     NULL, /* wait */
                                     NULL, /* notify */
                                     NULL, /* cancel */
                                     NULL, /* specific */
                                     NULL, /* optional */
                                     NULL  /* free */
                                 },
                                 H5VL_log_blob_g,
                                 H5VL_log_token_g,
                                 H5VL_log_optional};

H5PL_type_t H5PLget_plugin_type (void) { return H5PL_TYPE_VOL; }
const void *H5PLget_plugin_info (void) { return &H5VL_log_g; }

int mpi_inited;
bool h5dwriten_registered = false;

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_init
 *
 * Purpose:     Initialize this VOL connector, performing any necessary
 *      operations for the connector that will apply to all containers
 *              accessed with the connector.
 *
 * Return:  Success:    0
 *      Failure:    -1
 *
 *-------------------------------------------------------------------------
 */
herr_t H5VL_log_init (hid_t vipl_id) {
    herr_t err = 0;
    int mpierr;
    // H5VL_log_req_type_t blocking = false;
    // ssize_t infty = LOG_VOL_BSIZE_UNLIMITED;
    // htri_t exist;

    try {
        mpierr = MPI_Initialized (&mpi_inited);
        CHECK_MPIERR
        if (!mpi_inited) { MPI_Init (NULL, NULL); }

        // Register H5Dwrite_n and H5Dread_n
        if (!h5dwriten_registered) {
            err = H5VLregister_opt_operation (H5VL_SUBCLS_DATASET, "H5VL_log.H5Dwrite_n",
                                              &H5Dwrite_n_op_val);
            CHECK_ERR
            err = H5VLregister_opt_operation (H5VL_SUBCLS_DATASET, "H5VL_log.H5Dread_n",
                                              &H5Dread_n_op_val);
            CHECK_ERR
            h5dwriten_registered = true;
        }

        /* SID no longer recognized at this stage, move to file close
        if(H5VL_log_dataspace_contig==H5I_INVALID_HID){
                H5VL_log_dataspace_contig = H5Screate(H5S_SCALAR);
                CHECK_ID(H5VL_log_dataspace_contig);
        }
        */

        /* Default pclass should not be changed, insert property to plist instead
        exist = H5Pexist (H5P_DATASET_XFER, "nonblocking");
        CHECK_ID (exist)
        if (!exist) {
                err = H5Pregister2 (H5P_DATASET_XFER, "nonblocking", sizeof (H5VL_log_req_type_t),
                                                        &blocking, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL); CHECK_ERR
        }

        exist = H5Pexist (H5P_FILE_ACCESS, "nb_buffer_size");
        CHECK_ID (exist)
        if (!exist) {
                err = H5Pregister2 (H5P_FILE_ACCESS, "nb_buffer_size", sizeof (ssize_t), &infty,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL); CHECK_ERR
        }
        */
    }
    H5VL_LOGI_EXP_CATCH_ERR

err_out:;
    return err;
} /* end H5VL_log_init() */

/*---------------------------------------------------------------------------
 * Function:    H5VL_log_obj_term
 *
 * Purpose:     Terminate this VOL connector, performing any necessary
 *      operations for the connector that release connector-wide
 *      resources (usually created / initialized with the 'init'
 *      callback).
 *
 * Return:  Success:    0
 *      Failure:    (Can't fail)
 *
 *---------------------------------------------------------------------------
 */
herr_t H5VL_log_obj_term (void) {
    herr_t err = 0;
    int mpierr;

    try {
        /* SID no longer recognized at this stage, move to file close
        if(H5VL_log_dataspace_contig!=H5I_INVALID_HID){
                H5VL_log_dataspace_contig=H5I_INVALID_HID;
        }
        */

        // Unregister H5Dwrite_n and H5Dread_n
        if (h5dwriten_registered) {
            err = H5VLunregister_opt_operation (H5VL_SUBCLS_DATASET, "H5VL_log.H5Dwrite_n");
            CHECK_ERR
            // Unregister H5Dread_n
            err = H5VLunregister_opt_operation (H5VL_SUBCLS_DATASET, "H5VL_log.H5Dread_n");
            CHECK_ERR
            h5dwriten_registered = false;
        }

        if (!mpi_inited) {
            mpierr = MPI_Initialized (&mpi_inited);
            CHECK_MPIERR
            if (mpi_inited) { MPI_Finalize (); }
        }
    }
    H5VL_LOGI_EXP_CATCH_ERR

err_out:;
    return err;
} /* end H5VL_log_obj_term() */

/*-------------------------------------------------------------------------
 * Function:    H5VL_log_optional
 *
 * Purpose:     Handles the generic 'optional' callback
 *
 * Return:      SUCCEED / FAIL
 *
 *-------------------------------------------------------------------------
 */
herr_t H5VL_log_optional (void *obj, H5VL_optional_args_t *args, hid_t dxpl_id, void **req) {
    H5VL_log_obj_t *o = (H5VL_log_obj_t *)obj;
    herr_t ret_value;

#ifdef LOGVOL_DEBUG
    if (H5VL_logi_debug_verbose ()) {
        printf ("H5VL_log_optional(%p, %d, dxpl_id, %p,...\n", obj, args->op_type, req);
    }
#endif

    ret_value = H5VLoptional (o->uo, o->uvlid, args, dxpl_id, req);

    return ret_value;
} /* end H5VL_log_optional() */
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

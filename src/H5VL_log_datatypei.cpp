<<<<<<< HEAD
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "H5VL_log_datatype.hpp"
#include "H5VL_log_obj.hpp"
#include "H5VL_log_filei.hpp"
#include "H5VL_logi.hpp"

void *H5VL_log_datatype_open_with_uo (void *obj, void *uo, const H5VL_loc_params_t *loc_params) {
	H5VL_log_obj_t *op	 = (H5VL_log_obj_t *)obj;
	H5VL_log_obj_t *tp = NULL;

	/* Check arguments */
	// if(loc_params->type != H5VL_OBJECT_BY_SELF) ERR_OUT("loc_params->type is not
	// H5VL_OBJECT_BY_SELF")

	tp = new H5VL_log_obj_t (op,H5I_DATATYPE,uo);
	CHECK_PTR (tp);
	
	return (void *)tp;

err_out:;
	delete tp;

	return NULL;
} /* end H5VL_log_group_open() */
=======
/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
//
#include <memory>
//
#include "H5VL_log_datatype.hpp"
#include "H5VL_log_filei.hpp"
#include "H5VL_log_obj.hpp"
#include "H5VL_logi.hpp"

void *H5VL_log_datatype_open_with_uo (void *obj, void *uo, const H5VL_loc_params_t *loc_params) {
    H5VL_log_obj_t *op = (H5VL_log_obj_t *)obj;
    std::unique_ptr<H5VL_log_obj_t> tp;

    /* Check arguments */
    // if(loc_params->type != H5VL_OBJECT_BY_SELF) ERR_OUT("loc_params->type is not
    // H5VL_OBJECT_BY_SELF")

    tp = std::make_unique<H5VL_log_obj_t> (new H5VL_log_obj_t (op, H5I_DATATYPE, uo));
    CHECK_PTR (tp);

    return (void *)(tp.release ());
} /* end H5VL_log_group_open() */
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

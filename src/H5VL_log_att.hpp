<<<<<<< HEAD
=======
/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
#pragma once

#include <hdf5.h>
#include <mpi.h>

void *H5VL_log_attr_create (void *obj,
<<<<<<< HEAD
							const H5VL_loc_params_t *loc_params,
							const char *attr_name,
							hid_t type_id,
							hid_t space_id,
							hid_t acpl_id,
							hid_t aapl_id,
							hid_t dxpl_id,
							void **req);
void *H5VL_log_attr_open (void *obj,
						  const H5VL_loc_params_t *loc_params,
						  const char *attr_name,
						  hid_t aapl_id,
						  hid_t dxpl_id,
						  void **req);
herr_t H5VL_log_attr_read (void *attr, hid_t dtype_id, void *buf, hid_t dxpl_id, void **req);
herr_t H5VL_log_attr_write (void *attr, hid_t dtype_id, const void *buf, hid_t dxpl_id, void **req);
herr_t H5VL_log_attr_get (
	void *obj, H5VL_attr_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
herr_t H5VL_log_attr_specific (void *obj,
							   const H5VL_loc_params_t *loc_params,
							   H5VL_attr_specific_t specific_type,
							   hid_t dxpl_id,
							   void **req,
							   va_list arguments);
herr_t H5VL_log_attr_optional (
	void *obj, H5VL_attr_optional_t opt_type, hid_t dxpl_id, void **req, va_list arguments);
herr_t H5VL_log_attr_close (void *attr, hid_t dxpl_id, void **req);
=======
                            const H5VL_loc_params_t *loc_params,
                            const char *attr_name,
                            hid_t type_id,
                            hid_t space_id,
                            hid_t acpl_id,
                            hid_t aapl_id,
                            hid_t dxpl_id,
                            void **req);
void *H5VL_log_attr_open (void *obj,
                          const H5VL_loc_params_t *loc_params,
                          const char *attr_name,
                          hid_t aapl_id,
                          hid_t dxpl_id,
                          void **req);
herr_t H5VL_log_attr_read (void *attr, hid_t dtype_id, void *buf, hid_t dxpl_id, void **req);
herr_t H5VL_log_attr_write (void *attr, hid_t dtype_id, const void *buf, hid_t dxpl_id, void **req);
herr_t H5VL_log_attr_get (void *obj, H5VL_attr_get_args_t *args, hid_t dxpl_id, void **req);
herr_t H5VL_log_attr_specific (void *obj,
                               const H5VL_loc_params_t *loc_params,
                               H5VL_attr_specific_args_t *args,
                               hid_t dxpl_id,
                               void **req);
herr_t H5VL_log_attr_optional (void *obj, H5VL_optional_args_t *args, hid_t dxpl_id, void **req);
herr_t H5VL_log_attr_close (void *attr, hid_t dxpl_id, void **req);
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

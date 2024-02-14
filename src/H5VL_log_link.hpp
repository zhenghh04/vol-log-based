<<<<<<< HEAD
#pragma once

#include <H5VLpublic.h>

herr_t 
H5VL_log_link_create_reissue(H5VL_link_create_type_t create_type,
    void *obj, const H5VL_loc_params_t *loc_params, hid_t connector_id,
    hid_t lcpl_id, hid_t lapl_id, hid_t dxpl_id, void **req, ...);
herr_t 
H5VL_log_link_create(H5VL_link_create_type_t create_type, void *obj,
    const H5VL_loc_params_t *loc_params, hid_t lcpl_id, hid_t lapl_id,
    hid_t dxpl_id, void **req, va_list arguments);
herr_t 
H5VL_log_link_copy(void *src_obj, const H5VL_loc_params_t *loc_params1,
    void *dst_obj, const H5VL_loc_params_t *loc_params2, hid_t lcpl_id,
    hid_t lapl_id, hid_t dxpl_id, void **req);
herr_t 
H5VL_log_link_move(void *src_obj, const H5VL_loc_params_t *loc_params1,
    void *dst_obj, const H5VL_loc_params_t *loc_params2, hid_t lcpl_id,
    hid_t lapl_id, hid_t dxpl_id, void **req);
herr_t 
H5VL_log_link_get(void *obj, const H5VL_loc_params_t *loc_params,
    H5VL_link_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
herr_t 
H5VL_log_link_specific(void *obj, const H5VL_loc_params_t *loc_params, 
    H5VL_link_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments);
herr_t
H5VL_log_link_optional(void *obj, H5VL_link_optional_t opt_type, hid_t dxpl_id, void **req,
    va_list arguments);
=======
/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

#pragma once

#include <H5VLconnector.h>

herr_t H5VL_log_link_create_reissue (H5VL_link_create_args_t *args,
                                     void *obj,
                                     const H5VL_loc_params_t *loc_params,
                                     hid_t connector_id,
                                     hid_t lcpl_id,
                                     hid_t lapl_id,
                                     hid_t dxpl_id,
                                     void **req,
                                     ...);
herr_t H5VL_log_link_create (H5VL_link_create_args_t *args,
                             void *obj,
                             const H5VL_loc_params_t *loc_params,
                             hid_t lcpl_id,
                             hid_t lapl_id,
                             hid_t dxpl_id,
                             void **req);
herr_t H5VL_log_link_copy (void *src_obj,
                           const H5VL_loc_params_t *loc_params1,
                           void *dst_obj,
                           const H5VL_loc_params_t *loc_params2,
                           hid_t lcpl_id,
                           hid_t lapl_id,
                           hid_t dxpl_id,
                           void **req);
herr_t H5VL_log_link_move (void *src_obj,
                           const H5VL_loc_params_t *loc_params1,
                           void *dst_obj,
                           const H5VL_loc_params_t *loc_params2,
                           hid_t lcpl_id,
                           hid_t lapl_id,
                           hid_t dxpl_id,
                           void **req);
herr_t H5VL_log_link_get (void *obj,
                          const H5VL_loc_params_t *loc_params,
                          H5VL_link_get_args_t *args,
                          hid_t dxpl_id,
                          void **req);
herr_t H5VL_log_link_specific (void *obj,
                               const H5VL_loc_params_t *loc_params,
                               H5VL_link_specific_args_t *args,
                               hid_t dxpl_id,
                               void **req);
herr_t H5VL_log_link_optional (void *obj,
                               const H5VL_loc_params_t *loc_params,
                               H5VL_optional_args_t *args,
                               hid_t dxpl_id,
                               void **req);
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

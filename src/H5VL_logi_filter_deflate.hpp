<<<<<<< HEAD
#include <H5VLpublic.h>

#include "H5VL_logi_filter.hpp"

herr_t H5VL_logi_filter_deflate (H5VL_log_filter_t &fp, void *in, int in_len, void *out, int *out_len) ;
herr_t H5VL_logi_filter_deflate_alloc (H5VL_log_filter_t &fp, void *in, int in_len, void **out, int *out_len) ;
herr_t H5VL_logi_filter_inflate (H5VL_log_filter_t &fp, void *in, int in_len, void *out, int *out_len);
herr_t H5VL_logi_filter_inflate_alloc (H5VL_log_filter_t &fp, void *in, int in_len, void **out, int *out_len) ;
=======
/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

#include <H5VLconnector.h>

#include "H5VL_logi_filter.hpp"

void H5VL_logi_filter_deflate (
    H5VL_log_filter_t &fp, void *in, int in_len, void *out, int *out_len);
void H5VL_logi_filter_deflate_alloc (
    H5VL_log_filter_t &fp, void *in, int in_len, void **out, int *out_len);
void H5VL_logi_filter_inflate (
    H5VL_log_filter_t &fp, void *in, int in_len, void *out, int *out_len);
void H5VL_logi_filter_inflate_alloc (
    H5VL_log_filter_t &fp, void *in, int in_len, void **out, int *out_len);
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

<<<<<<< HEAD
=======
/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
#pragma once

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

<<<<<<< HEAD
#include <H5VLpublic.h>

#ifdef ENABLE_ZLIB
herr_t H5VL_log_zip_compress(void *in, int in_len, void *out, int *out_len);
herr_t H5VL_log_zip_compress_alloc(void *in, int in_len, void **out, int *out_len);
herr_t H5VL_log_zip_decompress(void *in, int in_len, void *out, int *out_len);
herr_t H5VL_log_zip_decompress_alloc(void *in, int in_len, void **out, int *out_len);
#endif
=======
#include <H5VLconnector.h>

#ifdef ENABLE_ZLIB
bool H5VL_log_zip_compress (void *in, int in_len, void *out, int *out_len);
void H5VL_log_zip_compress_alloc (void *in, int in_len, void **out, int *out_len);
bool H5VL_log_zip_decompress (void *in, int in_len, void *out, int *out_len);
void H5VL_log_zip_decompress_alloc (void *in, int in_len, void **out, int *out_len);
#endif
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

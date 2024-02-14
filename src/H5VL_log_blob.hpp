<<<<<<< HEAD
#pragma once

#include <H5VLpublic.h>
=======
/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

#pragma once

#include <H5VLconnector.h>
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

/* Blob callbacks */
static herr_t H5VL_log_blob_put (void *obj, const void *buf, size_t size, void *blob_id, void *ctx);
static herr_t H5VL_log_blob_get (void *obj, const void *blob_id, void *buf, size_t size, void *ctx);
<<<<<<< HEAD
static herr_t H5VL_log_blob_specific (void *obj,
									  void *blob_id,
									  H5VL_blob_specific_t specific_type,
									  va_list arguments);
static herr_t H5VL_log_blob_optional (void *obj,
									  void *blob_id,
									  H5VL_blob_optional_t opt_type,
									  va_list arguments);
=======
static herr_t H5VL_log_blob_specific (void *obj, void *blob_id, H5VL_blob_specific_args_t *args);
static herr_t H5VL_log_blob_optional (void *obj, void *blob_id, H5VL_optional_args_t *args);
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

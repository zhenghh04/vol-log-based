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
#include "H5VL_logi_mem.hpp"
#include "H5VL_logi_debug.hpp"
#include "H5VL_logi_profiling.hpp"
#include "H5VL_logi_err.hpp"
=======
#include "H5VL_logi_debug.hpp"
#include "H5VL_logi_err.hpp"
#include "H5VL_logi_mem.hpp"
#ifndef REPLAY_BUILD
#include "H5VL_logi_profiling.hpp"
#endif
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

// APIs
extern const H5VL_dataset_class_t H5VL_log_dataset_g;
extern const H5VL_attr_class_t H5VL_log_attr_g;
extern const H5VL_file_class_t H5VL_log_file_g;
extern const H5VL_info_class_t H5VL_log_info_g;
extern const H5VL_group_class_t H5VL_log_group_g;
extern const H5VL_introspect_class_t H5VL_log_introspect_g;
extern const H5VL_object_class_t H5VL_log_object_g;
extern const H5VL_datatype_class_t H5VL_log_datatype_g;
extern const H5VL_blob_class_t H5VL_log_blob_g;
extern const H5VL_link_class_t H5VL_log_link_g;
extern const H5VL_token_class_t H5VL_log_token_g;
extern const H5VL_wrap_class_t H5VL_log_wrap_g;

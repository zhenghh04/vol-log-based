<<<<<<< HEAD
#pragma once

#include <H5VLpublic.h>

typedef struct H5VL_log_info_t {
    hid_t uvlid;         /* VOL ID for under VOL */
    void *under_vol_info;       /* VOL info for under VOL */
} H5VL_log_info_t;
=======
/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

#pragma once

#include <H5VLconnector.h>

#include "H5VL_log.h"
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

extern void *H5VL_log_info_copy (const void *_info);
extern herr_t H5VL_log_info_cmp (int *cmp_value, const void *_info1, const void *_info2);
extern herr_t H5VL_log_info_free (void *_info);
extern herr_t H5VL_log_info_to_str (const void *_info, char **str);
<<<<<<< HEAD
extern herr_t H5VL_log_str_to_info (const char *str, void **_info);
=======
extern herr_t H5VL_log_str_to_info (const char *str, void **_info);
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

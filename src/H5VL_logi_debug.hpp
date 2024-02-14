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
#include <mpi.h>
#include <cstdio>
#include <H5VLpublic.h>

#ifdef LOGVOL_DEBUG
extern int H5VL_log_debug_MPI_Type_create_subarray (int ndims,
													const int array_of_sizes[],
													const int array_of_subsizes[],
													const int array_of_starts[],
													int order,
													MPI_Datatype oldtype,
													MPI_Datatype *newtype);
=======
#include <H5VLconnector.h>
#include <mpi.h>

#include <cstdio>

#ifdef LOGVOL_DEBUG
extern int H5VL_log_debug_MPI_Type_create_subarray (int ndims,
                                                    const int array_of_sizes[],
                                                    const int array_of_subsizes[],
                                                    const int array_of_starts[],
                                                    int order,
                                                    MPI_Datatype oldtype,
                                                    MPI_Datatype *newtype);
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
extern void hexDump (char *desc, void *addr, size_t len, char *fname);
extern void hexDump (char *desc, void *addr, size_t len);
extern void hexDump (char *desc, void *addr, size_t len, FILE *fp);
extern int H5VL_logi_inc_ref (hid_t);
extern int H5VL_logi_dec_ref (hid_t);
#else
#define H5VL_log_debug_MPI_Type_create_subarray MPI_Type_create_subarray
<<<<<<< HEAD
#define H5VL_logi_inc_ref						H5Iinc_ref
#define H5VL_logi_dec_ref						H5Idec_ref
=======
#define H5VL_logi_inc_ref                       H5Iinc_ref
#define H5VL_logi_dec_ref                       H5Idec_ref
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
#endif

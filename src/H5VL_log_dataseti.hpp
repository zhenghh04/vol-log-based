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
#include <mpi.h>

#include "H5VL_log_obj.hpp"
#include "H5VL_log_wrap.hpp"
#include "H5VL_logi_idx.hpp"

<<<<<<< HEAD

typedef struct H5VL_log_copy_ctx {
	char *src;
	char *dst;
	size_t size;
} H5VL_log_copy_ctx;

void *H5VL_log_dataseti_open_with_uo (void *obj,
									 void *uo,
									 const H5VL_loc_params_t *loc_params,
									 hid_t dxpl_id);
void *H5VL_log_dataseti_wrap (void *uo, H5VL_log_obj_t *cp);
herr_t H5VL_log_dataset_readi_gen_rtypes (std::vector<H5VL_log_search_ret_t> blocks,
												 MPI_Datatype *ftype,
												 MPI_Datatype *mtype,
												 std::vector<H5VL_log_copy_ctx> &overlaps);
/*
herr_t H5VL_log_dataseti_writen (hid_t did,
				  hid_t mem_type_id,
				  int n,
				  MPI_Offset **starts,
				  MPI_Offset **counts,
				  hid_t dxplid,
				  void *buf);
				*/
=======
#define H5VL_LOG_DATASETI_ATTR_DIMS  "_dims"
#define H5VL_LOG_DATASETI_ATTR_MDIMS "_mdims"
#define H5VL_LOG_DATASETI_ATTR_ID    "_ID"

typedef struct H5VL_log_dio_n_arg_t {
    hid_t mem_type_id;
    int n;
    hsize_t **starts;
    hsize_t **counts;
    void *buf;
} H5VL_log_dio_n_arg_t;

typedef struct H5VL_log_copy_ctx {
    char *src;    // Copy from
    char *dst;    // Copy to
    size_t size;  // Size in byte to copy
} H5VL_log_copy_ctx;

void *H5VL_log_dataseti_open (void *obj, void *uo, hid_t dxpl_id);
void *H5VL_log_dataseti_wrap (void *uo, H5VL_log_obj_t *cp);
void H5VL_log_dataset_readi_gen_rtypes (std::vector<H5VL_log_idx_search_ret_t> &blocks,
                                        MPI_Datatype *ftype,
                                        MPI_Datatype *mtype,
                                        std::vector<H5VL_log_copy_ctx> &overlaps);
void H5VL_log_dataseti_write (H5VL_log_dset_t *dp,
                              hid_t mem_type_id,
                              hid_t mem_space_id,
                              H5VL_log_selections *dsel,
                              hid_t plist_id,
                              const void *buf,
                              void **req);
void H5VL_log_dataseti_read (H5VL_log_dset_t *dp,
                             hid_t mem_type_id,
                             hid_t mem_space_id,
                             H5VL_log_selections *dsel,
                             hid_t plist_id,
                             void *buf,
                             void **req);

void H5VL_log_dataset_readi_passthru (std::vector<H5VL_log_idx_search_ret_t> &blocks,
                                      std::vector<H5VL_log_copy_ctx> &overlaps,
                                      H5VL_log_file_t *fp);
/*
herr_t H5VL_log_dataseti_writen (hid_t did,
                                  hid_t mem_type_id,
                                  int n,
                                  MPI_Offset **starts,
                                  MPI_Offset **counts,
                                  hid_t dxplid,
                                  void *buf);
                                */
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

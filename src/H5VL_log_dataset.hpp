#pragma once

#include <H5VLpublic.h>
#include <mpi.h>

#include "H5VL_log_obj.hpp"
#include "H5VL_log_wrap.hpp"


#define LOGVOL_SELCTION_TYPE_HYPERSLABS 0x01
#define LOGVOL_SELCTION_TYPE_POINTS 0x02
#define LOGVOL_SELCTION_TYPE_OFFSETS 0x04

/* The log VOL dataset object */
typedef struct H5VL_log_dset_t : H5VL_log_obj_t {
	int id;
	hsize_t ndim;
	hsize_t dims[H5S_MAX_RANK];
	hsize_t mdims[H5S_MAX_RANK];
	//hsize_t dsteps[H5S_MAX_RANK];

	hid_t dtype;
	hsize_t esize;

	using H5VL_log_obj_t::H5VL_log_obj_t;
} H5VL_log_dset_t;

void *H5VL_log_dataset_create (void *obj,
							   const H5VL_loc_params_t *loc_params,
							   const char *name,
							   hid_t lcpl_id,
							   hid_t type_id,
							   hid_t space_id,
							   hid_t dcpl_id,
							   hid_t dapl_id,
							   hid_t dxpl_id,
							   void **req);
void *H5VL_log_dataset_open (void *obj,
							 const H5VL_loc_params_t *loc_params,
							 const char *name,
							 hid_t dapl_id,
							 hid_t dxpl_id,
							 void **req);
herr_t H5VL_log_dataset_read (void *dset,
							  hid_t mem_type_id,
							  hid_t mem_space_id,
							  hid_t file_space_id,
							  hid_t plist_id,
							  void *buf,
							  void **req);
herr_t H5VL_log_dataset_write (void *dset,
							   hid_t mem_type_id,
							   hid_t mem_space_id,
							   hid_t file_space_id,
							   hid_t plist_id,
							   const void *buf,
							   void **req);
herr_t H5VL_log_dataset_get (
	void *dset, H5VL_dataset_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
herr_t H5VL_log_dataset_specific (
	void *obj, H5VL_dataset_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments);
herr_t H5VL_log_dataset_optional (
	void *obj, H5VL_dataset_optional_t optional_type, hid_t dxpl_id, void **req, va_list arguments);
herr_t H5VL_log_dataset_close (void *dset, hid_t dxpl_id, void **req);
#pragma once

#include <H5VLpublic.h>
#include <mpi.h>
#include <vector>

#include "H5VL_logi_dataspace.hpp"

#define H5VL_LOGI_META_FLAG_MUL_SEL 0x01
#define H5VL_LOGI_META_FLAG_MUL_SELX 0x02
#define H5VL_LOGI_META_FLAG_SEL_ENCODE 0x04
#define H5VL_LOGI_META_FLAG_SEL_DEFLATE 0x08

typedef struct H5VL_logi_meta_hdr {
	int meta_size;	// Size of the metadata entry
	int did;	// Target dataset ID
	int flag;	
} H5VL_logi_meta_hdr;

typedef struct H5VL_log_wreq_t {
	H5VL_logi_meta_hdr hdr;
	//int ndim;  // Dim of the target dataset
	// MPI_Offset start[H5S_MAX_RANK];
	// MPI_Offset count[H5S_MAX_RANK];
	//int flag;
	//std::vector<H5VL_log_selection> sels;  // Selections within the dataset

	//H5VL_logi_meta_hdr *meta_hdr;
	char *meta_buf;
	int nsel;
	//size_t meta_size;

	int ldid;		   // Log dataset ID
	MPI_Offset ldoff;  // Offset in log dataset

	size_t rsize;  // Size of data in xbuf (bytes)
	char *xbuf;	   // I/O buffer, always continguous and the same format as the dataset
	char *ubuf;	   // User buffer
				   // int buf_alloc;  // Whether the buffer is allocated or
} H5VL_log_wreq_t;

typedef struct H5VL_log_rreq_t {
	H5VL_logi_meta_hdr hdr;
	//int did;							   // Source dataset ID
	int ndim;							   // Dim of the source dataset
	std::vector<H5VL_log_selection> sels;  // Selections within the dataset
	// MPI_Offset start[H5S_MAX_RANK];
	// MPI_Offset count[H5S_MAX_RANK];

	hid_t dtype;  // Dataset type
	hid_t mtype;  // Memory type

	size_t rsize;  // Number of data elements in xbuf
	size_t esize;  // Size of a data element in xbuf

	char *ubuf;	 // I/O buffer, always continguous and the same format as the dataset
	char *xbuf;	 // User buffer

	MPI_Datatype ptype;	 // Datatype that represetn memory space selection
} H5VL_log_rreq_t;

herr_t H5VL_log_nb_flush_read_reqs (void *file,
										   std::vector<H5VL_log_rreq_t> reqs,
										   hid_t dxplid);
herr_t H5VL_log_nb_flush_write_reqs (void *file, hid_t dxplid);
herr_t H5VL_log_nb_ost_write (void *file, off64_t doff, off64_t off, int cnt, int *mlens, off64_t *moffs);
herr_t H5VL_log_nb_flush_write_reqs_align (void *file, hid_t dxplid);
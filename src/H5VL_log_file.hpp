#pragma once

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <array>
#include <string>
#include "H5VL_log_obj.hpp"
#include "H5VL_log.h"
#include "H5VL_logi.hpp"
#include "H5VL_logi_idx.hpp"
#include "H5VL_logi_nb.hpp"
#include "H5VL_logi_profiling.hpp"

#define LOG_GROUP_NAME "_LOG"

typedef struct H5VL_log_contig_buffer_t {
	char *begin, *end;
	char *cur;
} H5VL_log_contig_buffer_t;

typedef struct H5VL_log_cord_t {
	MPI_Offset cord[H5S_MAX_RANK];
} H5VL_log_cord_t;

/* The log VOL file object */
typedef struct H5VL_log_file_t : H5VL_log_obj_t {
	int rank;
	int np;
	MPI_Comm comm;

	/* Aligned data layout */
	int nnode;
	int nodeid;
	int noderank;
	int prev_rank;
	int next_rank;
	int target_ost;
	size_t ssize;
	int scount;
	MPI_Comm nodecomm;

	int refcnt;
	bool closing;
	unsigned flag;

	hid_t dxplid;

	void *lgp;
	int ndset;
	int nldset;
	int nmdset;

	MPI_File fh;
	int fd;

	std::vector<H5VL_log_wreq_t> wreqs;
	int nflushed;
	std::vector<H5VL_log_rreq_t> rreqs;

	// Should we do metadata caching?
	std::vector<int> ndim;
	std::vector<std::array<hsize_t, H5S_MAX_RANK>> dsizes;
	// std::vector<H5VL_log_dset_meta_t> mdc;

	ssize_t bsize;
	size_t bused;

	std::string name;

	// H5VL_log_buffer_pool_t data_buf;
	H5VL_log_contig_buffer_t meta_buf;

	// std::vector<int> lut;
	std::vector<std::vector<H5VL_log_metaentry_t>> idx;
	bool idxvalid;
	bool metadirty;

	// Configuration flag
	int config;

#ifdef LOGVOL_PROFILING
//#pragma message ( "C Preprocessor got here!" )
	double tlocal[H5VL_LOG_NTIMER];
	double clocal[H5VL_LOG_NTIMER];
#endif

	H5VL_log_file_t ();
	H5VL_log_file_t (hid_t uvlid);
	H5VL_log_file_t (void *uo, hid_t uvlid);
	//~H5VL_log_file_t ();
} H5VL_log_file_t;

typedef struct H5VL_log_buffer_block_t {
	char *begin, *end;
	char *cur;
	H5VL_log_buffer_block_t *next;
} H5VL_log_buffer_block_t;

typedef struct H5VL_log_buffer_pool_t {
	ssize_t bsize;
	int inf;
	H5VL_log_buffer_block_t *head;
	H5VL_log_buffer_block_t *free_blocks;
} H5VL_log_buffer_pool_t;

typedef struct H5VL_log_dset_meta_t {
	// H5VL_log_file_t *fp;
	// int id;
	hsize_t ndim;
	// hsize_t dims[H5S_MAX_RANK];
	// hsize_t mdims[H5S_MAX_RANK];
	hid_t dtype;
	// hsize_t esize;
} H5VL_log_dset_meta_t;

void *H5VL_log_file_create (
	const char *name, unsigned flags, hid_t fcpl_id, hid_t fapl_id, hid_t dxpl_id, void **req);
void *H5VL_log_file_open (
	const char *name, unsigned flags, hid_t fapl_id, hid_t dxpl_id, void **req);
herr_t H5VL_log_file_get (
	void *file, H5VL_file_get_t get_type, hid_t dxpl_id, void **req, va_list arguments);
herr_t H5VL_log_file_specific (
	void *file, H5VL_file_specific_t specific_type, hid_t dxpl_id, void **req, va_list arguments);
herr_t H5VL_log_file_optional (
	void *file, H5VL_file_optional_t opt_type, hid_t dxpl_id, void **req, va_list arguments);
herr_t H5VL_log_file_close (void *file, hid_t dxpl_id, void **req);
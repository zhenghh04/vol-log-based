<<<<<<< HEAD
=======
/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <mpi.h>

#include <array>
<<<<<<< HEAD
#include <cstdlib>
#include <cstring>
=======
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <map>
#include <unordered_map>
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a
#include <vector>

#include "H5VL_log_file.hpp"
#include "H5VL_log_filei.hpp"
#include "H5VL_logi.hpp"
#include "H5VL_logi_err.hpp"
<<<<<<< HEAD
#include "H5VL_logi_wrapper.hpp"
#include "H5VL_logi_zip.hpp"

herr_t H5VL_log_filei_metaflush (H5VL_log_file_t *fp) {
	herr_t err = 0;
	int mpierr;
	int i, j;
	int *cnt, *flag;	   // Number of entry to merge per dataset; flag of merged entry per dataset
	int merge_threshould;  // A trick to merge entry with 1 selection
	MPI_Offset *mlens = NULL;  // metadata size of merged entry per dataset
	MPI_Offset *moffs = NULL;  // metadata offset in memory of merged entry per dataset
	MPI_Offset doff;		   // Local metadata offset within the metadata dataset
	MPI_Offset mdsize_all;	   // Global metadata size
	MPI_Offset mdsize = 0;	   // Local metadata size
	MPI_Aint *offs	  = NULL;  // Offset in MPI_Type_hindexed
	int *lens		  = NULL;  // Lens in MPI_Type_hindexed
	int nentry		  = 0;	   // Number of metadata entries
	size_t bsize	  = 0;	   // Size of metadata buffer = size of metadata before compression
	size_t esize;			   // Size of the current processing metadata entry
#ifdef ENABLE_ZLIB
	MPI_Offset zbsize = 0;	// Size of zbuf
	char *zbuf;				// Buffer to temporarily sotre compressed data
#endif
	char *buf	= NULL;				// Buffer to store merged entries
	char **bufp = NULL;				// Point to merged entry per dataset in buf
	char mdname[32];				// Name of metadata dataset
	int clen, inlen;				// Compressed size; Size of data to be compressed
	void *mdp;						// under VOL object of the metadata dataset
	hid_t mdsid = -1;				// metadata dataset data space ID
	hsize_t dsize;					// Size of the metadata dataset = mdsize_all
	MPI_Offset seloff, soff, eoff;	// Temp variable for encoding start and end
	haddr_t mdoff;					// File offset of the metadata dataset
	MPI_Datatype mmtype = MPI_DATATYPE_NULL;
	MPI_Status stat;
	std::vector<std::array<MPI_Offset, H5S_MAX_RANK>> dsteps (fp->ndset);

	H5VL_LOGI_PROFILING_TIMER_START;

	H5VL_LOGI_PROFILING_TIMER_START;

	mlens = (MPI_Offset *)malloc (sizeof (MPI_Offset) * (fp->ndset * 2 + 1));
	memset (mlens, 0, sizeof (MPI_Offset) * fp->ndset);
	moffs = mlens + fp->ndset;
	cnt	  = (int *)malloc (sizeof (int) * fp->ndset * 2);
	memset (cnt, 0, sizeof (int) * fp->ndset);
	flag = cnt + fp->ndset;

	// Merge entries with 1 selection of a dataset into a single entry with multiple selection
	if (fp->config & H5VL_FILEI_CONFIG_METADATA_MERGE) {
		// Calculate the information to encode and decode selection
		if (fp->config & H5VL_FILEI_CONFIG_SEL_ENCODE) {
			for (i = 0; i < fp->ndset; i++) {
				dsteps[i][fp->ndim[i] - 1] = 1;
				for (j = fp->ndim[i] - 2; j > -1; j--) {
					dsteps[i][j] = dsteps[i][j + 1] * fp->dsizes[i][j + 1];
				}
			}
		}
		// Calculate size and offset of the metadata per dataset
		merge_threshould = 2;  // merge entries < 2 selection
	} else {
		merge_threshould = -1;	// don't merge any
	}

	for (auto &rp : fp->wreqs) {
		if (rp.nsel < merge_threshould) {  // Don't merge varn entries
			cnt[rp.hdr.did]++;
		} else {
			char *ptr;
#ifdef ENABLE_ZLIB
			if (zbsize < rp.hdr.meta_size) { zbsize = rp.hdr.meta_size; }
#endif
			mdsize += rp.hdr.meta_size;
			nentry++;

			ptr					 = rp.meta_buf + sizeof (H5VL_logi_meta_hdr);
			*((MPI_Offset *)ptr) = rp.ldoff;
			ptr += sizeof (MPI_Offset);
			*((MPI_Offset *)ptr) = rp.rsize;
			ptr += sizeof (MPI_Offset);
		}
	}

	// Count the size of merged entries
	if (fp->config & H5VL_FILEI_CONFIG_METADATA_MERGE) {
		for (i = 0; i < fp->ndset; i++) {
			if (cnt[i] > 0) {							  // Have merged entry
				mlens[i] += sizeof (H5VL_logi_meta_hdr);  // Size, ID and flag
				// Size of selection list
				// nsel field only present when there are more than 1 hyperslab
				if (cnt[i] > 1) { mlens[i] += sizeof (int); }
				// Selection list
				if (fp->config & H5VL_FILEI_CONFIG_SEL_ENCODE) {
					mlens[i] += fp->ndim[i] * sizeof (MPI_Offset);	// dstep
					mlens[i] += (sizeof (MPI_Offset) * 3 + sizeof (size_t)) * (size_t)cnt[i];
				} else {
					mlens[i] += (sizeof (MPI_Offset) * fp->ndim[i] * 2 + sizeof (MPI_Offset) +
								 sizeof (size_t)) *
								(size_t)cnt[i];
				}
			}
			mdsize += mlens[i];
		}
	}

	// Buf offset for each merged entry
	moffs[0] = 0;
	for (i = 0; i < fp->ndset; i++) {
		moffs[i + 1] = moffs[i] + mlens[i];
#ifdef ENABLE_ZLIB
		if (zbsize < mlens[i]) { zbsize = mlens[i]; }
#endif
	}

	H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_INIT);

#ifdef LOGVOL_PROFILING
	H5VL_log_profile_add_time (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_SIZE, (double)(mdsize) / 1048576);
#endif

	// Pack data
	H5VL_LOGI_PROFILING_TIMER_START;
#ifdef ENABLE_ZLIB
	buf	 = (char *)malloc (moffs[fp->ndset] + zbsize);
	zbuf = buf + moffs[fp->ndset];
#else
	buf = (char *)malloc (moffs[fp->ndset]);
#endif
	bufp = (char **)malloc (sizeof (char *) * fp->ndset * 2);

	// Pack data for the merged requests
	if (fp->config & H5VL_FILEI_CONFIG_METADATA_MERGE) {
		nentry += fp->ndset;
		// Header for merged entries
		for (i = 0; i < fp->ndset; i++) {
			bufp[i] = buf + moffs[i] + sizeof (H5VL_logi_meta_hdr);	 // Skip the header for now
			flag[i] = 0;
			// Fill the header
			// Don't generate merged entry if there is none
			if (cnt[i] > 0) {
				if ((fp->ndim[i] > 1) && (fp->config & H5VL_FILEI_CONFIG_SEL_ENCODE)) {
					flag[i] |= H5VL_LOGI_META_FLAG_SEL_ENCODE;
				}
				if (cnt[i] > 1) {
					flag[i] |= H5VL_LOGI_META_FLAG_MUL_SELX;

					if (fp->config & H5VL_FILEI_CONFIG_SEL_DEFLATE) {
						flag[i] |= H5VL_LOGI_META_FLAG_SEL_DEFLATE;
					}

					// Number of entries
					*((int *)bufp[i]) = cnt[i];
					bufp[i] += sizeof (int);
				}
			}
			bufp[i + fp->ndset] = bufp[i] + sizeof (MPI_Offset) * cnt[i] * 2;
		}

		// Pack selection
		for (auto &rp : fp->wreqs) {
			if (rp.nsel < merge_threshould) {  // Part of merged entries
				char *ptr;

				ptr = bufp[rp.hdr.did];
				bufp[rp.hdr.did] += sizeof (MPI_Offset);

				// File offset and size
				*((MPI_Offset *)ptr) = rp.ldoff;
				ptr += sizeof (MPI_Offset) * cnt[rp.hdr.did];
				*((size_t *)ptr) = rp.rsize;
				ptr += sizeof (size_t) * cnt[rp.hdr.did];

				// Start and count
				if (fp->config & H5VL_FILEI_CONFIG_SEL_ENCODE) {
					MPI_Offset *start;
					MPI_Offset *count;

					start = (MPI_Offset *)(rp.meta_buf + sizeof (H5VL_logi_meta_hdr) +
										   sizeof (MPI_Offset) * 2);
					count = start + fp->ndim[rp.hdr.did];
					soff = eoff = 0;
					for (i = 0; i < fp->ndim[rp.hdr.did]; i++) {
						soff += start[i] *
								dsteps[rp.hdr.did][i];	// Starting offset of the bounding box
						eoff += (count[i]) *
								dsteps[rp.hdr.did][i];	// Ending offset of the bounding box
					}
					ptr = bufp[rp.hdr.did + fp->ndset];
					bufp[rp.hdr.did + fp->ndset] += sizeof (MPI_Offset);
					*((MPI_Offset *)ptr) = soff;
					ptr += sizeof (MPI_Offset) * cnt[rp.hdr.did];
					*((MPI_Offset *)ptr) = eoff;
					ptr += sizeof (MPI_Offset) * cnt[rp.hdr.did];
				} else {
					ptr = bufp[rp.hdr.did + fp->ndset];
					bufp[rp.hdr.did + fp->ndset] += sizeof (MPI_Offset) * cnt[rp.hdr.did];
					memcpy (ptr,
							rp.meta_buf + sizeof (H5VL_logi_meta_hdr) + sizeof (MPI_Offset) * 2,
							sizeof (MPI_Offset) * fp->ndim[rp.hdr.did]);
					ptr += sizeof (MPI_Offset) * fp->ndim[rp.hdr.did] * cnt[rp.hdr.did];
					memcpy (ptr,
							rp.meta_buf + sizeof (H5VL_logi_meta_hdr) + sizeof (MPI_Offset) * 2,
							sizeof (MPI_Offset) * fp->ndim[rp.hdr.did]);
				}
			}
		}
	}

	H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_PACK);

#ifdef ENABLE_ZLIB
	H5VL_LOGI_PROFILING_TIMER_START;
	// Recount mdsize after compression
	mdsize = 0;
	// Compress merged entries
	if (fp->config & H5VL_FILEI_CONFIG_METADATA_MERGE) {
		for (i = 0; i < fp->ndset; i++) {
			if (flag[i] & H5VL_LOGI_META_FLAG_SEL_DEFLATE) {
				inlen = mlens[i] - sizeof (H5VL_logi_meta_hdr);
				clen  = zbsize;
				err	  = H5VL_log_zip_compress (buf + moffs[i] + sizeof (H5VL_logi_meta_hdr), inlen,
											   zbuf, &clen);
				if ((err == 0) && (clen < inlen)) {
					memcpy (buf + moffs[i] + sizeof (H5VL_logi_meta_hdr), zbuf, clen);
					mlens[i] = sizeof (H5VL_logi_meta_hdr) + clen;
				} else {
					// Compressed size larger, abort compression
					flag[i] &= ~(H5VL_FILEI_CONFIG_SEL_DEFLATE);
				}
			}
			// Recalculate metadata size after comrpession
			mdsize += mlens[i];
		}
	}

	// Compress standalone varn entries
	for (auto &rp : fp->wreqs) {
		if (rp.nsel >= merge_threshould) {
			if (rp.hdr.flag & H5VL_LOGI_META_FLAG_SEL_DEFLATE) {
				inlen = rp.hdr.meta_size - sizeof (H5VL_logi_meta_hdr);
				clen  = zbsize;
				err = H5VL_log_zip_compress (rp.meta_buf + sizeof (H5VL_logi_meta_hdr), inlen, zbuf,
											 &clen);
				if ((err == 0) && (clen < inlen)) {
					memcpy (rp.meta_buf + sizeof (H5VL_logi_meta_hdr), zbuf, clen);
					rp.hdr.meta_size = sizeof (H5VL_logi_meta_hdr) + clen;
				} else {
					// Compressed size larger, abort compression
					rp.hdr.flag &= ~(H5VL_FILEI_CONFIG_SEL_DEFLATE);
				}
				mdsize += rp.hdr.meta_size;
			}
		}
	}
	H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_ZIP);
#ifdef LOGVOL_PROFILING
	H5VL_log_profile_add_time (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_SIZE_ZIP, (double)(mdsize) / 1048576);
#endif
#endif

	// Write entry header later after compression
	H5VL_LOGI_PROFILING_TIMER_START;
	// Header for the merged requests
	if (fp->config & H5VL_FILEI_CONFIG_METADATA_MERGE) {
		// Header for merged entries
		for (i = 0; i < fp->ndset; i++) {
			// Don't generate merged entry if there is none
			if (cnt[i] > 0) {
				*((H5VL_logi_meta_hdr *)(buf + moffs[i])) = {(int)mlens[i], i, flag[i]};
			}
		}
	}
	// Header for standalone varn requests
	for (auto &rp : fp->wreqs) {
		if (rp.nsel >= merge_threshould) {	// Part of merged entries
			*((H5VL_logi_meta_hdr *)rp.meta_buf) = rp.hdr;
		}
	}

	H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_PACK);

	// Write metadata to file
	H5VL_LOGI_PROFILING_TIMER_START;
	// Create memory datatype
	offs = (MPI_Aint *)malloc (sizeof (MPI_Aint) * nentry);
	lens = (int *)malloc (sizeof (int) * nentry);
	if (fp->config & H5VL_FILEI_CONFIG_METADATA_MERGE) {
		// moffs will be reused as file offset, create memory type first
		for (i = 0; i < fp->ndset; i++) {
			offs[i] = (MPI_Aint) (moffs[i] + (size_t)buf);
			lens[i] = (int)mlens[i];
		}
		nentry = fp->ndset;
	} else {
		nentry = 0;
	}
	// Standalone varn requests
	for (auto &rp : fp->wreqs) {
		if (rp.nsel >= merge_threshould) {	// Part of merged entries
			offs[nentry]   = (MPI_Aint)rp.meta_buf;
			lens[nentry++] = (int)rp.hdr.meta_size;
		}
	}

	mpierr = MPI_Type_hindexed (nentry, lens, offs, MPI_BYTE, &mmtype);
	CHECK_MPIERR
	mpierr = MPI_Type_commit (&mmtype);
	CHECK_MPIERR
	H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_WRITE);  // Part of writing

	// Sync metadata size
	H5VL_LOGI_PROFILING_TIMER_START;
	mpierr = MPI_Allreduce (&mdsize, &mdsize_all, 1, MPI_LONG_LONG, MPI_SUM, fp->comm);
	CHECK_MPIERR
	// NOTE: Some MPI implementation do not produce output for rank 0, moffs must ne initialized
	// to 0
	doff   = 0;
	mpierr = MPI_Exscan (&mdsize, &doff, 1, MPI_LONG_LONG, MPI_SUM, fp->comm);
	CHECK_MPIERR
	H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_SYNC);

	dsize = (hsize_t)mdsize_all;
	if (dsize > 0) {
		H5VL_loc_params_t loc;

		// Create metadata dataset
		H5VL_LOGI_PROFILING_TIMER_START;
		mdsid = H5Screate_simple (1, &dsize, &dsize);
		CHECK_ID (mdsid)
		sprintf (mdname, "_md_%d", fp->nmdset);
		loc.obj_type = H5I_GROUP;
		loc.type	 = H5VL_OBJECT_BY_SELF;
		H5VL_LOGI_PROFILING_TIMER_START;
		mdp = H5VLdataset_create (fp->lgp, &loc, fp->uvlid, mdname, H5P_LINK_CREATE_DEFAULT,
								  H5T_STD_B8LE, mdsid, H5P_DATASET_CREATE_DEFAULT,
								  H5P_DATASET_ACCESS_DEFAULT, fp->dxplid, NULL);
		CHECK_PTR (mdp);
		fp->nmdset++;
		H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VLDATASET_CREATE);

		// Get metadata dataset file offset
		H5VL_LOGI_PROFILING_TIMER_START;
		err = H5VL_logi_dataset_optional_wrapper (mdp, fp->uvlid, H5VL_NATIVE_DATASET_GET_OFFSET,
												  fp->dxplid, NULL, &mdoff);
		CHECK_ERR
		H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VLDATASET_OPTIONAL);
		H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_CREATE);

		// Close the metadata dataset
		H5VL_LOGI_PROFILING_TIMER_START;
		H5VL_LOGI_PROFILING_TIMER_START;
		err = H5VLdataset_close (mdp, fp->uvlid, fp->dxplid, NULL);
		CHECK_ERR
		H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VLDATASET_CLOSE);
		H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_CLOSE);

		// Write metadata
		H5VL_LOGI_PROFILING_TIMER_START;  // TIMER_H5VL_LOG_FILEI_METAFLUSH_WRITE
		err = MPI_File_write_at_all (fp->fh, mdoff + doff, MPI_BOTTOM, 1, mmtype, &stat);
		CHECK_MPIERR
		H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_WRITE);

		H5VL_LOGI_PROFILING_TIMER_START;
		// This barrier is required to ensure no process read metadata before everyone finishes
		// writing
		MPI_Barrier (MPI_COMM_WORLD);
		H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_BARRIER);

		// Update status
		fp->idxvalid  = false;
		fp->metadirty = false;
	}

	for (auto &rp : fp->wreqs) {
		if (rp.meta_buf) { free (rp.meta_buf); }
	}
	H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH);
err_out:
	// Cleanup
	H5VL_log_free (offs);
	H5VL_log_free (lens);
	H5VL_log_free (mlens);
	H5VL_log_free (cnt);
	H5VL_log_free (buf);
	H5VL_log_free (bufp);
	H5VL_log_free (mlens);
	H5VL_log_Sclose (mdsid);
	if (mmtype != MPI_DATATYPE_NULL) { MPI_Type_free (&mmtype); }
	return err;
}

herr_t H5VL_log_filei_metaupdate (H5VL_log_file_t *fp) {
	herr_t err = 0;
	int i;
	H5VL_loc_params_t loc;
	htri_t mdexist;
	void *mdp = NULL, *ldp = NULL;
	hid_t mdsid = -1, ldsid = -1;
	hsize_t mdsize, ldsize;
	char *buf = NULL, *bufp;
	int ndim;
	H5VL_log_metaentry_t entry;
	H5VL_LOGI_PROFILING_TIMER_START;

	if (fp->metadirty) { H5VL_log_filei_metaflush (fp); }

	loc.obj_type					 = H5I_GROUP;
	loc.type						 = H5VL_OBJECT_BY_SELF;
	loc.loc_data.loc_by_name.name	 = "_idx";
	loc.loc_data.loc_by_name.lapl_id = H5P_LINK_ACCESS_DEFAULT;
	err = H5VL_logi_link_specific_wrapper (fp->lgp, &loc, fp->uvlid, H5VL_LINK_EXISTS, fp->dxplid,
										   NULL, &mdexist);
	CHECK_ERR

	if (mdexist > 0) {
		mdp = H5VLdataset_open (fp->lgp, &loc, fp->uvlid, "_idx", H5P_DATASET_ACCESS_DEFAULT,
								fp->dxplid, NULL);
		CHECK_PTR (mdp)
		// ldp = H5VLdataset_open(fp->lgp, &loc, fp->uvlid, "_lookup",
		// H5P_DATASET_ACCESS_DEFAULT, fp->dxplid, NULL); CHECK_PTR(ldp)

		// Get data space and size
		H5VL_LOGI_PROFILING_TIMER_START;
		err = H5VL_logi_dataset_get_wrapper (mdp, fp->uvlid, H5VL_DATASET_GET_SPACE, fp->dxplid,
											 NULL, &mdsid);
		CHECK_ERR
		H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VLDATASET_GET);
		// err = H5VL_logi_dataset_get_wrapper(ldp, fp->uvlid, H5VL_DATASET_GET_SPACE,
		// fp->dxplid, NULL, &ldsid); CHECK_ERR
		ndim = H5Sget_simple_extent_dims (mdsid, &mdsize, NULL);
		LOG_VOL_ASSERT (ndim == 1);
		// ndim = H5Sget_simple_extent_dims(ldsid, &ldsize, NULL); assert(ndim == 1);
		err = H5Sselect_all (mdsid);
		CHECK_ERR

		// Allocate buffer
		buf = (char *)malloc (sizeof (char) * mdsize);
		// fp->lut.resize(ldsize);

		// Read metadata
		err = H5VLdataset_read (mdp, fp->uvlid, H5T_NATIVE_B8, mdsid, mdsid, fp->dxplid, buf, NULL);
		CHECK_ERR
		// err = H5VLdataset_read(ldp, fp->uvlid, H5T_STD_I64LE, ldsid, ldsid, fp->dxplid,
		// fp->lut.data(), NULL);    CHECK_ERR

		// Close the dataset
		err = H5VLdataset_close (mdp, fp->uvlid, fp->dxplid, NULL);
		CHECK_ERR
		// err = H5VLdataset_close(ldp, fp->uvlid, fp->dxplid, NULL); CHECK_ERR

		/* Debug code to dump metadata read
		{
			int rank;
			char fname[32];

			MPI_Comm_rank(MPI_COMM_WORLD, &rank);

			sprintf(fname,"p%d_rd.txt",rank);
			hexDump(NULL, buf, mdsize, fname);

		}
		*/

		// Parse metadata
		bufp = buf;
		while (bufp < buf + mdsize) {
			entry.did = *((int *)bufp);
			LOG_VOL_ASSERT ((entry.did >= 0) && (entry.did < fp->ndset));
			bufp += sizeof (int);
			ndim = *((int *)bufp);
			LOG_VOL_ASSERT (ndim >= 0);
			bufp += sizeof (int);
			memcpy (entry.start, bufp, ndim * sizeof (MPI_Offset));
			bufp += ndim * sizeof (MPI_Offset);
			memcpy (entry.count, bufp, ndim * sizeof (MPI_Offset));
			bufp += ndim * sizeof (MPI_Offset);
			entry.ldoff = *((MPI_Offset *)bufp);
			bufp += sizeof (MPI_Offset);
			entry.rsize = *((size_t *)bufp);
			bufp += sizeof (size_t);

			fp->idx[entry.did].push_back (entry);
		}
	} else {
		for (i = 0; i < fp->ndset; i++) { fp->idx[i].clear (); }
	}

	fp->idxvalid = true;

	H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAUPDATE);
err_out:;

	// Cleanup
	if (mdsid >= 0) H5Sclose (mdsid);
	if (ldsid >= 0) H5Sclose (ldsid);
	H5VL_log_free (buf);

	return err;
}
=======
#include "H5VL_logi_util.hpp"
#include "H5VL_logi_wrapper.hpp"
#include "H5VL_logi_zip.hpp"

// A hash function used to hash a pair of any kind
struct hash_pair {
    size_t operator() (const std::pair<void *, size_t> &p) const {
        size_t ret = 0;
        size_t *val;
        size_t *end = (size_t *)((char *)(p.first) + p.second - p.second % sizeof (size_t));

        for (val = (size_t *)(p.first); val < end; val++) { ret ^= *val; }

        return ret;
    }
};

struct equal_pair {
    bool operator() (const std::pair<void *, size_t> &a, const std::pair<void *, size_t> &b) const {
        if (a.second != b.second) { return false; }
        return memcmp (a.first, b.first, a.second) == 0;
    }
};

void H5VL_log_filei_metaflush (H5VL_log_file_t *fp) {
    herr_t err = 0;
    int mpierr;
    int i;
    MPI_Offset
        rbuf[2];  // [Local metadata offset within the metadata dataset, Global metadata size]
    MPI_Offset mdsize  = 0;  // Local metadata size
    MPI_Offset *mdoffs = NULL;
    MPI_Offset *mdoffs_snd;
    MPI_Aint *offs = NULL;                    // Offset in MPI_Type_create_hindexed
    int *lens      = NULL;                    // Lens in MPI_Type_create_hindexed
    int nentry     = 0;                       // Number of metadata entries
    char mdname[32];                          // Name of metadata dataset
    void *mdp;                                // under VOL object of the metadata dataset
    hid_t mdsid  = -1;                        // metadata dataset data space ID
    hid_t dcplid = -1;                        // metadata dataset creation property ID
    hid_t dxplid = -1;                        // metadata dataset transfer property ID
    hid_t fdid = -1;                          // file driver ID; used to perform passthru write
    hsize_t dsize;                            // Size of the metadata dataset = mdsize_all
    haddr_t mdoff;                            // File offset of the metadata dataset
    MPI_Datatype mmtype = MPI_DATATYPE_NULL;  // Memory datatype for writing the metadata
    MPI_Status stat;                          // Status of MPI I/O
    H5VL_loc_params_t loc;
    bool perform_write_in_mpi = true;
    H5VL_logi_err_finally finally ([&offs, &lens, &mdoffs, &mdsid, &dcplid, &dxplid, &mmtype] () -> void {
        H5VL_log_free (offs);
        H5VL_log_free (lens);
        H5VL_log_free (mdoffs);
        H5VL_log_Sclose (mdsid);
        H5VL_log_Pclose (dcplid);
        H5VL_log_Pclose (dxplid);
        if (mmtype != MPI_DATATYPE_NULL) { MPI_Type_free (&mmtype); }
    });

    if (fp->config & H5VL_FILEI_CONFIG_PASSTHRU) {
        perform_write_in_mpi = false;
    } else {
        perform_write_in_mpi = true;
    }

    H5VL_LOGI_PROFILING_TIMER_START;
    H5VL_LOGI_PROFILING_TIMER_START;

    // Create memory datatype
    nentry = fp->wreqs.size ();
    if (fp->group_rank == 0) { nentry++; }
    offs = (MPI_Aint *)malloc (sizeof (MPI_Aint) * nentry);
    lens = (int *)malloc (sizeof (int) * nentry);
    if (fp->group_rank == 0) {
        mdoffs = (MPI_Offset *)malloc (sizeof (MPI_Offset) * (fp->group_np + 1) * 3);
        CHECK_PTR (mdoffs)
        mdoffs_snd = mdoffs + fp->group_np + 1;

        offs[0] = (MPI_Aint) (mdoffs);
        lens[0] = (int)(sizeof (MPI_Offset) * (fp->group_np + 1));

        nentry = 1;
        mdsize += lens[0];
    } else {
        nentry = 0;
    }

    // Gather offset and lens
    for (auto &rp : fp->wreqs) {
        offs[nentry] = (MPI_Aint)rp->meta_buf;
        lens[nentry] = (int)rp->hdr->meta_size;
        mdsize += lens[nentry++];
    }
    if (nentry && perform_write_in_mpi) {
        mpierr = MPI_Type_create_hindexed (nentry, lens, offs, MPI_BYTE, &mmtype);
        CHECK_MPIERR
        mpierr = MPI_Type_commit (&mmtype);
        CHECK_MPIERR
    }
    H5VL_LOGI_PROFILING_TIMER_STOP (fp,
                                    TIMER_H5VL_LOG_FILEI_METAFLUSH_PACK);  // Part of writing

    // Sync metadata size
    H5VL_LOGI_PROFILING_TIMER_START;
    // mpierr = MPI_Allreduce (&mdsize, &mdsize_all, 1, MPI_LONG_LONG, MPI_SUM, fp->comm);
    // CHECK_MPIERR
    mpierr =
        MPI_Gather (&mdsize, 1, MPI_LONG_LONG, mdoffs + 1, 1, MPI_LONG_LONG, 0, fp->group_comm);
    CHECK_MPIERR
    if (fp->group_rank == 0) {  // Rank 0 calculate
        mdoffs[0] = 0;
        for (i = 0; i < fp->group_np; i++) { mdoffs[i + 1] += mdoffs[i]; }
        rbuf[1] = mdoffs[fp->group_np];  // Total size
        // Copy to send array with space
        for (i = 0; i < fp->group_np; i++) { mdoffs_snd[i << 1] = mdoffs[i]; }
        // Fill total size
        for (i = 1; i < fp->group_np * 2; i += 2) { mdoffs_snd[i] = rbuf[1]; }
    }
    mpierr = MPI_Scatter (mdoffs_snd, 2, MPI_LONG_LONG, rbuf, 2, MPI_LONG_LONG, 0, fp->group_comm);
    CHECK_MPIERR
    // Bcast merged into scatter
    // mpierr = MPI_Bcast (&mdsize_all, 1, MPI_LONG_LONG, 0, fp->comm);
    // CHECK_MPIERR

    // The first lens[0] byte is the decomposition map
    if (fp->group_rank == 0) { mdoffs[0] = lens[0] / sizeof (MPI_Offset) - 1; }

    // NOTE: Some MPI implementation do not produce output for rank 0, moffs must ne initialized
    // to 0
    // doff = 0;
    // mpierr = MPI_Exscan (&mdsize, &doff, 1, MPI_LONG_LONG, MPI_SUM, fp->comm);
    // CHECK_MPIERR
    H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_SYNC);

    // Swap endian of metadata headers before writing
#ifdef WORDS_BIGENDIAN
    for (auto &rp : fp->wreqs) {
        H5VL_logi_lreverse ((uint32_t *)rp->meta_buf,
                            (uint32_t *)(rp->meta_buf + sizeof (H5VL_logi_meta_hdr)));
    }
#endif

    // Where to create data dataset, main file or subfile
    loc.type     = H5VL_OBJECT_BY_SELF;
    loc.obj_type = H5I_GROUP;

    dsize = (hsize_t)rbuf[1];
    if (dsize > (hsize_t) (sizeof (MPI_Offset) * (fp->group_np + 1))) {
        // Create metadata dataset
        H5VL_LOGI_PROFILING_TIMER_START;
        mdsid = H5Screate_simple (1, &dsize, &dsize);
        CHECK_ID (mdsid)

        // Allocate file space at creation time
        dcplid = H5Pcreate (H5P_DATASET_CREATE);
        CHECK_ID (dcplid)
        err = H5Pset_alloc_time (dcplid, H5D_ALLOC_TIME_EARLY);

        // set up transfer property list; using collective MPI IO
        dxplid = H5Pcreate(H5P_DATASET_XFER);
        CHECK_ID(dxplid);

        // Create dataset with under VOL
        sprintf (mdname, "%s_%d", H5VL_LOG_FILEI_DSET_META, fp->nmdset);
        H5VL_LOGI_PROFILING_TIMER_START;
        mdp = H5VLdataset_create (fp->lgp, &loc, fp->uvlid, mdname, H5P_LINK_CREATE_DEFAULT,
                                  H5T_STD_B8LE, mdsid, dcplid, H5P_DATASET_ACCESS_DEFAULT,
                                  dxplid, NULL);
        H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VLDATASET_CREATE);
        CHECK_PTR (mdp);
        fp->nmdset++;

        // Get metadata dataset file offset
        H5VL_logi_dataset_get_foff (fp, mdp, fp->uvlid, dxplid, &mdoff);

        // If not allocated, flush the file and reopen the dataset
        if (mdoff == HADDR_UNDEF) {
            H5VL_file_specific_args_t arg;

            // Close the dataset
            err = H5VLdataset_close (mdp, fp->uvlid, dxplid, NULL);
            CHECK_ERR

            // Flush the file
            arg.op_type             = H5VL_FILE_FLUSH;
            arg.args.flush.scope    = H5F_SCOPE_GLOBAL;
            arg.args.flush.obj_type = H5I_FILE;
            err                     = H5VLfile_specific (fp->uo, fp->uvlid, &arg, dxplid, NULL);
            CHECK_ERR

            // Reopen the dataset
            mdp = H5VLdataset_open (fp->lgp, &loc, fp->uvlid, mdname, H5P_DATASET_ACCESS_DEFAULT,
                                    dxplid, NULL);
            CHECK_PTR (mdp);

            // Get dataset file offset
            H5VL_logi_dataset_get_foff (fp, mdp, fp->uvlid, dxplid, &mdoff);

            // Still don't work, discard the data
            if (mdoff == HADDR_UNDEF) {
                printf ("WARNING: Log dataset creation failed, metadata is not recorded\n");
                fflush (stdout);

                nentry = 0;
                mdoff  = 0;
            }
        }
        H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_CREATE);

        // Write metadata
        if (perform_write_in_mpi) {
            H5VL_LOGI_PROFILING_TIMER_START;  // TIMER_H5VL_LOG_FILEI_METAFLUSH_WRITE
            if (nentry) {
                mpierr =
                    MPI_File_write_at_all (fp->fh, mdoff + rbuf[0], MPI_BOTTOM, 1, mmtype, &stat);
            } else {
                mpierr =
                    MPI_File_write_at_all (fp->fh, mdoff + rbuf[0], MPI_BOTTOM, 0, MPI_INT, &stat);
            }
            CHECK_MPIERR

            H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_WRITE);
        } else {
            // set collective MPI IO only if H5FD_MPIO driver is used.
            fdid = H5Pget_driver (fp->ufaplid);
            CHECK_ID (fdid)
            if (fdid == H5FD_MPIO) {
                err = H5Pset_dxpl_mpio(dxplid, H5FD_MPIO_COLLECTIVE);
                CHECK_ERR;
            }
            hsize_t mstart = (hsize_t)rbuf[0], mbsize = (hsize_t)mdsize, one = 1;

            // file space:
            err = H5Sselect_hyperslab (mdsid, H5S_SELECT_SET, &mstart, NULL, &one, &mbsize);
            CHECK_ERR;

            // mem space
            char *mbuff = (char *)malloc (mdsize);
            for (int i = 0, mstart = 0; i < nentry; i++) {
                memcpy (mbuff + mstart, (void *)offs[i], lens[i]);
                mstart += lens[i];
            }
            hid_t mspace_id = H5Screate_simple (1, &mbsize, &mbsize);

            H5VL_LOGI_PROFILING_TIMER_START;
            err = H5VL_log_under_dataset_write (mdp, fp->uvlid, H5T_STD_B8LE, mspace_id, mdsid,
                                     dxplid, mbuff, NULL);
            CHECK_ERR;
            H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_WRITE);
            free (mbuff);
            H5VL_log_Sclose (mspace_id);
        }

        // Close the metadata dataset
        H5VL_LOGI_PROFILING_TIMER_START;
        H5VL_LOGI_PROFILING_TIMER_START;
        err = H5VLdataset_close (mdp, fp->uvlid, dxplid, NULL);
        CHECK_ERR
        H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VLDATASET_CLOSE);
        H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_CLOSE);

        H5VL_LOGI_PROFILING_TIMER_START;
        // This barrier is required to ensure no process read metadata before everyone finishes
        // writing
        MPI_Barrier (fp->comm);
        H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH_BARRIER);
    }

    // Need to swap the endian back if metadata headers are still needed
    /*
#ifdef WORDS_BIGENDIAN
    for (auto &rp : fp->wreqs) {
            H5VL_logi_lreverse (rp->meta_buf, (uint64_t *)(rp->meta_buf +
sizeof(H5VL_logi_meta_hdr)));
    }
#endif
    */

    // Update status
    fp->idxvalid  = false;
    fp->metadirty = false;

    // Delete requests
    for (auto &rp : fp->wreqs) { delete rp; }
    fp->wreqs.clear ();
    fp->nflushed = 0;

    // Recore metadata size
#ifdef LOGVOL_PROFILING
    H5VL_log_profile_add_time (fp, TIMER_H5VL_LOG_FILEI_METASIZE, (double)(fp->mdsize) / 1048576);
#endif
    fp->mdsize = 0;
    // Record dedup hash
    fp->wreq_hash.clear ();

    H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAFLUSH);
}

/*
 * Remove all existing index entry in fp
 * Load all metadata in the metadata index of fp
 */
void H5VL_log_filei_metaupdate (H5VL_log_file_t *fp) {
    herr_t err = 0;
    int i;
    H5VL_loc_params_t loc;
    void *mdp   = NULL;  // Metadata dataset
    hid_t mdsid = -1;    // Metadata dataset space
    hid_t mmsid = -1;    // metadata buffer memory space
    hsize_t mdsize;      // Size of metadata dataset
    hsize_t start, count, one = 1;
    char *buf = NULL;             // Buffer for raw metadata
    int ndim;                     // metadata dataset dimensions (should be 1)
    MPI_Offset nsec;              // Number of sections in current metadata dataset
    H5VL_logi_metaentry_t block;  // Buffer of decoded metadata entry
    std::map<char *, std::vector<H5VL_logi_metasel_t>> bcache;  // Cache for linked metadata entry
    char mdname[16];
    H5VL_logi_err_finally finally ([&mdsid, &mmsid, &buf] () -> void {
        if (mdsid >= 0) H5Sclose (mdsid);
        if (mmsid >= 0) H5Sclose (mmsid);
        if (buf) { H5VL_log_free (buf); }
    });

    H5VL_LOGI_PROFILING_TIMER_START;

    // Dataspace for memory buffer
    start = count = INT64_MAX - 1;
    mmsid         = H5Screate_simple (1, &start, &count);

    // Flush all write requests
    if (fp->metadirty) { H5VL_log_filei_metaflush (fp); }

    // Remove all index entries
    fp->idx->clear ();

    // iterate through all metadata datasets
    loc.type     = H5VL_OBJECT_BY_SELF;
    loc.obj_type = H5I_GROUP;
    for (i = 0; i < fp->nmdset; i++) {
        // Open the metadata dataset
        sprintf (mdname, "%s_%d", H5VL_LOG_FILEI_DSET_META, i);
        mdp = H5VLdataset_open (fp->lgp, &loc, fp->uvlid, mdname, H5P_DATASET_ACCESS_DEFAULT,
                                fp->dxplid, NULL);
        CHECK_PTR (mdp)

        // Get data space and size
        mdsid = H5VL_logi_dataset_get_space (fp, mdp, fp->uvlid, fp->dxplid);
        CHECK_ID (mdsid)
        ndim = H5Sget_simple_extent_dims (mdsid, &mdsize, NULL);
        assert (ndim == 1);

        // N sections
        start = 0;
        count = sizeof (MPI_Offset);
        err   = H5Sselect_hyperslab (mmsid, H5S_SELECT_SET, &start, NULL, &one, &count);
        CHECK_ERR
        err = H5Sselect_hyperslab (mdsid, H5S_SELECT_SET, &start, NULL, &one, &count);
        CHECK_ERR
        MPI_Offset *nsecp = &nsec;
        err =
            H5VL_log_under_dataset_read (mdp, fp->uvlid, H5T_NATIVE_B8, mmsid, mdsid, fp->dxplid, nsecp, NULL);
        CHECK_ERR

        // Allocate buffer for raw metadata
        start = sizeof (MPI_Offset) * (nsec + 1);
        count = mdsize - start;
        buf   = (char *)malloc (sizeof (char) * count);

        // Read metadata
        err = H5Sselect_hyperslab (mdsid, H5S_SELECT_SET, &start, NULL, &one, &count);
        CHECK_ERR
        start = 0;
        err   = H5Sselect_hyperslab (mmsid, H5S_SELECT_SET, &start, NULL, &one, &count);
        CHECK_ERR
        err = H5VL_log_under_dataset_read (mdp, fp->uvlid, H5T_NATIVE_B8, mmsid, mdsid, fp->dxplid, buf, NULL);
        CHECK_ERR

        // Close the metadata dataset
        err = H5VLdataset_close (mdp, fp->uvlid, fp->dxplid, NULL);
        CHECK_ERR

        // Parse metadata
        fp->idx->parse_block (buf, count);

        // Free metadata buffer
        H5VL_log_free (buf);
    }

    // Mark index as up to date
    fp->idxvalid = true;

    H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAUPDATE);
}

/*
 * Remove all existing index entry in fp
 * Load the metadata starting from sec in md in the metadata index of fp until the metadata
 * buffer size is reached Advance sec to the next unprocessed section. If all section is
 * processed, advance md and set sec to 0 If all metadata datasset is processed, set md to -1
 */
void H5VL_log_filei_metaupdate_part (H5VL_log_file_t *fp, int &md, int &sec) {
    herr_t err = 0;
    int i;
    H5VL_loc_params_t loc;
    void *mdp   = NULL;  // Metadata dataset
    hid_t mdsid = -1;    // Metadata dataset space
    hid_t mmsid = -1;    // metadata buffer memory space
    hsize_t mdsize;      // Size of metadata dataset
    hsize_t start, count, one = 1;
    char *buf = NULL;             // Buffer for raw metadata
    int ndim;                     // metadata dataset dimensions (should be 1)
    MPI_Offset nsec;              // Number of sections in current metadata dataset
    MPI_Offset *offs;             // Section end offset array
    H5VL_logi_metaentry_t block;  // Buffer of decoded metadata entry
    std::map<char *, std::vector<H5VL_logi_metasel_t>> bcache;  // Cache for linked metadata entry
    char mdname[16];
    H5VL_logi_err_finally finally ([&mdsid, &mmsid, &buf] () -> void {
        if (mdsid >= 0) H5Sclose (mdsid);
        if (mmsid >= 0) H5Sclose (mmsid);
        H5VL_log_free (buf);
    });

    H5VL_LOGI_PROFILING_TIMER_START;

    // Dataspace for memory buffer
    start = count = INT64_MAX - 1;
    mmsid         = H5Screate_simple (1, &start, &count);

    // Flush all write requests
    if (fp->metadirty) { H5VL_log_filei_metaflush (fp); }

    // Remove all index entries
    fp->idx->clear ();

    // Open the metadata dataset
    loc.type     = H5VL_OBJECT_BY_SELF;
    loc.obj_type = H5I_GROUP;
    sprintf (mdname, "%s_%d", H5VL_LOG_FILEI_DSET_META, md);
    mdp = H5VLdataset_open (fp->lgp, &loc, fp->uvlid, mdname, H5P_DATASET_ACCESS_DEFAULT,
                            fp->dxplid, NULL);
    CHECK_PTR (mdp)

    // Get data space and size
    mdsid = H5VL_logi_dataset_get_space (fp, mdp, fp->uvlid, fp->dxplid);
    CHECK_ID (mdsid)
    ndim = H5Sget_simple_extent_dims (mdsid, &mdsize, NULL);
    assert (ndim == 1);

    // Get number of sections (first 8 bytes)
    start = 0;
    count = sizeof (MPI_Offset);
    err   = H5Sselect_hyperslab (mmsid, H5S_SELECT_SET, &start, NULL, &one, &count);
    CHECK_ERR
    err = H5Sselect_hyperslab (mdsid, H5S_SELECT_SET, &start, NULL, &one, &count);
    CHECK_ERR
    MPI_Offset *nsecp = &nsec;
    err = H5VL_log_under_dataset_read (mdp, fp->uvlid, H5T_NATIVE_B8, mmsid, mdsid, fp->dxplid, nsecp, NULL);
    CHECK_ERR

    // Get the ending offset of each section (next 8 * nsec bytes)
    count = sizeof (MPI_Offset) * nsec;
    offs  = (MPI_Offset *)malloc (count);
    err   = H5Sselect_hyperslab (mmsid, H5S_SELECT_SET, &start, NULL, &one, &count);
    CHECK_ERR
    start = sizeof (MPI_Offset);
    err   = H5Sselect_hyperslab (mdsid, H5S_SELECT_SET, &start, NULL, &one, &count);
    CHECK_ERR
    err = H5VL_log_under_dataset_read (mdp, fp->uvlid, H5T_NATIVE_B8, mmsid, mdsid, fp->dxplid, offs, NULL);
    CHECK_ERR

    // Determine #sec to fit
    if (sec >= nsec) { RET_ERR ("Invalid section") }
    if (sec == 0) {  // First section always starts after the sections offset array
        start = sizeof (MPI_Offset) * (nsec + 1);
    } else {
        start = offs[sec - 1];
    }
    for (i = sec + 1; i < nsec; i++) {
        if (offs[i] - start > (size_t) (fp->mbuf_size)) { break; }
    }
    if (i <= sec) { RET_ERR ("OOM") }  // At least 1 section should fit into buffer limit
    count = offs[i - 1] - start;

    // Advance sec and md
    sec = i;
    if (sec >= nsec) {
        sec = 0;
        md++;
    }
    if (md >= fp->nmdset) { md = -1; }

    // Allocate buffer for raw metadata
    buf = (char *)malloc (sizeof (char) * count);

    // Read metadata
    err = H5Sselect_hyperslab (mdsid, H5S_SELECT_SET, &start, NULL, &one, &count);
    CHECK_ERR
    start = 0;
    err   = H5Sselect_hyperslab (mmsid, H5S_SELECT_SET, &start, NULL, &one, &count);
    CHECK_ERR
    err = H5VL_log_under_dataset_read (mdp, fp->uvlid, H5T_NATIVE_B8, mmsid, mdsid, fp->dxplid, buf, NULL);
    CHECK_ERR

    // Close the metadata dataset
    err = H5VLdataset_close (mdp, fp->uvlid, fp->dxplid, NULL);
    CHECK_ERR

    // Parse metadata
    fp->idx->parse_block (buf, count);

    H5VL_LOGI_PROFILING_TIMER_STOP (fp, TIMER_H5VL_LOG_FILEI_METAUPDATE);
}
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

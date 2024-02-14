/*
 *  Copyright (C) 2022, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <hdf5.h>

#ifdef TEST_H5VL_LOG
#include "H5VL_log.h"
#include "testutils.hpp"
#else
#include "common.hpp"
#endif

#define N 10

int main (int argc, char **argv) {
    int err, nerrs = 0;
    int rank, np;
    const char *file_name;
    hid_t fid      = -1;  // File ID
    hid_t gid      = -1;  // Group ID
    hid_t sgid     = -1;  // Subgroup ID
    hid_t faplid   = -1;

    int mpi_required;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &mpi_required);

    MPI_Comm_size (MPI_COMM_WORLD, &np);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    if (argc > 2) {
        if (!rank) printf ("Usage: %s [filename]\n", argv[0]);
        MPI_Finalize ();
        return 1;
    } else if (argc > 1) {
        file_name = argv[1];
    } else {
        file_name = "group.h5";
    }

    faplid = H5Pcreate (H5P_FILE_ACCESS);
    CHECK_ERR (faplid)
    // MPI and collective metadata is required by LOG VOL
    err = H5Pset_fapl_mpio (faplid, MPI_COMM_WORLD, MPI_INFO_NULL);
    CHECK_ERR (err)
    err = H5Pset_all_coll_metadata_ops (faplid, 1);
    CHECK_ERR (err)

#ifdef TEST_H5VL_LOG
    /* check VOL related environment variables */
    vol_env env;
    check_env(&env);
    if (env.native_only == 0 && env.connector == 0) {
        hid_t log_vlid=H5I_INVALID_HID;
        // Register LOG VOL plugin
        log_vlid = H5VLregister_connector (&H5VL_log_g, H5P_DEFAULT);
        CHECK_ERR (log_vlid)
        err = H5Pset_vol (faplid, log_vlid, NULL);
        CHECK_ERR (err)
        err = H5VLclose (log_vlid);
        CHECK_ERR (err)
    }
#endif
    SHOW_TEST_INFO ("Creating groups")

    // Create file
    fid = H5Fcreate (file_name, H5F_ACC_TRUNC, H5P_DEFAULT, faplid);
    CHECK_ERR (fid)

    // Create group
    gid = H5Gcreate2 (fid, "test", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    CHECK_ERR (gid)
    // Create sub-group
    sgid = H5Gcreate2 (gid, "test2", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    CHECK_ERR (sgid)
    err = H5Gclose (sgid);
    CHECK_ERR (err)
    err = H5Gclose (gid);
    CHECK_ERR (err)

    // Open group
    gid = H5Gopen2 (fid, "test", H5P_DEFAULT);
    CHECK_ERR (gid)
    // Open sub-group
    sgid = H5Gopen2 (gid, "test2", H5P_DEFAULT);
    CHECK_ERR (sgid)

    err = H5Gclose (sgid);
    CHECK_ERR (err)
    sgid = -1;
    err  = H5Gclose (gid);
    CHECK_ERR (err)
    gid = -1;

    err = H5Fclose (fid);
    CHECK_ERR (err)
    fid = -1;

    err = H5Pclose (faplid);
    CHECK_ERR (err)
    faplid = -1;

err_out:
    if (sgid >= 0) H5Gclose (sgid);
    if (gid >= 0) H5Gclose (gid);
    if (fid >= 0) H5Fclose (fid);
    if (faplid >= 0) H5Pclose (faplid);

    SHOW_TEST_RESULT

    MPI_Finalize ();

    return (nerrs > 0);
}

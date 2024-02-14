#!/bin/bash -l
#
# Copyright (C) 2022, Northwestern University and Argonne National Laboratory
# See COPYRIGHT notice in top-level directory.
#

RUN_CMD=`echo ${TESTMPIRUN} | ${SED} -e "s/NP/$1/g"`
# echo "MPIRUN = ${MPIRUN}"
# echo "check_PROGRAMS=${check_PROGRAMS}"

# Some output files may be HDF5 regular files
. $srcdir/../common/wrap_runs.sh

log_vol_file_only=0

for p in ${check_PROGRAMS} ; do
   test_func ./$p
done


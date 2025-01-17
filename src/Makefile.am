#
# Copyright (C) 2019, Northwestern University and Fermi National Accelerator Laboratory
# See COPYRIGHT notice in top-level directory.
#
# @configure_input@

SUFFIXES = .cpp .hpp .o .m4 .m4h

AM_CPPFLAGS = -I.
if LOGVOL_DEBUG
   AM_CPPFLAGS += -DLOGVOL_DEBUG=1
endif
if LOGVOL_PROFILING
   AM_CPPFLAGS += -DLOGVOL_PROFILING=1
endif
M4FLAGS = -I${top_srcdir}/m4

lib_LTLIBRARIES = libH5VL_log.la

M4_SRCS =  
            
M4H_SRCS =  

if LOGVOL_PROFILING
   M4_SRCS +=  H5VL_logi_profiling.m4 
   M4H_SRCS += H5VL_logi_profiling.m4h
endif

H_SRCS =    H5VL_log.h \
            H5VL_log_internal.h

C_SRCS = 

CXX_SRCS =  H5VL_log_att.cpp \
            H5VL_log_blob.cpp \
            H5VL_log_dataset.cpp \
            H5VL_log_dataseti.cpp \
            H5VL_log_datatype.cpp \
            H5VL_log_datatypei.cpp \
            H5VL_log_file.cpp \
            H5VL_log_filei.cpp \
            H5VL_log_filei_meta.cpp \
            H5VL_log_group.cpp \
            H5VL_log_info.cpp \
            H5VL_log_introspect.cpp \
            H5VL_log_link.cpp \
            H5VL_log_main.cpp \
            H5VL_log_obj.cpp \
            H5VL_log_obji.cpp \
            H5VL_log_req.cpp \
            H5VL_log_reqi.cpp \
            H5VL_log_token.cpp \
            H5VL_log_wrap.cpp \
            H5VL_log.cpp \
            H5VL_logi_dataspace.cpp \
            H5VL_logi_filter.cpp \
            H5VL_logi_filter_deflate.cpp \
            H5VL_logi_idx.cpp \
            H5VL_logi_mem.cpp \
            H5VL_logi_nb.cpp \
            H5VL_logi_util.cpp \
            H5VL_logi_wrapper.cpp \
            H5VL_logi_zip.cpp

if LOGVOL_DEBUG
   CXX_SRCS += H5VL_logi_debug.cpp
endif

include_HEADERS = H5VL_log.h

$(M4_SRCS:.m4=.cpp): Makefile
$(M4H_SRCS:.m4=.hpp): Makefile

.m4.cpp:
	$(M4) $(AM_M4FLAGS) $(M4FLAGS) $< >$@

.m4h.hpp:
	$(M4) $(AM_M4FLAGS) $(M4FLAGS) $< >$@

libH5VL_log_la_SOURCES = $(C_SRCS) $(CXX_SRCS) $(H_SRCS)
nodist_libH5VL_log_la_SOURCES = $(M4_SRCS:.m4=.cpp) $(M4H_SRCS:.m4h=.h)

BUILT_SOURCES = $(M4_SRCS:.m4=.cpp) $(M4H_SRCS:.m4h=.hpp)

CLEANFILES = $(M4_SRCS:.m4=.cpp) $(M4H_SRCS:.m4h=.hpp) core core.* *.gcda *.gcno *.gcov gmon.out

EXTRA_DIST = $(M4_HFILES) $(M4_SRCS) $(M4H_SRCS)

dist-hook:
	$(SED_I) -e "s|RELEASE_DATE|@LOGVOL_RELEASE_DATE@|g" $(distdir)/main.cpp
	$(SED_I) -e "1,10s|_LOGVOL_RELEASE_DATE_|@LOGVOL_RELEASE_DATE@|" $(distdir)/RELEASE_NOTES.md
	$(SED_I) -e "1,10s|_LOGVOL_VERSION_|$(LOGVOL_VERSION)|" $(distdir)/RELEASE_NOTES.md

.PHONY:

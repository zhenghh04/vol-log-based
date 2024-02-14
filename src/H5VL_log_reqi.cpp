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

<<<<<<< HEAD
#include <H5VLpublic.h>
=======
#include <H5VLconnector.h>
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

#include <cassert>
#include <cstdlib>

#include "H5VL_log_obj.hpp"
#include "H5VL_log_req.hpp"
#include "H5VL_log_reqi.hpp"
#include "H5VL_logi.hpp"
#include "H5VL_logi_debug.hpp"

<<<<<<< HEAD
herr_t H5VL_log_reqi_notify_cb (void *ctx, H5ES_status_t status) {
	herr_t err = 0;
	int i;
	H5VL_log_req_notify_ctx_t *cp = (H5VL_log_req_notify_ctx_t *)ctx;

	if (status == H5ES_STATUS_FAIL) {
		cp->stat = H5ES_STATUS_FAIL;
	} else if (cp->stat == H5ES_STATUS_SUCCEED) {
		cp->stat = status;
	}

	if (--cp->cnt == 0) {
		err = cp->cb (cp->ctx, cp->stat);
		delete cp;
	}

	return err;
}

void H5VL_log_req_t::append (void *uo) {
	H5VL_log_ureq_t ureq;

	ureq.stat = H5ES_STATUS_IN_PROGRESS;
	ureq.req  = uo;
	this->ureqs.push_back (ureq);
}
=======
herr_t H5VL_log_reqi_notify_cb (void *ctx, H5VL_request_status_t status) {
    herr_t err                    = 0;
    H5VL_log_req_notify_ctx_t *cp = (H5VL_log_req_notify_ctx_t *)ctx;

    if (status == H5VL_REQUEST_STATUS_FAIL) {
        cp->stat = H5VL_REQUEST_STATUS_FAIL;
    } else if (cp->stat == H5VL_REQUEST_STATUS_SUCCEED) {
        cp->stat = status;
    }

    if (--cp->cnt == 0) {
        err = cp->cb (cp->ctx, cp->stat);
        delete cp;
    }

    return err;
}

void H5VL_log_req_t::append (void *uo) {
    H5VL_log_ureq_t ureq;

    ureq.stat = H5VL_REQUEST_STATUS_IN_PROGRESS;
    ureq.req  = uo;
    this->ureqs.push_back (ureq);
}
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

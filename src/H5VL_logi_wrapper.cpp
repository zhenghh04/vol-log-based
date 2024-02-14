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
#include "H5VL_logi_wrapper.hpp"
#include "H5VL_logi.hpp"

herr_t H5VL_logi_file_optional_wrapper(void *obj, hid_t connector_id, H5VL_file_optional_t opt_type, hid_t dxpl_id, void **req, ...) {
    herr_t err = 0;
    va_list args;

    va_start(args, req);
    err = H5VLfile_optional(obj, connector_id, opt_type, dxpl_id, req, args);
    va_end(args);

    return err;
}

herr_t H5VL_logi_attr_get_wrapper(void *obj, hid_t connector_id, H5VL_attr_get_t get_type, hid_t dxpl_id, void **req, ...) {
    herr_t err = 0;
    va_list args;

    va_start(args, req);
    err = H5VLattr_get(obj, connector_id, get_type, dxpl_id, req, args);
    va_end(args);

    return err;
}


herr_t H5VL_logi_dataset_optional_wrapper(void *obj, hid_t connector_id, H5VL_dataset_optional_t opt_type, hid_t dxpl_id, void **req, ...) {
    herr_t err = 0;
    va_list args;

    va_start(args, req);
    err = H5VLdataset_optional(obj, connector_id, opt_type, dxpl_id, req, args);
    va_end(args);

    return err;
}

herr_t H5VL_logi_dataset_specific_wrapper(void *obj, hid_t connector_id, H5VL_dataset_specific_t specific_type, hid_t dxpl_id, void **req, ...) {
    herr_t err = 0;
    va_list args;

    va_start(args, req);
    err = H5VLdataset_specific(obj, connector_id, specific_type, dxpl_id, req, args);
    va_end(args);

    return err;
}

herr_t H5VL_logi_dataset_get_wrapper(void *obj, hid_t connector_id, H5VL_dataset_get_t get_type, hid_t dxpl_id, void **req, ...) {
    herr_t err = 0;
    va_list args;

    va_start(args, req);
    err = H5VLdataset_get(obj, connector_id, get_type, dxpl_id, req, args);
    va_end(args);

    return err;
}

herr_t H5VL_logi_link_specific_wrapper(void *obj, const H5VL_loc_params_t *loc_params, hid_t connector_id, H5VL_link_specific_t specific_type, hid_t dxpl_id, void **req, ...) {
    herr_t err = 0;
    va_list args;

    va_start(args, req);
    err = H5VLlink_specific(obj, loc_params, connector_id, specific_type, dxpl_id, req, args);
    va_end(args);

    return err;
}

herr_t H5VL_logi_object_get_wrapper(void *obj, const H5VL_loc_params_t *loc_params, hid_t connector_id, H5VL_object_get_t get_type, hid_t dxpl_id, void **req, ...) {
    herr_t err = 0;
    va_list args;

    va_start(args, req);
    err = H5VLobject_get(obj, loc_params, connector_id, get_type, dxpl_id, req, args);
    va_end(args);

    return err;
}
=======
#include "H5VL_logi.hpp"
#include "H5VL_logi_wrapper.hpp"

/*
herr_t H5VL_optional_args_t *args, hid_t dxpl_id, void **req, ...) {
        herr_t err = 0;
        va_list args;

        va_start(args, req);
        err = H5VLfile_optional(obj, connector_id, opt_type, dxpl_id, req, args);
        va_end(args);

        return err;
}

herr_t H5VL_logi_attr_get_wrapper(void *obj, hid_t connector_id, H5VL_attr_get_args_t *args, hid_t
dxpl_id, void **req, ...) { herr_t err = 0; va_list args;

        va_start(args, req);
        err = H5VLattr_get(obj, connector_id, args->get_type, dxpl_id, req, args);
        va_end(args);

        return err;
}


herr_t H5VL_optional_args_t *args, hid_t dxpl_id, void **req, ...) {
        herr_t err = 0;
        va_list args;

        va_start(args, req);
        err = H5VLdataset_optional(obj, connector_id, opt_type, dxpl_id, req, args);
        va_end(args);

        return err;
}

herr_t H5VL_logi_dataset_specific_wrapper(void *obj, hid_t connector_id,
H5VL_dataset_specific_args_t *args, hid_t dxpl_id, void **req, ...) { herr_t err = 0; va_list args;

        va_start(args, req);
        err = H5VLdataset_specific(obj, connector_id, args->op_type, dxpl_id, req, args);
        va_end(args);

        return err;
}

herr_t H5VL_logi_dataset_get_wrapper(void *obj, hid_t connector_id, H5VL_dataset_get_args_t *args,
hid_t dxpl_id, void **req, ...) { herr_t err = 0; va_list args;

        va_start(args, req);
        err = H5VLdataset_get(obj, connector_id, args->get_type, dxpl_id, req, args);
        va_end(args);

        return err;
}

herr_t H5VL_logi_link_specific_wrapper(void *obj, const H5VL_loc_params_t *loc_params, hid_t
connector_id, H5VL_link_specific_args_t *args, hid_t dxpl_id, void **req, ...) { herr_t err = 0;
        va_list args;

        va_start(args, req);
        err = H5VLlink_specific(obj, loc_params, connector_id, args->op_type, dxpl_id, req, args);
        va_end(args);

        return err;
}

herr_t H5VL_logi_object_get_wrapper(void *obj, const H5VL_loc_params_t *loc_params, hid_t
connector_id, H5VL_object_get_args_t *args, hid_t dxpl_id, void **req, ...) { herr_t err = 0;
        va_list args;

        va_start(args, req);
        err = H5VLobject_get(obj, loc_params, connector_id, args->get_type, dxpl_id, req, args);
        va_end(args);

        return err;
}
*/
>>>>>>> e3cb362c05e61722f6854d54b14270b33ec7c49a

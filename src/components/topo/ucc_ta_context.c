/**
 * Copyright (C) Mellanox Technologies Ltd. 2021.  ALL RIGHTS 
 * RESERVED. 
 *
 * See file LICENSE for terms.
 */

#include "ucc_ta_context.h"
#include "core/ucc_context.h"

ucc_status_t ucc_ta_context_create(const ucc_context_config_h  config,
                                   ucc_context_t *context)
{
    context->ta_ctx = NULL;
    return UCC_OK; /* TODO !!! Implement */
}

ucc_status_t ucc_ta_context_destroy(ucc_ta_context_t *ta_ctx)
{
    return UCC_OK; /* TODO !!! Implement */
}



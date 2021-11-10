/**
 * Copyright (C) Mellanox Technologies Ltd. 2021.  ALL RIGHTS 
 * RESERVED. 
 *
 * See file LICENSE for terms.
 */

#include "ucc_ta.h"

ucc_status_t ucc_ta_alltoallv_get_comm_pattern(ucc_ta_coll_op_req_t *req,
                                               ucc_ta_coll_comm_pattern_t **pattern)
{
    *pattern = NULL;
    return UCC_OK; /* TODO !!! Implement */
}


void ucc_ta_pattern_destroy(ucc_ta_coll_comm_pattern_t *pattern)
{
    /* TODO !!! Implement */
}

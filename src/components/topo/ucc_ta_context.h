/**
 * Copyright (C) Mellanox Technologies Ltd. 2021.  ALL RIGHTS 
 * RESERVED. 
 *
 * See file LICENSE for terms.
 */

#ifndef UCC_TA_CONTEXT_H_
#define UCC_TA_CONTEXT_H_

#include "components/base/ucc_base_iface.h"

/** TA CONTEXT (topology aware context) is a data structure
    used to store the topology niformation.
 */
typedef struct ucc_ta_net_context ucc_ta_net_context_t; /*!!! IMPLEMENT */
typedef struct ucc_ta_node_context ucc_ta_node_context_t; /*!!! IMPLEMENT */

typedef struct ucc_ta_net_context {

} ucc_ta_net_context_t;

typedef struct ucc_ta_node_context {

} ucc_ta_node_context_t;

typedef struct ucc_ta_context {
    ucc_ta_net_context_t    net_ctx;
    ucc_ta_node_context_t   node_ctx;
} ucc_ta_context_t;


/* Parse topology files */
ucc_status_t ucc_ta_context_create(const ucc_context_config_h  config,
                                   ucc_context_t *context);

ucc_status_t ucc_ta_context_destroy(ucc_ta_context_t *ta_ctx);


#endif /* UCC_TA_CONTEXT_H_ */

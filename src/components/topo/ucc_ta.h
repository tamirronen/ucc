/**
 * Copyright (C) Mellanox Technologies Ltd. 2021.  ALL RIGHTS 
 * RESERVED. 
 *
 * See file LICENSE for terms.
 */

#ifndef UCC_TA_H_
#define UCC_TA_H_

#include "components/base/ucc_base_iface.h"

/** TA (topology aware) is an internal interface that provides
    communication pattern based on the topology structure and
    the location of the team members.
 */
typedef enum {
    UCC_TA_ALGORITHM_SRA_KNOMIAL        = UCC_BIT(0),
    UCC_TA_ALGORITHM_PAIRWISE           = UCC_BIT(1),
    UCC_TA_ALGORITHM_LAST               = UCC_BIT(2)
} ucc_ta_algorithm_t;

typedef enum {
    UCC_TA_COMM_TYPE_RING,
    UCC_TA_COMM_TYPE_SRA_KNOMIAL,
    UCC_TA_COMM_TYPE_IO_LIST,
    UCC_TA_COMM_TYPE_CUDA_IPC,
    UCC_TA_COMM_TYPE_LAST
} ucc_ta_comm_type_t;
 
typedef struct ucc_ta_comm_stage_data {
    ucc_ta_comm_type_t comm_type;
    int64_t comm_data;
    uint8_t stage_start;
    uint8_t stage_end;
    ucc_rank_t *dst_comm_seq;
    uint16_t dst_comm_seq_size;
    ucc_rank_t *src_comm_seq;
    uint16_t src_comm_seq_size;
} ucc_ta_comm_stage_data_t;

typedef struct ucc_ta_coll_op_req {
    ucc_ta_algorithm_t algorithm;
    ucc_base_team_t *team;
    int is_cuda_ipc;
} ucc_ta_coll_op_req_t;


typedef struct ucc_ta_coll_comm_pattern {
	ucc_ta_comm_stage_data_t *stages;
        uint16_t stages_size;
} ucc_ta_coll_comm_pattern_t;

ucc_status_t ucc_ta_alltoallv_get_comm_pattern(ucc_ta_coll_op_req_t *req,
                                               ucc_ta_coll_comm_pattern_t **pattern);


void ucc_ta_pattern_destroy(ucc_ta_coll_comm_pattern_t *pattern);

#endif

/**
 * Copyright (C) Mellanox Technologies Ltd. 2021.  ALL RIGHTS RESERVED.
 *
 * See file LICENSE for terms.
 */

#include "config.h"
#include "tl_ucp.h"
#include "alltoallv.h"
#include "components/topo/ucc_ta.h"

ucc_status_t ucc_tl_ucp_alltoallv_pairwise_start(ucc_coll_task_t *task);
ucc_status_t ucc_tl_ucp_alltoallv_pairwise_progress(ucc_coll_task_t *task);

static ucc_status_t update_ta_stage(ucc_tl_ucp_task_t *task,
                                    ucc_ta_coll_comm_pattern_t *pattern)
{
    ucc_tl_ucp_team_t *team  = TASK_TEAM(task);
    ucc_rank_t         gsize = UCC_TL_TEAM_SIZE(team);;
    task->super.ta_stage = NULL;

    if (pattern == NULL) {
        return UCC_OK;
    }

    if (pattern->stages_size != 1 ||
        pattern->stages[0].comm_type != UCC_TA_COMM_TYPE_IO_LIST ||
        pattern->stages[0].dst_comm_seq_size != gsize ||
        pattern->stages[0].src_comm_seq_size != gsize) {
        return UCC_ERR_NOT_IMPLEMENTED;
    }
    task->super.ta_stage = &pattern->stages[0];

    return UCC_OK;
}

ucc_status_t ucc_tl_ucp_alltoallv_init(ucc_tl_ucp_task_t *task)
{
    ucc_status_t status;
    ucc_ta_coll_op_req_t req;
    ucc_ta_coll_comm_pattern_t *pattern;

    ALLTOALLV_TASK_CHECK(TASK_ARGS(task), TASK_TEAM(task));

    req.algorithm = UCC_TA_ALGORITHM_LAST;
    req.team = task->super.team;
    req.is_cuda_ipc = 0;

    status = ucc_ta_alltoallv_get_comm_pattern(&req, &pattern);
    if (status != UCC_OK) {
        goto out;
    }
    status = update_ta_stage(task, pattern);
    if (status != UCC_OK) {
        goto out;
    }

    status = ucc_tl_ucp_alltoallv_pairwise_init_common(task);
out:
    return status;
}

ucc_status_t ucc_tl_ucp_alltoallv_pairwise_init(ucc_base_coll_args_t *coll_args,
                                                ucc_base_team_t      *team,
                                                ucc_coll_task_t     **task_h)
{
    ucc_tl_ucp_team_t *tl_team = ucc_derived_of(team, ucc_tl_ucp_team_t);
    ucc_tl_ucp_task_t *task;
    ucc_status_t       status;

    ALLTOALLV_TASK_CHECK(coll_args->args, tl_team);
    task                 = ucc_tl_ucp_init_task(coll_args, team);
    *task_h              = &task->super;
    status = ucc_tl_ucp_alltoallv_pairwise_init_common(task);
out:
    return status;
}

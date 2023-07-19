#ifndef IBE_REENC_SYSTEM_H
#define IBE_REENC_SYSTEM_H

// includes
#include <stdio.h>
#include <pbc/pbc.h>

#include "lib-misc.h"
#include "lib-mesg.h"
#include "lib-shared.h"
#include "lib-custom-types.h"
#include "lib-bb-ibe-system.h"
#include "lib-cbe-gamal-system.h"

// alias
typedef shared_params_t ibe_reenc_params_t;

// functions
void ibe_reenc_clear(
    reenc_eID_t eID,
    ibe_reenc_rkID_t rkID,
    ibe_reenc_skR_t skR);
void ibe_reenc_system_egen(
    reenc_eID_t eID,
    bb_ibe_skID_t skID,
    pairing_t pairing);
void ibe_reenc_system_keygen_rkg(
    ibe_reenc_skR_t skR,
    bb_ibe_mk_t mk,
    ibe_reenc_params_t params,
    pairing_t pairing);
void ibe_reenc_system_keygen_pro(
    ibe_reenc_rkID_t rkID,
    ibe_reenc_skR_t skR,
    reenc_eID_t eID1,
    ibe_reenc_params_t params,
    element_t ID,
    element_t ID1,
    pairing_t pairing);
void ibe_reenc_system_reenc(
    bb_ibe_C_t C_ID1,
    ibe_reenc_rkID_t rkID,
    ibe_reenc_params_t params,
    bb_ibe_C_t C_ID,
    // element_t ID,
    // element_t ID1,
    pairing_t pairing);
int ibe_reenc_system_check(
    ibe_reenc_params_t params,
    bb_ibe_C_t C_ID,
    element_t ID,
    pairing_t pairing);

#endif
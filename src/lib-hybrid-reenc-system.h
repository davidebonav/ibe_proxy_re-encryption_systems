#ifndef hybrid_reenc_SYSTEM_H
#define hybrid_reenc_SYSTEM_H

/*
    Implementation of the "Boneh-Boyen Identity-Based Encryption (BB-IBE) system"
    introduced by Boneh and Boyen in their 2004 paper.
*/

// includes
#include <stdio.h>
#include <pbc/pbc.h>

#include "lib-misc.h"
#include "lib-mesg.h"
#include "lib-shared.h"
#include "lib-custom-types.h"
#include "lib-bb-ibe-system.h"
#include "lib-cbe-gamal-system.h"

// structs
typedef shared_params_ptr hybrid_reenc_params_ptr;
typedef shared_params_t hybrid_reenc_params_t; // alias

// functions
void hybrid_reenc_clear(
    reenc_eID_t eID,
    hybrid_reenc_rkID_t rkID);

void hybrid_reenc_system_egen(
    reenc_eID_t eID,
    bb_ibe_skID_t skID,
    pairing_t pairing);

void hybrid_reenc_system_keygen_pro(
    hybrid_reenc_rkID_t rkID,
    cbe_gamal_sk_t sk,
    reenc_eID_t eID,
    hybrid_reenc_params_t params,
    pairing_t pairing);

void hybrid_reenc_system_reenc(
    bb_ibe_C_t C_ID,
    hybrid_reenc_rkID_t rkID,
    hybrid_reenc_params_t params,
    cbe_gamal_C_t C_PK,
    element_t ID,
    pairing_t pairing);

int hybrid_reenc_system_check(
    hybrid_reenc_params_t params,
    cbe_gamal_C_t C_PK,
    cbe_gamal_pk_t pk,
    pairing_t pairing);

#endif // hybrid_reenc_SYSTEM_H

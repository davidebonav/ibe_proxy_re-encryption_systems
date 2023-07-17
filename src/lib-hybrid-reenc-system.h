#ifndef hybrid_reenc_SYSTEM_H
#define hybrid_reenc_SYSTEM_H

/*
    Implementation of the "Boneh-Boyen Identity-Based Encryption (BB-IBE) system"
    introduced by Boneh and Boyen in their 2004 paper.
*/

// includes
#include <pbc/pbc.h>
#include <gmp.h>

#include <stdio.h>
#include <assert.h>

#include "lib-misc.h"
#include "lib-mesg.h"
#include "lib-shared.h"
#include "lib-bb-ibe-system.h"
#include "lib-cbe-gamal-system.h"

// structs
typedef shared_params_ptr hybrid_reenc_params_ptr;
typedef shared_params_t hybrid_reenc_params_t; // alias

struct hybrid_reenc_eID_struct
{
    element_t eID;
};
typedef struct hybrid_reenc_eID_struct *hybrid_reenc_eID_ptr;
typedef struct hybrid_reenc_eID_struct hybrid_reenc_eID_t[1];

struct hybrid_reenc_rkID_struct
{
    element_t theta;
    element_t g_u_b;
    element_t delta;
};
typedef struct hybrid_reenc_rkID_struct *hybrid_reenc_rkID_ptr;
typedef struct hybrid_reenc_rkID_struct hybrid_reenc_rkID_t[1];

// functions
void hybrid_reenc_clear(
    hybrid_reenc_eID_t eID,
    hybrid_reenc_rkID_t rkID);

void hybrid_reenc_system_egen(
    hybrid_reenc_eID_t eID,
    bb_ibe_skID_t skID,
    pairing_t pairing);

void hybrid_reenc_system_keygen_pro(
    hybrid_reenc_rkID_t rkID,
    cbe_gamal_sk_t sk,
    hybrid_reenc_eID_t eID,
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

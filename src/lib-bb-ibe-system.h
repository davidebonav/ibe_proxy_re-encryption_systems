#ifndef BB_IBE_SYSTEM_H
#define BB_IBE_SYSTEM_H

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

// structs
typedef shared_params_ptr bb_ibe_params_ptr;
typedef shared_params_t bb_ibe_params_t; // alias

struct bb_ibe_mk_struct
{
    element_t mk; // = g2^a
};
typedef struct bb_ibe_mk_struct *bb_ibe_mk_ptr;
typedef struct bb_ibe_mk_struct bb_ibe_mk_t[1];

struct bb_ibe_skID_struct
{
    element_t d0;
    element_t d1;
};
typedef struct bb_ibe_skID_struct *bb_ibe_skID_ptr;
typedef struct bb_ibe_skID_struct bb_ibe_skID_t[1];

struct bb_ibe_C_struct
{
    element_t c1;
    element_t c2;
    element_t c3;
};
typedef struct bb_ibe_C_struct *bb_ibe_C_ptr;
typedef struct bb_ibe_C_struct bb_ibe_C_t[1];

// functions
void bb_ibe_clear(
    bb_ibe_params_t params,
    bb_ibe_mk_t mk,
    bb_ibe_skID_t sk,
    bb_ibe_C_t C);

void bb_ibe_system_setup(
    bb_ibe_params_t params,
    bb_ibe_mk_t mk,
    pairing_t pairing);

void bb_ibe_system_keygen(
    bb_ibe_skID_t skID,
    bb_ibe_params_t params,
    bb_ibe_mk_t mk,
    element_t ID,
    pairing_t pairing);

void bb_ibe_system_encrypt(
    bb_ibe_C_t C,
    element_t ID,
    bb_ibe_params_t params,
    element_t M,
    pairing_t pairing);

void bb_ibe_system_decrypt(
    element_t M,
    bb_ibe_skID_t sk,
    bb_ibe_C_t C,
    bb_ibe_params_t params,
    pairing_t pairing);

#endif // BB_IBE_SYSTEM_H

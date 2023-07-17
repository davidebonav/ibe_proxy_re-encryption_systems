#ifndef CBE_ELGAMAL_SYSTEM_H
#define CBE_ELGAMAL_SYSTEM_H

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
typedef shared_params_ptr cbe_gamal_params_ptr;
typedef shared_params_t cbe_gamal_params_t; // alias

struct cbe_gamal_pk_struct
{
    element_t g3;
    element_t g4;
    element_t g5;
};
typedef struct cbe_gamal_pk_struct *cbe_gamal_pk_ptr;
typedef struct cbe_gamal_pk_struct cbe_gamal_pk_t[1];

struct cbe_gamal_sk_struct
{
    element_t theta;
    element_t beta;
    element_t delta;
};
typedef struct cbe_gamal_sk_struct *cbe_gamal_sk_ptr;
typedef struct cbe_gamal_sk_struct cbe_gamal_sk_t[1];

struct cbe_gamal_C_struct
{
    element_t c1;
    element_t c2;
    element_t c3;
    element_t c4;
};
typedef struct cbe_gamal_C_struct *cbe_gamal_C_ptr;
typedef struct cbe_gamal_C_struct cbe_gamal_C_t[1];


// functions
void cbe_gamal_clear(
    cbe_gamal_params_t params,
    cbe_gamal_pk_t pk,
    cbe_gamal_sk_t sk,
    cbe_gamal_C_t C);

void cbe_gamal_system_setup(
    cbe_gamal_params_t params,
    pairing_t pairing);

void cbe_gamal_system_keygen(
    cbe_gamal_sk_t sk,
    cbe_gamal_pk_t pk,
    cbe_gamal_params_t params,
    pairing_t pairing);

void cbe_gamal_system_encrypt(
    cbe_gamal_C_t C,
    cbe_gamal_pk_t pk,
    cbe_gamal_params_t params,
    element_t M,
    pairing_t pairing);

void cbe_gamal_system_decrypt(
    element_t M,
    cbe_gamal_sk_t sk,
    cbe_gamal_params_t params,
    cbe_gamal_C_t C,
    pairing_t pairing);

#endif // CBE_ELGAMAL_SYSTEM_H

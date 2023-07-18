#ifndef CBE_ELGAMAL_SYSTEM_H
#define CBE_ELGAMAL_SYSTEM_H

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

// structs
typedef shared_params_ptr cbe_gamal_params_ptr;
typedef shared_params_t cbe_gamal_params_t; // alias

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

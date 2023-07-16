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
struct bb_ibe_system_struct
{
    pairing_t pairing;
};
typedef struct bb_ibe_system_struct *bb_ibe_system_ptr;
typedef struct bb_ibe_system_struct bb_ibe_systems_t[1];

struct bb_ibe_params_struct
{
    element_t g;  // generator
    element_t g1; // = g^a
    element_t g2;
    element_t h;
};
typedef struct bb_ibe_params_struct *bb_ibe_params_ptr;
typedef struct bb_ibe_params_struct bb_ibe_params_t[1];

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

// functions
void bb_ibe_init(bb_ibe_systems_t bb_ibe_system, pbc_pairing_type_t pairing_type, unsigned int level);
void bb_ibe_clear(bb_ibe_systems_t system, bb_ibe_params_t params, bb_ibe_mk_t mk);

void bb_ibe_system_setup(bb_ibe_params_t params, bb_ibe_mk_t mk, bb_ibe_systems_t system);
// void bb_ibe_system_keygen();
// void bb_ibe_system_encrypt();
// void bb_ibe_system_decrypt();

#endif // BB_IBE_SYSTEM_H

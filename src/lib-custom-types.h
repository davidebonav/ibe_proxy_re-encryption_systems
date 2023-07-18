#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

// includes
#include <pbc/pbc.h>
#include <stdbool.h>

#include "lib-misc.h"

extern bool compute_parameters;
extern bool precomputation;
extern bool pairing_pp;
extern int sec_level;
extern pbc_pairing_type_t type;

// SHARED
struct shared_params_struct
{
    element_t g;  // generator
    element_t g1; // = g^a
    element_t g2;
    element_t h;
    // precomputation
    element_pp_t pp_g;
    element_pp_t pp_g1;
    element_pp_t pp_g2;
    element_pp_t pp_h;

    pairing_pp_t pairing_pp_g2;
};
typedef struct shared_params_struct *shared_params_ptr;
typedef struct shared_params_struct shared_params_t[1];

void init_shared_params_t(shared_params_t params, pairing_t pairing);
void clear_shared_params_t(shared_params_t params);

// BB-IBE
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
    // precomputation
    element_pp_t pp_d0;

    pairing_pp_t pairing_pp_d0;
    pairing_pp_t pairing_pp_d1;
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

void init_bb_ibe_mk_t(bb_ibe_mk_t mk, pairing_t pairing);
void init_bb_ibe_skID_t(bb_ibe_skID_t skID, pairing_t pairing);
void init_bb_ibe_C_t(bb_ibe_C_t C, pairing_t pairing);
void clear_bb_ibe_mk_t(bb_ibe_mk_t mk);
void clear_bb_ibe_skID_t(bb_ibe_skID_t skID);
void clear_bb_ibe_C_t(bb_ibe_C_t C);

// CBE-GAMAL
struct cbe_gamal_pk_struct
{
    element_t g3;
    element_t g4;
    element_t g5;

    // precomputation
    element_pp_t pp_g3;
    element_pp_t pp_g4;
    element_pp_t pp_g5;

    pairing_pp_t pairing_pp_g3;
    pairing_pp_t pairing_pp_g4;
    pairing_pp_t pairing_pp_g5;
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

    // precomputation
    element_pp_t pp_c1;
    element_pp_t pp_c2;
    element_pp_t pp_c3;

    pairing_pp_t pairing_pp_c1;
    pairing_pp_t pairing_pp_c2;
    pairing_pp_t pairing_pp_c3;
};
typedef struct cbe_gamal_C_struct *cbe_gamal_C_ptr;
typedef struct cbe_gamal_C_struct cbe_gamal_C_t[1];

void init_cbe_gamal_pk_t(cbe_gamal_pk_t pk, pairing_t pairing);
void init_cbe_gamal_sk_t(cbe_gamal_sk_t sk, pairing_t pairing);
void init_cbe_gamal_C_t(cbe_gamal_C_t C, pairing_t pairing);
void clear_cbe_gamal_pk_t(cbe_gamal_pk_t pk);
void clear_cbe_gamal_sk_t(cbe_gamal_sk_t sk);
void clear_cbe_gamal_C_t(cbe_gamal_C_t C);

// HYBRID-PROXY
struct hybrid_reenc_eID_struct
{
    element_t eID;
    // precomputation
    element_pp_t pp_eID;
};
typedef struct hybrid_reenc_eID_struct *hybrid_reenc_eID_ptr;
typedef struct hybrid_reenc_eID_struct hybrid_reenc_eID_t[1];

struct hybrid_reenc_rkID_struct
{
    element_t theta;
    element_t g_u_b;
    element_t delta;

    pairing_pp_t pairing_pp_g_u_b;
};
typedef struct hybrid_reenc_rkID_struct *hybrid_reenc_rkID_ptr;
typedef struct hybrid_reenc_rkID_struct hybrid_reenc_rkID_t[1];

void init_hybrid_reenc_eID_t(hybrid_reenc_eID_t eID, pairing_t pairing);
void init_hybrid_reenc_rkID_t(hybrid_reenc_rkID_t rkID, pairing_t pairing);
void clear_hybrid_reenc_eID_t(hybrid_reenc_eID_t eID);
void clear_hybrid_reenc_rkID_t(hybrid_reenc_rkID_t rkID);
#endif // CUSTOM_TYPES_H

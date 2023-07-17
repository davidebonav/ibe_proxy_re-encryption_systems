#include "lib-custom-types.h"

void init_shared_params_t(shared_params_t params, pairing_t pairing)
{
    element_init_G1(params->g, pairing);
    element_init_G1(params->g1, pairing);
    element_init_G1(params->g2, pairing);
    element_init_G1(params->h, pairing);
}
void clear_shared_params_t(shared_params_t params)
{
    if (params)
    {
        element_clear(params->g);
        element_clear(params->g1);
        element_clear(params->g2);
        element_clear(params->h);
    }
}

void init_bb_ibe_mk_t(bb_ibe_mk_t mk, pairing_t pairing)
{
    element_init_G1(mk->mk, pairing);
}
void clear_bb_ibe_mk_t(bb_ibe_mk_t mk)
{
    if (mk)
        element_clear(mk->mk);
}

void init_bb_ibe_skID_t(bb_ibe_skID_t skID, pairing_t pairing)
{
    element_init_G1(skID->d0, pairing);
    element_init_G1(skID->d1, pairing);
}
void clear_bb_ibe_skID_t(bb_ibe_skID_t skID)
{
    if (skID)
    {
        element_clear(skID->d0);
        element_clear(skID->d1);
    }
}

void init_bb_ibe_C_t(bb_ibe_C_t C, pairing_t pairing)
{
    element_init_G1(C->c1, pairing);
    element_init_G1(C->c2, pairing);
    element_init_GT(C->c3, pairing);
}
void clear_bb_ibe_C_t(bb_ibe_C_t C)
{
    if (C)
    {
        element_clear(C->c1);
        element_clear(C->c2);
        element_clear(C->c3);
    }
}

void init_cbe_gamal_pk_t(cbe_gamal_pk_t pk, pairing_t pairing)
{
    element_init_G1(pk->g3, pairing);
    element_init_G1(pk->g4, pairing);
    element_init_G1(pk->g5, pairing);
}
void clear_cbe_gamal_pk_t(cbe_gamal_pk_t pk)
{
    if (pk)
    {
        element_clear(pk->g3);
        element_clear(pk->g4);
        element_clear(pk->g5);
    }
}

void init_cbe_gamal_sk_t(cbe_gamal_sk_t sk, pairing_t pairing)
{
    element_init_Zr(sk->theta, pairing);
    element_init_Zr(sk->beta, pairing);
    element_init_Zr(sk->delta, pairing);
}
void clear_cbe_gamal_sk_t(cbe_gamal_sk_t sk)
{
    if (sk)
    {
        element_clear(sk->theta);
        element_clear(sk->beta);
        element_clear(sk->delta);
    }
}

void init_cbe_gamal_C_t(cbe_gamal_C_t C, pairing_t pairing)
{
    element_init_G1(C->c1, pairing);
    element_init_G1(C->c2, pairing);
    element_init_G1(C->c3, pairing);
    element_init_GT(C->c4, pairing);
}
void clear_cbe_gamal_C_t(cbe_gamal_C_t C)
{
    if (C)
    {
        element_clear(C->c1);
        element_clear(C->c2);
        element_clear(C->c3);
        element_clear(C->c4);
    }
}

void init_hybrid_reenc_eID_t(hybrid_reenc_eID_t eID, pairing_t pairing)
{
    element_init_G1(eID->eID, pairing);
}
void clear_hybrid_reenc_eID_t(hybrid_reenc_eID_t eID)
{
    if (eID)
        element_clear(eID->eID);
}

void init_hybrid_reenc_rkID_t(hybrid_reenc_rkID_t rkID, pairing_t pairing)
{
    element_init_Zr(rkID->theta, pairing);
    element_init_Zr(rkID->delta, pairing);
    element_init_G1(rkID->g_u_b, pairing);
}
void clear_hybrid_reenc_rkID_t(hybrid_reenc_rkID_t rkID)
{
    if (rkID)
    {
        element_clear(rkID->theta);
        element_clear(rkID->delta);
        element_clear(rkID->g_u_b);
    }
}
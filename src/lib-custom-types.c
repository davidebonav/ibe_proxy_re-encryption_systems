#include "lib-custom-types.h"

void init_shared_params_t(shared_params_t params, pairing_t pairing)
{
    element_init_G1(params->g, pairing);
    element_init_G1(params->g1, pairing);
    element_init_G1(params->g2, pairing);
    element_init_G1(params->h, pairing);
}

void init_bb_ibe_mk_t(bb_ibe_mk_t mk, pairing_t pairing)
{
    element_init_G1(mk->mk, pairing);
}

void init_bb_ibe_skID_t(bb_ibe_skID_t skID, pairing_t pairing)
{
    element_init_G1(skID->d0, pairing);
    element_init_G1(skID->d1, pairing);
}

void init_bb_ibe_C_t(bb_ibe_C_t C, pairing_t pairing)
{
    element_init_G1(C->c1, pairing);
    element_init_G1(C->c2, pairing);
    element_init_GT(C->c3, pairing);
}

void init_cbe_gamal_pk_t(cbe_gamal_pk_t pk, pairing_t pairing)
{
    element_init_G1(pk->g3, pairing);
    element_init_G1(pk->g4, pairing);
    element_init_G1(pk->g5, pairing);
}
void init_cbe_gamal_sk_t(cbe_gamal_sk_t sk, pairing_t pairing)
{
    element_init_Zr(sk->theta, pairing);
    element_init_Zr(sk->beta, pairing);
    element_init_Zr(sk->delta, pairing);
}
void init_cbe_gamal_C_t(cbe_gamal_C_t C, pairing_t pairing)
{
    element_init_G1(C->c1, pairing);
    element_init_G1(C->c2, pairing);
    element_init_G1(C->c3, pairing);
    element_init_GT(C->c4, pairing);
}

void init_hybrid_reenc_eID_t(hybrid_reenc_eID_t eID, pairing_t pairing)
{
    element_init_G1(eID->eID, pairing);
}
void init_hybrid_reenc_rkID_t(hybrid_reenc_rkID_t rkID, pairing_t pairing)
{
    element_init_G1(rkID->theta, pairing);
    element_init_G1(rkID->delta, pairing);
    element_init_G1(rkID->g_u_b, pairing);
}
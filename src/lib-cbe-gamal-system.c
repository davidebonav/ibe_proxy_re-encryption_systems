#include "lib-cbe-gamal-system.h"

void cbe_gamal_clear(
    cbe_gamal_params_t params,
    cbe_gamal_pk_t pk,
    cbe_gamal_sk_t sk,
    cbe_gamal_C_t C)
{
    pmesg(msg_verbose, "START cbe_gamal_clear ...");

    shared_params_clear(params);
    clear_cbe_gamal_pk_t(pk);
    clear_cbe_gamal_sk_t(sk);
    clear_cbe_gamal_C_t(C);

    pmesg(msg_verbose, "END cbe_gamal_clear ...");
}

void cbe_gamal_system_setup(
    cbe_gamal_params_t params,
    pairing_t pairing)
{
    pmesg(msg_verbose, "START cbe_gamal_system_setup ...");

    element_t a;
    element_init_Zr(a, pairing);
    element_random(a);
    pmesg_element(msg_verbose, "alpha = ", a);

    if (compute_parameters)
        shared_params_setup(params, a, pairing);

    pmesg(msg_verbose, "END cbe_gamal_system_setup ...");
}

void cbe_gamal_system_keygen(
    cbe_gamal_sk_t sk,
    cbe_gamal_pk_t pk,
    cbe_gamal_params_t params,
    pairing_t pairing)
{
    pmesg(msg_verbose, "END cbe_gamal_system_keygen ...");

    assert(sk);
    assert(pk);
    assert(params);
    assert(pairing);

    init_cbe_gamal_pk_t(pk, pairing);
    init_cbe_gamal_sk_t(sk, pairing);

    element_random(sk->theta);
    element_random(sk->beta);
    element_random(sk->delta);

    if (precomputation)
    {
        element_pp_pow_zn(pk->g3, sk->theta, params->pp_g);
        element_pp_pow_zn(pk->g4, sk->beta, params->pp_g1);
        element_pp_pow_zn(pk->g5, sk->delta, params->pp_h);

        element_pp_init(pk->pp_g3, pk->g3);
        element_pp_init(pk->pp_g4, pk->g4);
        element_pp_init(pk->pp_g5, pk->g5);
    }
    else
    {
        element_pow_zn(pk->g3, params->g, sk->theta);
        element_pow_zn(pk->g4, params->g1, sk->beta);
        element_pow_zn(pk->g5, params->h, sk->delta);
    }

    if(pairing_pp){
        pairing_pp_init(pk->pairing_pp_g3, pk->g3, pairing);
        pairing_pp_init(pk->pairing_pp_g4, pk->g4, pairing);
        pairing_pp_init(pk->pairing_pp_g5, pk->g5, pairing);
    }

    pmesg_element(msg_verbose, "", sk->theta);
    pmesg_element(msg_verbose, "", sk->beta);
    pmesg_element(msg_verbose, "", sk->delta);
    pmesg_element(msg_verbose, "", pk->g3);
    pmesg_element(msg_verbose, "", pk->g4);
    pmesg_element(msg_verbose, "", pk->g5);

    pmesg(msg_verbose, "END cbe_gamal_system_keygen ...");
}

void cbe_gamal_system_encrypt(
    cbe_gamal_C_t C,
    cbe_gamal_pk_t pk,
    cbe_gamal_params_t params,
    element_t M,
    pairing_t pairing)
{
    pmesg(msg_verbose, "START cbe_gamal_system_encrypt ...");

    assert(C);
    assert(pk);
    assert(params);
    assert(M);

    element_t r;

    element_init_Zr(r, pairing);
    init_cbe_gamal_C_t(C, pairing);

    element_random(r);
    if (precomputation)
    {
        element_pp_pow_zn(C->c1, r, pk->pp_g3);
        element_pp_pow_zn(C->c2, r, pk->pp_g4);
        element_pp_pow_zn(C->c3, r, pk->pp_g5);

        element_pp_init(C->pp_c1, C->c1);
        element_pp_init(C->pp_c2, C->c2);
        element_pp_init(C->pp_c3, C->c3);
    }
    else
    {
        element_pow_zn(C->c1, pk->g3, r);
        element_pow_zn(C->c2, pk->g4, r);
        element_pow_zn(C->c3, pk->g5, r);
    }

    if (pairing_pp)
    {
        pairing_pp_init(C->pairing_pp_c1,C->c1, pairing);
        pairing_pp_init(C->pairing_pp_c2,C->c2, pairing);
        pairing_pp_init(C->pairing_pp_c3,C->c3, pairing);

        pairing_pp_apply(C->c4, params->g1, params->pairing_pp_g2);
    }
    else
        element_pairing(C->c4, params->g1, params->g2);
    element_pow_zn(C->c4, C->c4, r);
    pmesg_element(msg_verbose, "TEMPORAL RESULT", C->c4);
    element_mul(C->c4, C->c4, M);

    pmesg_element(msg_verbose, "r = ", r);
    pmesg_element(msg_verbose, "", C->c1);
    pmesg_element(msg_verbose, "", C->c2);
    pmesg_element(msg_verbose, "", C->c3);
    pmesg_element(msg_verbose, "", C->c4);

    element_clear(r);
    pmesg(msg_verbose, "END cbe_gamal_system_encrypt ...");
}

void cbe_gamal_system_decrypt(
    element_t M,
    cbe_gamal_sk_t sk,
    cbe_gamal_params_t params,
    cbe_gamal_C_t C,
    pairing_t pairing)
{
    pmesg(msg_verbose, "START cbe_gamal_system_decrypt ...");

    element_t tmp1, tmp2;

    element_init_GT(M, pairing);

    element_init_Zr(tmp1, pairing);
    element_init_G1(tmp2, pairing);
    element_invert(tmp1, sk->beta);

    if (precomputation)
        element_pp_pow_zn(tmp2, tmp1, C->pp_c2);
    else
        element_pow_zn(tmp2, C->c2, tmp1);

    if (pairing_pp)
        pairing_pp_apply(M, tmp2, params->pairing_pp_g2);
    else
        element_pairing(M, tmp2, params->g2);
    element_div(M, C->c4, M);

    element_clear(tmp1);
    element_clear(tmp2);

    pmesg_element(msg_verbose, "", M);

    pmesg(msg_verbose, "END cbe_gamal_system_decrypt ...");
}

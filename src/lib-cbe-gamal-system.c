#include "lib-cbe-gamal-system.h"

void cbe_gamal_clear(
    cbe_gamal_params_t params,
    cbe_gamal_pk_t pk,
    cbe_gamal_sk_t sk,
    cbe_gamal_C_t C)
{
    pmesg(msg_very_verbose, "START cbe_gamal_clear ...");

    shared_params_clear(params);
    clear_cbe_gamal_pk_t(pk);
    clear_cbe_gamal_sk_t(sk);
    clear_cbe_gamal_C_t(C);

    pmesg(msg_very_verbose, "END cbe_gamal_clear ...");
}

void cbe_gamal_system_setup(
    cbe_gamal_params_t params,
    pairing_t pairing,
    options optn)
{
    pmesg(msg_very_verbose, "START cbe_gamal_system_setup ...");

    element_t a;
    element_init_Zr(a, pairing);
    element_random(a);
    pmesg_element(msg_verbose, "alpha = ", a);

    if (optn.precompute_parameters)
        shared_params_setup(params, a, pairing);

    pmesg(msg_very_verbose, "END cbe_gamal_system_setup ...");
}

void cbe_gamal_system_keygen(
    cbe_gamal_sk_t sk,
    cbe_gamal_pk_t pk,
    cbe_gamal_params_t params,
    pairing_t pairing)
{
    pmesg(msg_very_verbose, "END cbe_gamal_system_keygen ...");

    assert(sk);
    assert(pk);
    assert(params);
    assert(pairing);

    init_cbe_gamal_pk_t(pk, pairing);
    init_cbe_gamal_sk_t(sk, pairing);

    element_random(sk->theta);
    element_random(sk->beta);
    element_random(sk->delta);
    element_pow_zn(pk->g3, params->g, sk->theta);
    element_pow_zn(pk->g4, params->g1, sk->beta);
    element_pow_zn(pk->g5, params->h, sk->delta);

    pmesg_element(msg_verbose, "", sk->theta);
    pmesg_element(msg_verbose, "", sk->beta);
    pmesg_element(msg_verbose, "", sk->delta);
    pmesg_element(msg_verbose, "", pk->g3);
    pmesg_element(msg_verbose, "", pk->g4);
    pmesg_element(msg_verbose, "", pk->g5);

    pmesg(msg_very_verbose, "END cbe_gamal_system_keygen ...");
}

void cbe_gamal_system_encrypt(
    cbe_gamal_C_t C,
    cbe_gamal_pk_t pk,
    cbe_gamal_params_t params,
    element_t M,
    pairing_t pairing)
{
    pmesg(msg_very_verbose, "START cbe_gamal_system_encrypt ...");

    assert(C);
    assert(pk);
    assert(params);
    assert(M);

    element_t r;

    element_init_Zr(r, pairing);
    init_cbe_gamal_C_t(C, pairing);

    element_random(r);
    element_pow_zn(C->c1, pk->g3, r);
    element_pow_zn(C->c2, pk->g4, r);
    element_pow_zn(C->c3, pk->g5, r);

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
    pmesg(msg_very_verbose, "END cbe_gamal_system_encrypt ...");
}

void cbe_gamal_system_decrypt(
    element_t M,
    cbe_gamal_sk_t sk,
    cbe_gamal_params_t params,
    cbe_gamal_C_t C,
    pairing_t pairing)
{
    pmesg(msg_very_verbose, "START cbe_gamal_system_decrypt ...");

    element_t tmp1, tmp2;

    element_init_GT(M, pairing);

    element_init_Zr(tmp1, pairing);
    element_init_G1(tmp2, pairing);
    element_invert(tmp1, sk->beta);

    element_pow_zn(tmp2, C->c2, tmp1);
    element_pairing(M, tmp2, params->g2);
    element_div(M, C->c4, M);

    element_clear(tmp1);
    element_clear(tmp2);

    pmesg_element(msg_verbose, "", M);

    pmesg(msg_very_verbose, "END cbe_gamal_system_decrypt ...");
}

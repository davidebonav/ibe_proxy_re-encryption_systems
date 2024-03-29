#include "lib-bb-ibe-system.h"

void bb_ibe_clear(
    bb_ibe_params_t params,
    bb_ibe_mk_t mk,
    bb_ibe_skID_t sk,
    bb_ibe_C_t C)
{
    pmesg(msg_verbose, "START bb_ibe_clear ...");

    shared_params_clear(params);
    clear_bb_ibe_mk_t(mk);
    clear_bb_ibe_skID_t(sk);
    clear_bb_ibe_C_t(C);

    pmesg(msg_verbose, "END bb_ibe_clear ...");
}

void bb_ibe_system_setup(
    bb_ibe_params_t params,
    bb_ibe_mk_t mk,
    pairing_t pairing)
{
    pmesg(msg_verbose, "START bb_ibe_system_setup ...");

    element_t a;
    element_init_Zr(a, pairing);
    element_random(a);
    pmesg_element(msg_verbose, "theta = ", a);

    if (compute_parameters)
        shared_params_setup(params, a, pairing);

    init_bb_ibe_mk_t(mk, pairing);
    if (precomputation)
        element_pp_pow_zn(mk->mk, a, params->pp_g2);
    else
        element_pow_zn(mk->mk, params->g2, a);

    element_set(mk->alpha, a);
    
    pmesg_element(msg_verbose, "", mk->mk);
    pmesg_element(msg_verbose, "", mk->alpha);

    element_clear(a);
    pmesg(msg_verbose, "END bb_ibe_system_setup ...");
}

void bb_ibe_system_keygen(
    bb_ibe_skID_t skID,
    bb_ibe_params_t params,
    bb_ibe_mk_t mk,
    element_t ID,
    pairing_t pairing)
{
    pmesg(msg_verbose, "END bb_ibe_system_keygen ...");

    element_t u;

    init_bb_ibe_skID_t(skID, pairing);

    element_init_Zr(u, pairing);
    element_random(u);

    if (precomputation)
        element_pp_pow_zn(skID->d0, ID, params->pp_g1);
    else
        element_pow_zn(skID->d0, params->g1, ID);
    element_mul(skID->d0, skID->d0, params->h);
    element_pow_zn(skID->d0, skID->d0, u);
    element_mul(skID->d0, skID->d0, mk->mk);
    if (precomputation)
    {
        element_pp_init(skID->pp_d0, skID->d0);
        element_pp_pow_zn(skID->d1, u, params->pp_g);
    }
    else
        element_pow_zn(skID->d1, params->g, u);

    if (pairing_pp)
    {
        pairing_pp_init(skID->pairing_pp_d0, skID->d0, pairing);
        pairing_pp_init(skID->pairing_pp_d1, skID->d1, pairing);
    }

    pmesg_element(msg_verbose, "u = ", u);
    pmesg_element(msg_verbose, "", skID->d0);
    pmesg_element(msg_verbose, "", skID->d1);

    element_clear(u);
    pmesg(msg_verbose, "END bb_ibe_system_keygen ...");
}

void bb_ibe_system_encrypt(
    bb_ibe_C_t C,
    element_t ID,
    bb_ibe_params_t params,
    element_t M,
    pairing_t pairing)
{
    pmesg(msg_verbose, "START bb_ibe_system_encrypt ...");

    element_t r;

    element_init_Zr(r, pairing);
    init_bb_ibe_C_t(C, pairing);

    element_random(r);
    if (precomputation)
    {
        element_pp_pow_zn(C->c1, r, params->pp_g);
        element_pp_pow_zn(C->c2, ID, params->pp_g1);
    }
    else
    {
        element_pow_zn(C->c1, params->g, r);
        element_pow_zn(C->c2, params->g1, ID);
    }
    element_mul(C->c2, C->c2, params->h);
    element_pow_zn(C->c2, C->c2, r);

    if (pairing_pp)
        pairing_pp_apply(C->c3, params->g1, params->pairing_pp_g2);
    else
        element_pairing(C->c3, params->g1, params->g2);
    element_pow_zn(C->c3, C->c3, r);
    element_mul(C->c3, C->c3, M);

    pmesg_element(msg_verbose, "r = ", r);
    pmesg_element(msg_verbose, "", C->c1);
    pmesg_element(msg_verbose, "", C->c2);
    pmesg_element(msg_verbose, "", C->c3);

    element_clear(r);
    pmesg(msg_verbose, "END bb_ibe_system_encrypt ...");
}

void bb_ibe_system_decrypt(
    element_t M,
    bb_ibe_skID_t sk,
    bb_ibe_C_t C,
    bb_ibe_params_t params,
    pairing_t pairing)
{
    pmesg(msg_verbose, "START bb_ibe_system_decrypt ...");

    element_t tmp1, tmp2;

    element_init_GT(M, pairing);

    element_init_GT(tmp1, pairing);
    element_init_GT(tmp2, pairing);

    if (pairing_pp)
    {
        pairing_pp_apply(tmp1, C->c2, sk->pairing_pp_d1);
        pairing_pp_apply(tmp2, C->c1, sk->pairing_pp_d0);
    }
    else
    {
        element_pairing(tmp1, sk->d1, C->c2);
        element_pairing(tmp2, sk->d0, C->c1);
    }

    element_mul(tmp1, tmp1, C->c3);

    element_div(M, tmp1, tmp2);

    element_clear(tmp1);
    element_clear(tmp2);

    pmesg_element(msg_verbose, "", M);

    pmesg(msg_verbose, "END bb_ibe_system_decrypt ...");
}

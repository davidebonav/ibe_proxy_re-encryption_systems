#include "lib-ibe-reenc-system.h"

void ibe_reenc_clear(
    reenc_eID_t eID,
    ibe_reenc_rkID_t rkID,
    ibe_reenc_skR_t skR)
{
    pmesg(msg_verbose, "START ibe_reenc_clear ...");
    clear_reenc_eID_t(eID);
    clear_ibe_reenc_rkID_t(rkID);
    clear_ibe_reenc_skR_t(skR);
    pmesg(msg_verbose, "END ibe_reenc_clear ...");
}

void ibe_reenc_system_egen(
    reenc_eID_t eID,
    bb_ibe_skID_t skID,
    pairing_t pairing)
{
    pmesg(msg_verbose, "START ibe_reenc_system_egen ...");
    init_reenc_eID_t(eID, pairing);
    element_set(eID->eID, skID->d1);

    if (precomputation)
        element_pp_init(eID->pp_eID, eID->eID);

    pmesg_element(msg_verbose, "", eID->eID);
    pmesg(msg_verbose, "END ibe_reenc_system_egen ...");
}

void ibe_reenc_system_keygen_rkg(
    ibe_reenc_skR_t skR,
    bb_ibe_mk_t mk,
    ibe_reenc_params_t params,
    pairing_t pairing)
{
    pmesg(msg_verbose, "START ibe_reenc_system_keygen_rkg ...");
    init_ibe_reenc_skR_t(skR, pairing);
    element_set(skR->alpha, mk->alpha);
    pmesg_element(msg_verbose, "", skR->alpha);
    pmesg(msg_verbose, "END ibe_reenc_system_keygen_rkg ...");
}

void ibe_reenc_system_keygen_pro(
    ibe_reenc_rkID_t rkID,
    ibe_reenc_skR_t skR,
    reenc_eID_t eID1,
    ibe_reenc_params_t params,
    element_t ID,
    element_t ID1,
    pairing_t pairing)
{
    pmesg(msg_verbose, "START ibe_reenc_system_keygen_pro ...");

    init_ibe_reenc_rkID_t(rkID, pairing);

    if (precomputation)
        element_pp_pow_zn(rkID->g_u_a, skR->alpha, eID1->pp_eID);
    else
        element_pow_zn(rkID->g_u_a, eID1->eID, skR->alpha);

    if (pairing_pp)
        pairing_pp_init(rkID->pairing_pp_g_u_a, rkID->g_u_a, pairing);

    element_set(rkID->ID, ID);
    element_set(rkID->ID1, ID1);

    pmesg_element(msg_verbose, "", rkID->ID);
    pmesg_element(msg_verbose, "", rkID->ID1);
    pmesg_element(msg_verbose, "", rkID->g_u_a);

    pmesg(msg_verbose, "END ibe_reenc_system_keygen_pro ...");
}

void ibe_reenc_system_reenc(
    bb_ibe_C_t C_ID1,
    ibe_reenc_rkID_t rkID,
    ibe_reenc_params_t params,
    bb_ibe_C_t C_ID,
    // element_t ID,
    // element_t ID1,
    pairing_t pairing)
{
    pmesg(msg_verbose, "START ibe_reenc_system_reenc ...");

    element_t tmp, tmp2;

    element_init_Zr(tmp, pairing);
    element_init_G1(tmp2, pairing);

    init_bb_ibe_C_t(C_ID1, pairing);

    element_set(C_ID1->c1, C_ID->c1);
    element_set(C_ID1->c2, C_ID->c2);

    element_sub(tmp, rkID->ID1, rkID->ID);
    // if (precomputation)
    //     element_pp_pow_zn(tmp2, tmp, C_ID->pp_c1);
    // else
    element_pow_zn(tmp2, C_ID->c1, tmp);

    if (pairing_pp)
        pairing_pp_apply(C_ID1->c3, tmp2, rkID->pairing_pp_g_u_a);
    else
        element_pairing(C_ID1->c3, rkID->g_u_a, tmp2);

    element_mul(C_ID1->c3, C_ID->c3, C_ID1->c3);

    pmesg_element(msg_verbose, "", C_ID1->c1);
    pmesg_element(msg_verbose, "", C_ID1->c2);
    pmesg_element(msg_verbose, "", C_ID1->c3);

    element_clear(tmp);
    element_clear(tmp2);

    pmesg(msg_verbose, "END ibe_reenc_system_reenc ...");
}

int ibe_reenc_system_check(
    ibe_reenc_params_t params,
    bb_ibe_C_t C_ID,
    element_t ID,
    pairing_t pairing)
{

    element_t v0, v1, tmp;
    int output;

    element_init_GT(v0, pairing);
    element_init_GT(v1, pairing);
    element_init_G1(tmp, pairing);

    // if (precomputation)
    //     element_pp_pow(tmp, ID, params->pairing_pp_g1);
    // else
    element_pow_zn(tmp, params->g1, ID);
    element_mul(tmp, tmp, params->h);
    pairing_apply(v0, tmp, C_ID->c1, pairing);

    // if (pairing_pp)
    //     pairing_pp_apply(v1, C_ID->c2, params->pairing_pp_g);
    // else
    element_pairing(v1, C_ID->c2, params->g);

    pmesg_element(msg_verbose, "", v0);
    pmesg_element(msg_verbose, "", v1);

    output = !element_cmp(v0, v1);

    element_clear(v0);
    element_clear(v1);

    return output;
}
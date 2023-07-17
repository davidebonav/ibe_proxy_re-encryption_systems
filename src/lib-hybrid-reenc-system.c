#include "lib-hybrid-reenc-system.h"

void hybrid_reenc_clear(
    hybrid_reenc_eID_t eID,
    hybrid_reenc_rkID_t rkID)
{
    pmesg(msg_very_verbose, "START hybrid_reenc_clear ...");
    if (eID)
        element_clear(eID->eID);

    if (rkID)
    {
        element_clear(rkID->delta);
        element_clear(rkID->g_u_b);
        element_clear(rkID->theta);
    }
    pmesg(msg_very_verbose, "END hybrid_reenc_clear ...");
}

void hybrid_reenc_system_egen(
    hybrid_reenc_eID_t eID,
    bb_ibe_skID_t skID,
    pairing_t pairing)
{
    pmesg(msg_very_verbose, "START hybrid_reenc_system_egen ...");
    init_hybrid_reenc_eID_t(eID,pairing);
    element_set(eID->eID, skID->d1);
    pmesg_element(msg_verbose, "", eID->eID);
    pmesg(msg_very_verbose, "END hybrid_reenc_system_egen ...");
}

void hybrid_reenc_system_keygen_pro(
    hybrid_reenc_rkID_t rkID,
    cbe_gamal_sk_t sk,
    hybrid_reenc_eID_t eID,
    hybrid_reenc_params_t params,
    pairing_t pairing)
{
    pmesg(msg_very_verbose, "START hybrid_reenc_system_keygen_pro ...");

    element_t tmp;

    element_init_Zr(tmp, pairing);

    init_hybrid_reenc_rkID_t(rkID,pairing);

    element_set(rkID->theta, sk->theta);
    element_set(rkID->delta, sk->delta);

    element_invert(tmp, sk->beta);
    element_pow_zn(rkID->g_u_b, eID->eID, tmp);

    pmesg_element(msg_verbose, "", rkID->theta);
    pmesg_element(msg_verbose, "", rkID->g_u_b);
    pmesg_element(msg_verbose, "", rkID->delta);

    element_clear(tmp);

    pmesg(msg_very_verbose, "END hybrid_reenc_system_keygen_pro ...");
}

void hybrid_reenc_system_reenc(
    bb_ibe_C_t C_ID,
    hybrid_reenc_rkID_t rkID,
    hybrid_reenc_params_t params,
    cbe_gamal_C_t C_PK,
    element_t ID,
    pairing_t pairing)
{
    pmesg(msg_very_verbose, "START hybrid_reenc_system_reenc ...");

    element_t tmp, tmp2;

    element_init_Zr(tmp, pairing);
    element_init_G1(tmp2, pairing);

    init_bb_ibe_C_t(C_ID,pairing);

    element_invert(tmp, rkID->theta);
    element_pow_zn(C_ID->c1, C_PK->c1, tmp);

    element_invert(tmp, rkID->delta);
    element_pow_zn(C_ID->c2, C_PK->c3, tmp);

    element_pow_zn(tmp2, C_PK->c2, ID);
    element_pairing(C_ID->c3, rkID->g_u_b, tmp2);
    element_mul(C_ID->c3, C_PK->c4, C_ID->c3);

    pmesg_element(msg_verbose, "", C_ID->c1);
    pmesg_element(msg_verbose, "", C_ID->c2);
    pmesg_element(msg_verbose, "", C_ID->c3);

    element_clear(tmp);
    element_clear(tmp2);

    pmesg(msg_very_verbose, "END hybrid_reenc_system_reenc ...");
}

int hybrid_reenc_system_check(
    hybrid_reenc_params_t params,
    cbe_gamal_C_t C_PK,
    cbe_gamal_pk_t pk,
    pairing_t pairing)
{

    element_t v1, v2, v3, v4;
    int output;

    element_init_GT(v1, pairing);
    element_init_GT(v2, pairing);
    element_init_GT(v3, pairing);
    element_init_GT(v4, pairing);

    element_pairing(v1, C_PK->c1, pk->g4);
    element_pairing(v2, C_PK->c2, pk->g3);
    element_pairing(v3, C_PK->c2, pk->g5);
    element_pairing(v4, C_PK->c3, pk->g4);

    pmesg_element(msg_verbose, "", v1);
    pmesg_element(msg_verbose, "", v2);
    pmesg_element(msg_verbose, "", v3);
    pmesg_element(msg_verbose, "", v4);

    output = !(element_cmp(v1, v2) & element_cmp(v3, v4));

    element_clear(v1);
    element_clear(v2);
    element_clear(v3);
    element_clear(v4);

    return output;
}
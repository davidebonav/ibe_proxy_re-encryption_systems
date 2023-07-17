#include <stdio.h>
#include <nettle/ecc.h>
#include <nettle/ecc-curve.h>
#include <gmp.h>

#include "lib-mesg.h"
#include "lib-hybrid-reenc-system.h"
#include "lib-shared.h"

int main()
{
    set_messaging_level(msg_very_verbose);

    pairing_t pairing;
    hybrid_reenc_params_t params;

    cbe_gamal_pk_t pk;
    cbe_gamal_sk_t sk;
    cbe_gamal_C_t C;

    bb_ibe_skID_t skID;
    bb_ibe_mk_t mk;
    bb_ibe_C_t C_ID;

    hybrid_reenc_eID_t eID;
    hybrid_reenc_rkID_t rkID;

    element_t M, M1, ID;

    shared_pairing_init(pairing, pbc_pairing_type_a, 90);

    element_init_GT(M, pairing);
    element_init_Zr(ID, pairing);
    element_random(M);
    element_random(ID);
    pmesg_element(msg_verbose, "", M);
    pmesg_element(msg_verbose, "", ID);

    // ELGAMAL SETUP
    options opt1 = {true};
    cbe_gamal_system_setup(params, pairing, opt1);
    cbe_gamal_system_keygen(sk, pk, params, pairing);
    cbe_gamal_system_encrypt(C, pk, params, M, pairing);

    // BB-IBE SETUP
    options opt2 = {false};
    bb_ibe_system_setup(params, mk, pairing, opt2);
    bb_ibe_system_keygen(skID, params, mk, ID, pairing);
 
    // PROXY SETUP
    hybrid_reenc_system_egen(eID, skID, pairing);
    hybrid_reenc_system_keygen_pro(rkID, sk, eID, params, pairing);
    pmesg(msg_silence, "Check crittotesto %d", hybrid_reenc_system_check(params, C, pk, pairing));
    hybrid_reenc_system_reenc(C_ID, rkID, params, C, ID, pairing);

    bb_ibe_system_decrypt(M1, skID, C_ID, params, pairing);
    pmesg_element(msg_verbose, "", M1);

    if (element_cmp(M, M1) == 0)
        pmesg(msg_silence, "The system works correctly, the two elements are equal");
    else
        pmesg(msg_silence, "Some error occurs...");

    cbe_gamal_clear(params, pk, sk, C);
    bb_ibe_clear(NULL, mk, skID, C_ID);
    hybrid_reenc_clear(eID, rkID);
    element_clear(M);
    element_clear(M1);
    element_clear(ID);

    pairing_clear(pairing);
    return 0;
}
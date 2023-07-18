#include <stdio.h>
#include <nettle/ecc.h>
#include <nettle/ecc-curve.h>
#include <gmp.h>

#include "lib-mesg.h"
#include "lib-hybrid-reenc-system.h"
#include "lib-shared.h"

int main()
{
    set_messaging_level(msg_normal);

    pairing_t pairing;
    hybrid_reenc_params_t params;

    element_t M;

    shared_pairing_init(pairing, pbc_pairing_type_a, 90);

    element_init_GT(M, pairing);
    element_random(M);
    pmesg_element(msg_normal, "Messaggio generato", M);

    // INIT BB-IBE
    element_t ID;
    bb_ibe_mk_t mkID;
    bb_ibe_skID_t skID;
    bb_ibe_C_t ct_ID;

    element_init_Zr(ID, pairing);
    element_random(ID);
    pmesg_element(msg_normal, "Identità IBE", ID);

    compute_parameters = true;
    bb_ibe_system_setup(params, mkID, pairing);
    bb_ibe_system_keygen(skID, params, mkID, ID, pairing);

    // ****************************** TEST BB-IBE
    element_t m1_ID;
    bb_ibe_system_encrypt(ct_ID, ID, params, M, pairing);
    bb_ibe_system_decrypt(m1_ID, skID, ct_ID, params, pairing);

    pmesg_element(msg_normal, "", m1_ID);

    if (element_cmp(M, m1_ID) == 0)
        pmesg(msg_silence, "The system works correctly, the two elements are equal");
    else
    {
        pmesg(msg_silence, "Some error occurs...");
        exit(1);
    }
    element_clear(m1_ID);
    clear_bb_ibe_C_t(ct_ID);
    // ******************************
    // INIT CBE-EL-GAMAL
    cbe_gamal_pk_t pk;
    cbe_gamal_sk_t sk;
    cbe_gamal_C_t C;

    compute_parameters = false;
    cbe_gamal_system_setup(params, pairing);
    cbe_gamal_system_keygen(sk, pk, params, pairing);

    // ****************************** TEST CBE-EL-GAMAL
    element_t M1;

    cbe_gamal_system_encrypt(C, pk, params, M, pairing);
    cbe_gamal_system_decrypt(M1, sk, params, C, pairing);

    pmesg_element(msg_normal, "", M1);

    if (element_cmp(M, M1) == 0)
        pmesg(msg_silence, "The system works correctly, the two elements are equal");
    else
    {
        pmesg(msg_silence, "Some error occurs...");
        exit(1);
    }
    element_clear(M1);
    clear_cbe_gamal_C_t(C);
    // ******************************

    // TEST HYBRID
    hybrid_reenc_eID_t eID;
    hybrid_reenc_rkID_t rkID;

    hybrid_reenc_system_egen(eID, skID, pairing);
    hybrid_reenc_system_keygen_pro(rkID, sk, eID, params, pairing);

    // ****************************** TEST HYBRID
    element_t m_dec;

    cbe_gamal_system_encrypt(C, pk, params, M, pairing);

    if (hybrid_reenc_system_check(params, C, pk, pairing))
        pmesg(msg_silence, "Check crittotesto superato");
    else
    {
        pmesg(msg_silence, "Check crittotesto NON SUPERATO - ERROR");
        exit(1);
    }

    hybrid_reenc_system_reenc(ct_ID, rkID, params, C, ID, pairing);
    bb_ibe_system_decrypt(m_dec, skID, ct_ID, params, pairing);
    pmesg_element(msg_normal, "", m_dec);

    if (element_cmp(M, m_dec) == 0)
        pmesg(msg_silence, "The system works correctly, the two elements are equal");
    else
        {pmesg(msg_silence, "Some error occurs...");exit(1);}
    
    element_clear(m_dec);
    // ******************************

    bb_ibe_clear(params, mkID, skID, ct_ID);
    cbe_gamal_clear(NULL, pk, sk, C);
    hybrid_reenc_clear(eID, rkID);
    element_clear(M);
    element_clear(ID);

    pairing_clear(pairing);
    return 0;
}
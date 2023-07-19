#include <stdio.h>
#include <gmp.h>

#include "lib-mesg.h"
#include "lib-ibe-reenc-system.h"
#include "lib-shared.h"

int main()
{
    set_messaging_level(msg_verbose);

    pairing_t pairing;
    ibe_reenc_params_t params;

    element_t M;

    shared_pairing_init(pairing, pbc_pairing_type_a, 90);

    element_init_GT(M, pairing);
    element_random(M);
    pmesg_element(msg_normal, "Messaggio generato", M);

    // BB-IBE
    element_t ID, ID1;
    bb_ibe_mk_t mk;
    bb_ibe_skID_t skID, skID1;
    bb_ibe_C_t ct_ID, ct_ID1;

    // IBE REENC
    reenc_eID_t eID1;
    ibe_reenc_rkID_t rkID;
    ibe_reenc_skR_t skR;

    compute_parameters = true;
    bb_ibe_system_setup(params, mk, pairing);

    element_init_Zr(ID, pairing);
    element_random(ID);
    pmesg_element(msg_normal, "Identità IBE", ID);
    bb_ibe_system_keygen(skID, params, mk, ID, pairing);

    element_init_Zr(ID1, pairing);
    element_random(ID1);
    pmesg_element(msg_normal, "Identità IBE", ID1);
    bb_ibe_system_keygen(skID1, params, mk, ID1, pairing);

    bb_ibe_system_encrypt(ct_ID, ID, params, M, pairing);

    // ******************************

    if (ibe_reenc_system_check(params, ct_ID, ID, pairing))
        pmesg(msg_silence, "Check crittotesto superato");
    else
    {
        pmesg(msg_silence, "Check crittotesto NON SUPERATO - ERROR");
        exit(1);
    }

    ibe_reenc_system_keygen_rkg(skR, mk, params, pairing);

    ibe_reenc_system_egen(eID1, skID1, pairing);
    ibe_reenc_system_keygen_pro(rkID, skR, eID1, params, ID, ID1, pairing);
    ibe_reenc_system_reenc(ct_ID1, rkID, params, ct_ID, pairing);

    element_t m_dec;
    bb_ibe_system_decrypt(m_dec, skID1, ct_ID1, params, pairing);
    pmesg_element(msg_normal, "", m_dec);

    if (element_cmp(M, m_dec) == 0)
        pmesg(msg_silence, "The system works correctly, the two elements are equal");
    else
    {
        pmesg(msg_silence, "Some error occurs...");
        exit(1);
    }
    
    element_clear(m_dec);
    bb_ibe_clear(params, mk, skID, ct_ID);
    bb_ibe_clear(NULL, NULL, skID1, ct_ID1);
    ibe_reenc_clear(eID1, rkID, skR);
    element_clear(M);
    element_clear(ID);
    element_clear(ID1);

    pairing_clear(pairing);
    return 0;
}
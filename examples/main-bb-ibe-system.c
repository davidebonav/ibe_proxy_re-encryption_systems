#include <stdio.h>
#include <nettle/ecc.h>
#include <nettle/ecc-curve.h>
#include <gmp.h>

#include "lib-mesg.h"
#include "lib-bb-ibe-system.h"
#include "lib-shared.h"

int main()
{
    set_messaging_level(msg_normal);

    pairing_t pairing;

    options optn = {true};

    bb_ibe_params_t params;
    bb_ibe_mk_t mk;
    bb_ibe_skID_t sk;
    bb_ibe_C_t C;

    element_t M, M1, ID;

    shared_pairing_init(pairing, pbc_pairing_type_a, 90);

    element_init_Zr(ID, pairing);
    element_init_GT(M, pairing);

    element_random(ID);
    element_random(M);
    pmesg_element(msg_normal, "", ID);
    pmesg_element(msg_normal, "", M);

    bb_ibe_system_setup(params, mk, pairing, optn);
    bb_ibe_system_keygen(sk, params, mk, ID, pairing);
    bb_ibe_system_encrypt(C, ID, params, M, pairing);
    bb_ibe_system_decrypt(M1, sk, C, params, pairing);

    pmesg_element(msg_normal, "", M1);

    if (element_cmp(M, M1) == 0)
        pmesg(msg_silence, "The system works correctly, the two elements are equal");
    else
        pmesg(msg_silence, "Some error occurs...");

    bb_ibe_clear(params, mk, sk, C);
    element_clear(M);
    element_clear(M1);
    element_clear(ID);

    pairing_clear(pairing);
    return 0;
}
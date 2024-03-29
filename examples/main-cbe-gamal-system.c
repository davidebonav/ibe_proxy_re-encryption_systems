#include <stdio.h>

#include "lib-mesg.h"
#include "lib-cbe-gamal-system.h"
#include "lib-shared.h"

int main()
{
    set_messaging_level(msg_normal);

    pairing_t pairing;

    compute_parameters = true;

    cbe_gamal_params_t params;
    cbe_gamal_pk_t pk;
    cbe_gamal_sk_t sk;
    cbe_gamal_C_t C;

    element_t M, M1;

    shared_pairing_init(pairing, pbc_pairing_type_a, 90);

    element_init_GT(M, pairing);
    element_random(M);
    pmesg_element(msg_normal, "", M);

    cbe_gamal_system_setup(params, pairing);
    cbe_gamal_system_keygen(sk, pk, params, pairing);
    cbe_gamal_system_encrypt(C, pk, params, M, pairing);
    cbe_gamal_system_decrypt(M1, sk, params, C, pairing);

    pmesg_element(msg_normal, "", M1);

    if (element_cmp(M, M1) == 0)
        pmesg(msg_silence, "The system works correctly, the two elements are equal");
    else
        pmesg(msg_silence, "Some error occurs...");

    cbe_gamal_clear(params, pk, sk, C);
    element_clear(M);
    element_clear(M1);

    pairing_clear(pairing);
    return 0;
}
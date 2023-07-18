#include <stdio.h>

#include "lib-mesg.h"
#include "lib-shared.h"
#include "lib-custom-types.h"
#include "lib-cbe-gamal-system.h"

#define sampling_period 5 /* secondi */
#define max_samples (sampling_period * 1000)

int main(int argc, char *argv[])
{
    pairing_t pairing;
    cbe_gamal_params_t params;
    cbe_gamal_pk_t pk;
    cbe_gamal_sk_t sk;
    cbe_gamal_C_t C;
    element_t M, M1;
    stats_t stats;
    elapsed_time_t elapsed_time;

    parse_input(argc, argv);

    set_messaging_level(msg_silence);
    compute_parameters = true;
    shared_pairing_init(pairing, pbc_pairing_type_a, 90);

    element_init_GT(M, pairing);
    element_random(M);

    printf("\nCalibration tools for stats...\n");
    calibrate_timing_methods();

    printf("\nSetUp...\n");
    perform_oneshot_cpu_time_sampling(elapsed_time, tu_millis, {
        cbe_gamal_system_setup(params, pairing);
    });
    printf_et(" cbe_gamal_system_setup: ", elapsed_time, tu_millis, "\n");

    printf("\nKeyGen...\n");
    perform_oneshot_cpu_time_sampling(elapsed_time, tu_millis, {
        cbe_gamal_system_keygen(sk, pk, params, pairing);
    });
    printf_et(" cbe_gamal_system_keygen: ", elapsed_time, tu_millis, "\n");

    printf("\nEncryption...\n");
    perform_wc_time_sampling_period(
        stats, sampling_period, max_samples, tu_millis,
        {
            cbe_gamal_system_encrypt(C, pk, params, M, pairing);
            clear_cbe_gamal_C_t(C);
        },
        {});
    printf_stats(" cbe_gamal_system_encrypt: ", stats, "");
    cbe_gamal_system_encrypt(C, pk, params, M, pairing);

    printf("\nDecryption...\n");
    perform_wc_time_sampling_period(
        stats, sampling_period, max_samples, tu_millis,
        {
            cbe_gamal_system_decrypt(M1, sk, params, C, pairing);
            element_clear(M1);
        },
        {});
    printf_stats(" cbe_gamal_system_decrypt: ", stats, "");
    cbe_gamal_system_decrypt(M1, sk, params, C, pairing);

    pmesg_element(msg_normal, "", M1);

    if (element_cmp(M, M1) == 0)
        pmesg(msg_silence, "The system works correctly");
    else
        pmesg(msg_silence, "Some error occurs...");

    cbe_gamal_clear(params, pk, sk, C);
    element_clear(M);
    element_clear(M1);

    pairing_clear(pairing);
    return 0;
}
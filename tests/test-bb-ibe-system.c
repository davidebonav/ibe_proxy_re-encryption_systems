#include <stdio.h>

#include "lib-mesg.h"
#include "lib-shared.h"
#include "lib-custom-types.h"
#include "lib-bb-ibe-system.h"

#define sampling_period 5 /* secondi */
#define max_samples (sampling_period * 1000)

int main(int argc,  char *argv[])
{
    pairing_t pairing;
    bb_ibe_params_t params;
    bb_ibe_mk_t mk;
    bb_ibe_skID_t sk;
    bb_ibe_C_t C;
    element_t M, M1, ID;
    stats_t stats;
    elapsed_time_t elapsed_time;

    parse_input(argc, argv);

    set_messaging_level(msg_silence);
    compute_parameters = true;
    shared_pairing_init(pairing, type, sec_level);

    element_init_Zr(ID, pairing);
    element_init_GT(M, pairing);
    element_random(ID);
    element_random(M);

    printf("\nCalibration tools for stats...\n");
    calibrate_timing_methods();

    printf("\nSetUp...\n");
    perform_oneshot_cpu_time_sampling(elapsed_time, tu_millis, {
        bb_ibe_system_setup(params, mk, pairing);
    });
    printf_et(" bb_ibe_system_setup: ", elapsed_time, tu_millis, "\n");

    printf("\nKeyGen...\n");
    perform_oneshot_cpu_time_sampling(elapsed_time, tu_millis, {
        bb_ibe_system_keygen(sk, params, mk, ID, pairing);
    });
    printf_et(" bb_ibe_system_keygen: ", elapsed_time, tu_millis, "\n");

    printf("\nEncryption...\n");
    perform_wc_time_sampling_period(
        stats, sampling_period, max_samples, tu_millis,
        {
            bb_ibe_system_encrypt(C, ID, params, M, pairing);
            clear_bb_ibe_C_t(C);
        },
        {});
    printf_stats(" bb_ibe_system_encrypt: ", stats, "");
    bb_ibe_system_encrypt(C, ID, params, M, pairing);

    printf("\nDecryption...\n");
    perform_wc_time_sampling_period(
        stats, sampling_period, max_samples, tu_millis,
        {
            bb_ibe_system_decrypt(M1, sk, C, params, pairing);
            element_clear(M1);
        },
        {});
    printf_stats(" bb_ibe_system_decrypt: ", stats, "");
    // printf_short_stats(" bb_ibe_system_decrypt", stats, "");
    bb_ibe_system_decrypt(M1, sk, C, params, pairing);

    if (element_cmp(M, M1) == 0)
        pmesg(msg_silence, "\nThe system works correctly");
    else
        pmesg(msg_silence, "\nSome error occurs...");

    bb_ibe_clear(params, mk, sk, C);
    element_clear(M);
    element_clear(M1);
    element_clear(ID);

    pairing_clear(pairing);
    return 0;
}
#include <stdio.h>

#include "lib-mesg.h"
#include "lib-shared.h"
#include "lib-custom-types.h"
#include "lib-hybrid-reenc-system.h"

#define sampling_period 5 /* secondi */
#define max_samples (sampling_period * 1000)

int main(int argc, char *argv[])
{
    pairing_t pairing;
    hybrid_reenc_params_t params;
    element_t M;
    // BB-IBE
    element_t ID;
    bb_ibe_mk_t mkID;
    bb_ibe_skID_t skID;
    bb_ibe_C_t ct_ID;
    // CBE-EL-GAMAL
    cbe_gamal_pk_t pk;
    cbe_gamal_sk_t sk;
    cbe_gamal_C_t C;
    // HYBRID-RE-ENC
    hybrid_reenc_eID_t eID;
    hybrid_reenc_rkID_t rkID;
    element_t m_dec;

    stats_t stats;
    elapsed_time_t elapsed_time;

    parse_input(argc, argv);

    set_messaging_level(msg_silence);
    shared_pairing_init(pairing, type, sec_level);

    element_init_GT(M, pairing);
    element_random(M);
    element_init_Zr(ID, pairing);
    element_random(ID);

    // BB - IBE
    compute_parameters = true;
    bb_ibe_system_setup(params, mkID, pairing);
    bb_ibe_system_keygen(skID, params, mkID, ID, pairing);

    // EL - GAMAL
    compute_parameters = false;
    cbe_gamal_system_setup(params, pairing);
    cbe_gamal_system_keygen(sk, pk, params, pairing);
    cbe_gamal_system_encrypt(C, pk, params, M, pairing);

    printf("Calibration tools for timing...\n");
    calibrate_timing_methods();

    // HYBRID
    printf("\nEGen...\n");
    perform_oneshot_cpu_time_sampling(elapsed_time, tu_millis, {
        hybrid_reenc_system_egen(eID, skID, pairing);
    });
    printf_et(" hybrid_reenc_system_egen: ", elapsed_time, tu_millis, "\n");

    printf("\nKeyGenPRO...\n");
    perform_oneshot_cpu_time_sampling(elapsed_time, tu_millis, {
        hybrid_reenc_system_keygen_pro(rkID, sk, eID, params, pairing);
    });
    printf_et(" hybrid_reenc_system_keygen_pro: ", elapsed_time, tu_millis, "\n");

    printf("\nCheck...\n");
    perform_wc_time_sampling_period(
        stats, sampling_period, max_samples, tu_millis,
        {
            hybrid_reenc_system_check(params, C, pk, pairing);
        },
        {});
    printf_stats(" hybrid_reenc_system_check: ", stats, "");

    printf("\nRe-Encryption...\n");
    perform_wc_time_sampling_period(
        stats, sampling_period, max_samples, tu_millis,
        {
            hybrid_reenc_system_reenc(ct_ID, rkID, params, C, ID, pairing);
            clear_bb_ibe_C_t(ct_ID);
        },
        {});
    printf_stats(" bb_ibe_system_encrypt: ", stats, "");
    hybrid_reenc_system_reenc(ct_ID, rkID, params, C, ID, pairing);

    bb_ibe_system_decrypt(m_dec, skID, ct_ID, params, pairing);

    if (element_cmp(M, m_dec) == 0)
        pmesg(msg_silence, "The system works correctly");
    else
    {
        pmesg(msg_silence, "Some error occurs...");
        exit(1);
    }

    element_clear(m_dec);
    bb_ibe_clear(params, mkID, skID, ct_ID);
    cbe_gamal_clear(NULL, pk, sk, C);
    hybrid_reenc_clear(eID, rkID);
    element_clear(M);
    element_clear(ID);

    pairing_clear(pairing);
    return 0;
}
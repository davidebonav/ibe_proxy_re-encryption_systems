#include <stdio.h>
#include <assert.h>

#include "lib-mesg.h"
#include "lib-timing.h"
#include "lib-shared.h"
#include "lib-custom-types.h"
#include "lib-ibe-reenc-system.h"

#define sampling_period 5 /* secondi */
#define max_samples (sampling_period * 1000)

int main(int argc, char *argv[])
{
    pairing_t pairing;
    ibe_reenc_params_t params;
    element_t M;
    // BB-IBE
    element_t ID, ID1;
    bb_ibe_mk_t mk;
    bb_ibe_skID_t skID, skID1;
    bb_ibe_C_t ct_ID, ct_ID1;
    // IBE REENC
    reenc_eID_t eID1;
    ibe_reenc_rkID_t rkID;
    ibe_reenc_skR_t skR;

    stats_t stats;
    elapsed_time_t elapsed_time;

    parse_input(argc, argv);

    set_messaging_level(msg_silence);
    shared_pairing_init(pairing, type, sec_level);

    compute_parameters = true;
    bb_ibe_system_setup(params, mk, pairing);

    element_init_GT(M, pairing);
    element_random(M);
    pmesg_element(msg_normal, "Messaggio generato", M);

    element_init_Zr(ID, pairing);
    element_random(ID);
    pmesg_element(msg_normal, "Identità IBE", ID);
    bb_ibe_system_keygen(skID, params, mk, ID, pairing);

    element_init_Zr(ID1, pairing);
    element_random(ID1);
    pmesg_element(msg_normal, "Identità IBE", ID1);
    bb_ibe_system_keygen(skID1, params, mk, ID1, pairing);

    bb_ibe_system_encrypt(ct_ID, ID, params, M, pairing);

    // **********************************************
    printf("Calibration tools for timing...\n");
    calibrate_timing_methods();

    printf("\nCheck...\n");
    perform_wc_time_sampling_period(
        stats, sampling_period, max_samples, tu_millis,
        {
            assert(ibe_reenc_system_check(params, ct_ID, ID, pairing) == 1);
        },
        {});
    printf_stats(" ibe_reenc_system_check: ", stats, "");

    printf("\nKeyGenRKG...\n");
    perform_oneshot_cpu_time_sampling(elapsed_time, tu_millis, {
        ibe_reenc_system_keygen_rkg(skR, mk, params, pairing);
    });
    printf_et(" ibe_reenc_system_keygen_rkg: ", elapsed_time, tu_millis, "\n");

    printf("\nEGen...\n");
    perform_oneshot_cpu_time_sampling(elapsed_time, tu_millis, {
        ibe_reenc_system_egen(eID1, skID1, pairing);
    });
    printf_et(" ibe_reenc_system_egen: ", elapsed_time, tu_millis, "\n");

    printf("\nKeyGenPRO...\n");
    perform_wc_time_sampling_period(
        stats, sampling_period, max_samples, tu_millis,
        {
            ibe_reenc_system_keygen_pro(rkID, skR, eID1, params, ID, ID1, pairing);
            clear_ibe_reenc_rkID_t(rkID);
        },
        {});
    printf_stats(" ibe_reenc_system_keygen_pro: ", stats, "");
    ibe_reenc_system_keygen_pro(rkID, skR, eID1, params, ID, ID1, pairing);

    printf("\nRe-Encryption...\n");
    perform_wc_time_sampling_period(
        stats, sampling_period, max_samples, tu_millis,
        {
            ibe_reenc_system_reenc(ct_ID1, rkID, params, ct_ID, pairing);
            clear_bb_ibe_C_t(ct_ID1);
        },
        {});
    printf_stats(" ibe_reenc_system_reenc: ", stats, "");
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
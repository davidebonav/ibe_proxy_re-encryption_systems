#include "lib-bb-ibe-system.h"

void bb_ibe_init(
    bb_ibe_systems_t bb_ibe_system,
    pbc_pairing_type_t pairing_type,
    unsigned int level)
{
    pmesg(msg_very_verbose, "START bb_ibe_init ...");

    assert(is_pairing_symmetric(pairing_type));
    assert(level);

    pbc_param_t pairing_param;
    if (pairing_type != pbc_pairing_type_a1)
        select_pbc_param_by_security_level(pairing_param, pairing_type, level, NULL);
    else
    {
        unsigned int mod_size =
            non_generic_dlog_secure_size_by_security_level(level);
        mpz_t p, q, n;
        mpz_inits(p, q, n, NULL);
        pbc_mpz_randomb(p, mod_size / (2 * 2));
        pbc_mpz_randomb(q, mod_size / (2 * 2));
        mpz_nextprime(p, p);
        mpz_nextprime(q, q);
        mpz_mul(n, p, q);
        select_pbc_param_by_security_level(pairing_param, pairing_type, level, n);
        mpz_clears(p, q, n, NULL);
    }
    pairing_init_pbc_param(bb_ibe_system->pairing, pairing_param);
    pbc_param_clear(pairing_param);

    assert(pairing_is_symmetric(bb_ibe_system->pairing));

    pmesg(msg_very_verbose, "END bb_ibe_init ...");
}

void bb_ibe_clear(bb_ibe_systems_t system, bb_ibe_params_t params, bb_ibe_mk_t mk)
{
    pmesg(msg_very_verbose, "START bb_ibe_clear ...");

    element_clear(mk->mk);

    element_clear(params->g);
    element_clear(params->g1);
    element_clear(params->g2);
    element_clear(params->h);

    pairing_clear(system->pairing);

    pmesg(msg_very_verbose, "END bb_ibe_clear ...");
}

void bb_ibe_system_setup(bb_ibe_params_t params, bb_ibe_mk_t mk, bb_ibe_systems_t system)
{
    pmesg(msg_very_verbose, "START bb_ibe_system_setup ...");

    element_init_G1(params->g2, system->pairing);
    element_random(params->g2);
    pmesg_element(msg_verbose, "", params->g2);

    element_init_G1(params->h, system->pairing);
    element_random(params->h);
    pmesg_element(msg_verbose, "", params->h);
    // element_printf("g = %B\n", params->g1);

    element_init_G1(params->g, system->pairing);
    pmesg(msg_normal, "TOFIXXXXXX");
    while (!element_is_generator(params->g, system->pairing))
        element_random(params->g);
    pmesg_element(msg_verbose, "", params->g);

    element_t a;
    element_init_Zr(a, system->pairing);
    element_random(a);
    pmesg_element(msg_verbose, "alpha = ", a);

    element_init_G1(params->g1, system->pairing);
    element_pow_zn(params->g1, params->g, a);
    pmesg_element(msg_verbose, "", params->g1);

    element_init_G1(mk->mk, system->pairing);
    element_pow_zn(mk->mk, params->g2, a);
    pmesg_element(msg_verbose, "", mk->mk);

    element_clear(a);
    pmesg(msg_very_verbose, "END bb_ibe_system_setup ...");
}

void bb_ibe_system_keygen(bb_ibe_skID_t skID, bb_ibe_params_t params, bb_ibe_mk_t mk, bb_ibe_systems_t system, element_t ID)
{
    pmesg(msg_very_verbose, "END bb_ibe_system_keygen ...");

    // element_init_G1(skID

    pmesg(msg_very_verbose, "END bb_ibe_system_keygen ...");
}
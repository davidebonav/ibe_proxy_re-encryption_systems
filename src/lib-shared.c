#include "lib-shared.h"

int shared_pairing_is_symmetric(pbc_pairing_type_t type)
{
    pmesg(msg_very_verbose, "START shared_pairing_is_symmetric ...");

    if (type == pbc_pairing_type_a || type == pbc_pairing_type_a1 || type == pbc_pairing_type_e)
        return 1;
    else
        return 0;
}

void shared_pairing_init(
    pairing_t pairing,
    pbc_pairing_type_t pairing_type,
    unsigned int level // this is the arameter k of the schemas
)
{
    pmesg(msg_very_verbose, "START shared_pairing_init ...");

    assert(shared_pairing_is_symmetric(pairing_type));
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
    pairing_init_pbc_param(pairing, pairing_param);
    pbc_param_clear(pairing_param);

    assert(pairing_is_symmetric(pairing));

    pmesg(msg_very_verbose, "END shared_pairing_init ...");
}

void shared_params_clear(shared_params_t params)
{
    pmesg(msg_very_verbose, "START shared_params_clear ...");

    if (params)
    {
        element_clear(params->g);
        element_clear(params->g1);
        element_clear(params->g2);
        element_clear(params->h);
    }

    pmesg(msg_very_verbose, "END shared_params_clear ...");
}

void shared_params_setup(shared_params_t params, element_t a, pairing_t pairing)
{
    pmesg(msg_very_verbose, "START shared_params_setup ...");

    assert(params);

    init_shared_params_t(params,pairing);

    element_random(params->g); // the order is prime, all the element are generator
    element_pow_zn(params->g1, params->g, a);
    element_random(params->g2);
    element_random(params->h);

    pmesg_element(msg_verbose, "", params->g);
    pmesg_element(msg_verbose, "", params->g1);
    pmesg_element(msg_verbose, "", params->g2);
    pmesg_element(msg_verbose, "", params->h);

    pmesg(msg_very_verbose, "END shared_params_setup ...");
}

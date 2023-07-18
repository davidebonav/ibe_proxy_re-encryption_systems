#include "lib-shared.h"

int shared_pairing_is_symmetric(pbc_pairing_type_t type)
{
    pmesg(msg_verbose, "START shared_pairing_is_symmetric ...");

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
    pmesg(msg_verbose, "START shared_pairing_init ...");

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

    pmesg(msg_verbose, "END shared_pairing_init ...");
}

void shared_params_clear(shared_params_t params)
{
    pmesg(msg_verbose, "START shared_params_clear ...");
    clear_shared_params_t(params);
    pmesg(msg_verbose, "END shared_params_clear ...");
}

void shared_params_setup(shared_params_t params, element_t a, pairing_t pairing)
{
    pmesg(msg_verbose, "START shared_params_setup ...");

    assert(params);

    init_shared_params_t(params, pairing);

    element_random(params->g);
    if (precomputation)
    {
        element_pp_init(params->pp_g, params->g);
        element_pp_pow_zn(params->g1, a, params->pp_g);
    }
    else
        element_pow_zn(params->g1, params->g, a);
    element_random(params->g2);
    element_random(params->h);

    if (precomputation)
    {
        element_pp_init(params->pp_g1, params->g1);
        element_pp_init(params->pp_g2, params->g2);
        element_pp_init(params->pp_h, params->h);
    }

    if (pairing_pp)
        pairing_pp_init(params->pairing_pp_g2, params->g2, pairing);

    pmesg_element(msg_verbose, "", params->g);
    pmesg_element(msg_verbose, "", params->g1);
    pmesg_element(msg_verbose, "", params->g2);
    pmesg_element(msg_verbose, "", params->h);

    pmesg(msg_verbose, "END shared_params_setup ...");
}

int isNumeric(const char *str)
{
    if (str == NULL || *str == '\0')
        return 0;

    int i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++; // Skip sign if present

    while (str[i] != '\0')
    {
        if (!isdigit(str[i]))
            return 0;
        i++;
    }

    return 1;
}

void parse_input(int argn,  char *args[])
{
    if (argn < 2)
    {
        printf("usage: %s [sec-level <n>] [pairing-pp t|f] [pow-pp t|f] "
               "[type-a|type-a1|type-e]\n",
               args[0]);
        exit(1);
    }

    for (int i = 1; i < argn; i++)
    {
        if (strcmp(args[i], "sec-level") == 0)
        {
            if (i + 1 >= argn || !isNumeric(args[i + 1]))
            {
                printf("argomento mancante o non numerico in sec-level!\n");
                exit(1);
            }
            sec_level = atoi(args[i + 1]);
            i++;
        }
        else if (strcmp(args[i], "pairing-pp") == 0)
        {
            if (i + 1 >= argn || strlen(args[i + 1]) > 1 || (args[i + 1][0] != 't' && args[i + 1][0] != 'f'))
            {
                printf("argomento mancante o non valido in pairing-pp!\n");
                exit(1);
            }
            precomputation = args[i + 1][0] == 't';
            i++;
        }
        else if (strcmp(args[i], "pow-pp") == 0)
        {
            if (i + 1 >= argn || strlen(args[i + 1]) > 1 || (args[i + 1][0] != 't' && args[i + 1][0] != 'f'))
            {
                printf("argomento mancante o non valido in pow-pp!\n");
                exit(1);
            }
            pairing_pp = args[i + 1][0] == 't';
            i++;
        }
        else if (strcmp(args[i], "type-a") == 0)
            type = pbc_pairing_type_a;
        else if (strcmp(args[i], "type-a1") == 0)
            type = pbc_pairing_type_a1;
        else if (strcmp(args[i], "type-e") == 0)
            type = pbc_pairing_type_e;
        else
        {
            printf("Parametro %s non riconosciuto...\n", args[i]);
            exit(1);
        }
    }

        printf("Running test: \n- sec-levle %d, \n- pairing %d, \n- precomputation pow %d, "
           "\n- precomputation pairing %d\n",
           sec_level, type, precomputation, pairing_pp);

}
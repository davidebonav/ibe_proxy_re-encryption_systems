#include "lib-shared.h"

int is_pairing_symmetric(pbc_pairing_type_t type)
{
    pmesg(msg_very_verbose, "START is_pairing_symmetric ...");

    if (type == pbc_pairing_type_a || type == pbc_pairing_type_a1 || type == pbc_pairing_type_e)
        return 1;
    else
        return 0;
}

int element_is_generator(element_t el, pairing_t pairing)
{
    pmesg(msg_very_verbose, "START element_is_generator ...");

    // int i;
    // for (i = 2; i <= pairing_get - 1; i++)
    // {
    //     element_t power;
    //     element_init_G1(power, pairing);

    //     element_pow_zn(power, generator, i);

    //     if (element_is1(power))
    //     {
    //         found_generator = 0;
    //         break;
    //     }
    //     element_clear(power);
    // }

    pmesg(msg_very_verbose, "END element_is_generator ...");
    return 1;
}
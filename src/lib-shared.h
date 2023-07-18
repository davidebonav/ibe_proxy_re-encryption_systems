#ifndef SHARED
#define SHARED

#include<stdio.h>
#include <pbc/pbc.h>
#include <ctype.h>
#include<assert.h>

#include"lib-custom-types.h"
#include "lib-misc.h"
#include "lib-mesg.h"

int shared_pairing_is_symmetric(pbc_pairing_type_t type);
void shared_pairing_init(
    pairing_t pairing,
    pbc_pairing_type_t pairing_type,
    unsigned int level);
void shared_params_clear(shared_params_t params);
void shared_params_setup(shared_params_t params, element_t a, pairing_t pairing);

int isNumeric(const char *str);
void parse_input(int argn,  char *args[]);

#endif // SHARED

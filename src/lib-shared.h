#ifndef SHARED
#define SHARED

#include"lib-custom-types.h"
#include "lib-misc.h"
#include "lib-mesg.h"

#include <pbc/pbc.h>
#include <assert.h>

typedef struct {
    bool precompute_parameters;
} options;

int shared_pairing_is_symmetric(pbc_pairing_type_t type);
void shared_pairing_init(
    pairing_t pairing,
    pbc_pairing_type_t pairing_type,
    unsigned int level);
void shared_params_clear(shared_params_t params);
void shared_params_setup(shared_params_t params, element_t a, pairing_t pairing);

#endif // SHARED

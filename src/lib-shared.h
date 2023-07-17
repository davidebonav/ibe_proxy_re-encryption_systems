#ifndef SHARED
#define SHARED

#include "lib-misc.h"
#include "lib-mesg.h"

#include <pbc/pbc.h>
#include <assert.h>

struct shared_params_struct
{
    element_t g;  // generator
    element_t g1; // = g^a
    element_t g2;
    element_t h;
};
typedef struct shared_params_struct *shared_params_ptr;
typedef struct shared_params_struct shared_params_t[1];

int shared_pairing_is_symmetric(pbc_pairing_type_t type);
void shared_pairing_init(
    pairing_t pairing,
    pbc_pairing_type_t pairing_type,
    unsigned int level);
void shared_params_clear(shared_params_t params);
void shared_params_setup(shared_params_t params, element_t a, pairing_t pairing);

#endif // SHARED

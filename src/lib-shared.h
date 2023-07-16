#ifndef SHARED
#define SHARED

#include "lib-misc.h"
#include "lib-mesg.h"

#include <pbc/pbc.h>

int is_pairing_symmetric(pbc_pairing_type_t type);
int element_is_generator(element_t el,pairing_t pairing);

#endif // SHARED

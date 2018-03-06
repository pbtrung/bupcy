#ifndef MACROS_H
#define MACROS_H

#include <stdlib.h>

#include "CException/CException.h"

#define bupcy_free(X)                                                          \
    if (X) {                                                                   \
        free(X);                                                               \
        X = NULL;                                                              \
    }

#define check_exception(X, E)                                                  \
    if (X) {                                                                   \
        Throw(E);                                                              \
    }

#define check_log_exception(X, E)                                              \
    if (X) {                                                                   \
        log_rc_msg(E);                                                         \
        Throw(E);                                                              \
    }

#endif // MACROS_H

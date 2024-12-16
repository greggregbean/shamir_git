#include "utils/debug.h"
#include <iostream>

#define LIKELY(exp) (__builtin_expect((exp) != 0, true))
#define UNLIKELY(exp) (__builtin_expect((exp) != 0, false))

#define ASSERT_FAIL(expr) shagit::AssertionFail(expr, __FILE__, __LINE__, __FUNCTION__)

#define ASSERT(cond)         \
    if (UNLIKELY(!(cond))) { \
        ASSERT_FAIL(#cond);  \
    }

#define ASSERT_PRINT(cond, message)                        \
    do {                                                   \
        if (auto cond_val = cond; UNLIKELY(!(cond_val))) { \
            std::cerr << message << std::endl;             \
            ASSERT_FAIL(#cond);                            \
        }                                                  \
    } while (0)
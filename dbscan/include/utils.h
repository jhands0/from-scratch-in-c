#include <stdlib.h>
#include <assert.h>

#define INIT_CAP 256
#define DECLTYPE_CAST(T)

#define da_reserve(da, new_capacity)                                                                            \
    do                                                                                                          \
    {                                                                                                           \
        if ((new_capacity) > (da)->capacity)                                                                    \
        {                                                                                                       \
            if ((da)->capacity == 0)                                                                            \
            {                                                                                                   \
                (da)->capacity = INIT_CAP;                                                                      \
            }                                                                                                   \
            while ((new_capacity) > (da)->capacity)                                                             \
            {                                                                                                   \
                (da)->capacity *= 2;                                                                            \
            }                                                                                                   \
            (da)->items = DECLTYPE_CAST((da)->items)realloc((da)->items, (da)->capacity * sizeof(*(da)->items));\
            assert((da)->items != NULL);                                                                        \
        }                                                                                                       \
    } while(0)

#define da_append(da, item)                 \
    do                                      \
    {                                       \
        da_reserve((da), (da)->count + 1);     \
        (da)->items[(da)->count++] = (item);\
    } while(0)

#define da_free(da) free((da).items)
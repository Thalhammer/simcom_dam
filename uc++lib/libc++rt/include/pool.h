#pragma once
#include <stddef.h>
#include <bits/c++config.h>
#include "lock.h"

namespace __gnu_cxx
{
void __freeres();
// A fixed-size heap, variable size object allocator
class pool
{
public:
    pool(char *, size_t);

    void *allocate(std::size_t);
    void free(void *);

    bool in_pool(void *);

private:
    struct free_entry;
    struct allocated_entry;

    // A single mutex controlling emergency allocations.
    __gnu_cxx::__mutex emergency_mutex;

    // The free-list
    free_entry *first_free_entry;
    // The arena itself - we need to keep track of these only
    // to implement in_pool.
    char *arena;
    std::size_t arena_size;

    friend void __gnu_cxx::__freeres();
};
}
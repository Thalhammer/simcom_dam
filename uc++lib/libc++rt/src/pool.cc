#include "pool.h"
#include "new.h"

namespace __gnu_cxx
{
struct pool::free_entry
{
    std::size_t size;
    free_entry *next;
};
struct pool::allocated_entry
{
    std::size_t size;
    char data[] __attribute__((aligned));
};

pool::pool(char *ptr, size_t size)
{
    arena = ptr;
    arena_size = size;
    if (!arena)
    {
        // If the allocation failed go without an emergency pool.
        arena_size = 0;
        first_free_entry = NULL;
        return;
    }

    // Populate the free-list with a single entry covering the whole arena
    first_free_entry = reinterpret_cast<free_entry *>(arena);
    new (first_free_entry) free_entry;
    first_free_entry->size = arena_size;
    first_free_entry->next = NULL;
}

void *pool::allocate(std::size_t size)
{
    __gnu_cxx::__scoped_lock sentry(emergency_mutex);
    // We need an additional size_t member plus the padding to
    // ensure proper alignment of data.
    size += offsetof(allocated_entry, data);
    // And we need to at least hand out objects of the size of
    // a freelist entry.
    if (size < sizeof(free_entry))
        size = sizeof(free_entry);
    // And we need to align objects we hand out to the maximum
    // alignment required on the target (this really aligns the
    // tail which will become a new freelist entry).
    size = ((size + __alignof__(allocated_entry::data) - 1) & ~(__alignof__(allocated_entry::data) - 1));
    // Search for an entry of proper size on the freelist.
    free_entry **e;
    for (e = &first_free_entry;
         *e && (*e)->size < size;
         e = &(*e)->next)
        ;
    if (!*e)
        return NULL;
    allocated_entry *x;
    if ((*e)->size - size >= sizeof(free_entry))
    {
        // Split block if it is too large.
        free_entry *f = reinterpret_cast<free_entry *>(reinterpret_cast<char *>(*e) + size);
        std::size_t sz = (*e)->size;
        free_entry *next = (*e)->next;
        new (f) free_entry;
        f->next = next;
        f->size = sz - size;
        x = reinterpret_cast<allocated_entry *>(*e);
        new (x) allocated_entry;
        x->size = size;
        *e = f;
    }
    else
    {
        // Exact size match or too small overhead for a free entry.
        std::size_t sz = (*e)->size;
        free_entry *next = (*e)->next;
        x = reinterpret_cast<allocated_entry *>(*e);
        new (x) allocated_entry;
        x->size = sz;
        *e = next;
    }
    return &x->data;
}

void pool::free(void *data)
{
    __gnu_cxx::__scoped_lock sentry(emergency_mutex);
    allocated_entry *e = reinterpret_cast<allocated_entry *>(reinterpret_cast<char *>(data) - offsetof(allocated_entry, data));
    std::size_t sz = e->size;
    if (!first_free_entry || (reinterpret_cast<char *>(e) + sz < reinterpret_cast<char *>(first_free_entry)))
    {
        // If the free list is empty or the entry is before the
        // first element and cannot be merged with it add it as
        // the first free entry.
        free_entry *f = reinterpret_cast<free_entry *>(e);
        new (f) free_entry;
        f->size = sz;
        f->next = first_free_entry;
        first_free_entry = f;
    }
    else if (reinterpret_cast<char *>(e) + sz == reinterpret_cast<char *>(first_free_entry))
    {
        // Check if we can merge with the first free entry being right
        // after us.
        free_entry *f = reinterpret_cast<free_entry *>(e);
        new (f) free_entry;
        f->size = sz + first_free_entry->size;
        f->next = first_free_entry->next;
        first_free_entry = f;
    }
    else
    {
        // Else search for a free item we can merge with at its end.
        free_entry **fe;
        for (fe = &first_free_entry;
             (*fe)->next && (reinterpret_cast<char *>((*fe)->next) > reinterpret_cast<char *>(e) + sz);
             fe = &(*fe)->next)
            ;
        // If we can merge the next block into us do so and continue
        // with the cases below.
        if (reinterpret_cast<char *>(e) + sz == reinterpret_cast<char *>((*fe)->next))
        {
            sz += (*fe)->next->size;
            (*fe)->next = (*fe)->next->next;
        }
        if (reinterpret_cast<char *>(*fe) + (*fe)->size == reinterpret_cast<char *>(e))
            // Merge with the freelist entry.
            (*fe)->size += sz;
        else
        {
            // Else put it after it which keeps the freelist sorted.
            free_entry *f = reinterpret_cast<free_entry *>(e);
            new (f) free_entry;
            f->size = sz;
            f->next = (*fe)->next;
            (*fe)->next = f;
        }
    }
}

bool pool::in_pool(void *ptr)
{
    char *p = reinterpret_cast<char *>(ptr);
    return (p > arena && p < arena + arena_size);
}

} // namespace __gnu_cxx
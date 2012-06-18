#include <exception>
#include <new>
#include <cstdlib>

//inline void * operator new(unsigned int s) {
inline void * operator new(size_t s) throw (std::bad_alloc)
{
    return malloc(s);
}

inline void operator delete(void *m) throw ()
{
    free(m);
}

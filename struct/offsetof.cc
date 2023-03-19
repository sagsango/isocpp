#include <stddef.h>
#include <stdio.h>

// XXX: Definition
/*
#define offsetof(st, m) \
    ((size_t)&(((st *)0)->m))

#define offsetof(st, m) \
    ((size_t)((char *)&((st *)0)->m - (char *)0))
*/


// XXX: Uses
/*
#define container_of(ptr, type, member) ({ \
                const typeof( ((type *)0)->member ) *__mptr = (ptr); \
                (type *)( (char *)__mptr - offsetof(type,member) );})

#define container_of(ptr, type, member) ((type *)((char *)(ptr) - offsetof(type, member)))
*/


// XXX: Resource
/*
     https://en.wikipedia.org/wiki/Offsetof
 */


struct A
{
    int  a;
    void dummy() {}
};

struct B: public A
{
    int  b;
};

int main()
{
    printf("offsetof(A, a) : %zu\n", offsetof(A, a));
    printf("offsetof(B, a) : %zu\n", offsetof(B, a));
    printf("offsetof(B, b) : %zu\n", offsetof(B, b));
    return 0;
}

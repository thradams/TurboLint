
#include <stdio.h>

typedef enum
{
    A,B
} E;

const char* E_ToString(E e);

const char* E_ToString(E e) { ... }

int main()
{
    E e = A;
    printf("%s", E_ToString(e));
}

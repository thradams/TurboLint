
#include <stdio.h>

typedef enum
{
    A,B
} E;
//
const char* E_ToString(E e);

const char* E_ToString(E e) { ... }


typedef struct 
{
    int i;
    int x;
} Y2;

inline void Y2_Destroy(Y2 * p) { ... }
Y2* Y2_Create() { ... }
void  Y2_Delete(Y2 *p) { ... }

typedef struct X
{
    Y2 y;
    int x;
} X;

void X_Destroy(X * p) {...}

int main()
{
    E e = A;
    printf("%s", E_ToString(e));
}

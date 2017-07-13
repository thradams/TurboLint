
#include <stdio.h>

typedef enum
{
    A,B
} E;

const char* E_ToString(E e);

const char* E_ToString(E e) {
    switch (e) {
        case A: return "A";
        case B: return "B";
    }
    return "";
  }


typedef struct 
{
    int i;
    int x;
} Y2;

 inline void Y2_Destroy(Y2 * p) {
//
//
  }
Y2* Y2_Create() {
    Y2* p = (Y2*) malloc(sizeof * p);
   if (p)
   {
      Y2 temp = {0,0};
      *p = temp;
   }
   return p; 
  }
void  Y2_Delete(Y2 *p) {
   if (p)
   {
      Y2_Destroy(p);
      free(p);
   }
  }

typedef struct X
{
    Y2 y;
    int x;
} X;

void X_Destroy(X * p) {
//
Y2_Destroy(&p->y);
//
//
}

int main()
{
    E e = A;
    printf("%s", E_ToString(e));
}
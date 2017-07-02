//a
//#include "Test\Test7.h"
//#include <stdio.h>
#include "h0.h"

#ifndef Y
#define Y 2
#endif

int i;

typedef enum E
{
    E1,
    E2
} E;

typedef struct Point
{
    int x /* =   1 */;
    int y /* =   2 */;
} Point;

#define NULL  0
#define F(a) a + 1

#if 1
int i =  1;
#else
int i = 2;
#endif

//#define P_INIT {} 2

int /*a*/main()
{
    Point pt =  {{  1,  2}};
    int* p =  {NULL};
    p = /*a*/0;
    p = /*a*/(0 /*b*/);
    F(2);

}
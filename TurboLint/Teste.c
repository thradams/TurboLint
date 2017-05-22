
#include <stdio.h>

typedef struct Point
{
  int x = 1;
  int y = 1;
} Point;

typedef struct Line
{
  Point pt;
  Point* pt2;
} Line;

typedef union s
{
  Point;
  Line;
};

int main()
{  
  Line line = {};
  Line* line = {};
  int *p = {}, p2 = {};
}


/*
#pragma mydir "C:\Users\thiago\Source\Repos\TurboLint\TurboLint"

#include ".\Base\StringEx.c"
#include ".\Base\StrBuilder.c"
#include ".\Base\Path.c"
#include ".\Base\Stream.c"
#include ".\Base\Array.c"

#include ".\Base\Map.c"
#include ".\Base\Map2.c"

#include ".\Parser\Ast.c"
#include ".\Parser\AstPrint.c"
#include ".\Parser\BasicScanner.c"
#include ".\Parser\Macro.c"
#include ".\Parser\Parser.c"
#include ".\Parser\PPToken.c"
#include ".\Parser\Scanner.c"
#include ".\Parser\TokenArray.c"

#include ".\TurboLint\AstMatch.c"
#include ".\TurboLint\CodePrint.c"
#include ".\TurboLint\TCLint2.c"

#include "TurboLint.c"

*/

//#include <stdio.h>

typedef struct Point
{
  int x;
  int y;
} Point;

typedef Point Point2;
typedef struct Line
{
  Point start;
  Point end = { 2, 4 };
  Point2 pt;
  string s;
  double d;
} Line;


int main()
{  
  Point* p = {};
  PointArray points;
  LineArray lines;
  Line  line = {};
  Point pt = {};
  Point* p =  Point_Create();
  pt = (Point){};
  LineArray_Push(lines, Line_Create());
  PointArray_Push(&points, Point_Create());
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
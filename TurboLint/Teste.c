

#pragma mydir "C:\Users\thiago\Source\Repos\TurboLint"


static void F(int* p)
{
}

#define NULL  ((void*)0)
#define A 1

static int main()
{ 
  int i = 1 + A;
  int* p = NULL;

  F(NULL);
  A + A;
}




/*
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

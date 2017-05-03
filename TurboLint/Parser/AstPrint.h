#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "Ast.h"


void TProgram_PrintAstToFile(TProgram* pProgram,
                          const char* fileName);



void PrintLiteralString(FILE* fp, const char* psz);

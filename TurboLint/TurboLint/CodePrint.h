#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "..\Parser\Ast.h"

typedef struct Options
{
    bool bExpandMacros;
    bool bIncludeComments;
} Options;


void TProgram_PrintCodeToFile(TProgram * pProgram,
                              Options* options,
                              const char * fileName,	                        
	                            const char* userpath);


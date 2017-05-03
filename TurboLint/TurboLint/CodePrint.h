#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "..\Parser\Ast.h"


void TProgram_PrintCodeToFile(TProgram * pProgram,
                            const char * fileName,
	                        
	                        const char* userpath);


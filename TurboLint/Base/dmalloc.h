
#pragma once

#include <stddef.h>

void Free(void* p);
void* Realloc(void* ptr, size_t len);
void* _opt _own Malloc(size_t len);


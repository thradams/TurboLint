

#include "dmalloc.h"
#include <stdlib.h>
#include "config.h"

void Free(void* p)
{
  free(p);
}

void* Realloc(void* ptr, size_t len)
{
  void* p = realloc(ptr, len);

  if (!p)
  {
    ASSERT(0);
  }

  return p;
}

void* _opt _own Malloc(size_t len)
{
  void* p = malloc(len);

  if (!p)
  {
    ASSERT(0);
  }

  return p;
}

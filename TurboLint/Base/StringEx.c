
#include "StringEx.h"
#include "dmalloc.h"
#include <stdlib.h>
#include <string.h>
#include <stdlib.h> //malloc


void String_Reset(String* pString)
{
  String_Destroy(pString);
  String_Init(pString, NULL);
}

void String_Destroy(String* _opt pString)
{
  if (pString != NULL)
  {
    Free(*pString);
    *pString = NULL;
  }
}

void String_Attach(String* pString, char* psz)
{
  Free(*pString);
  *pString = psz;
}

void String_Swap(String* pA, String* pB)
{
  String temp_Moved = *pA;
  *pA = *pB;
  *pB = _move temp_Moved;
}

Result String_Set(String *pS1, const char* psz1)
{
  Result result;
  String s1_Moved;
  result = String_Init(&s1_Moved, psz1);

  if (result == RESULT_OK)
  {
    String_Swap(&s1_Moved, pS1);
    String_Destroy(&s1_Moved);
  }

  return result;
}

Result String_Init(String* pString, const char* _opt sourceOpt)
{
  if (sourceOpt != NULL)
  {
    size_t len = strlen(sourceOpt) + 1;
    void * _opt _own snew = Malloc(sizeof(char) * len);

    if (snew == NULL)
    {
      return RESULT_OUT_OF_MEM;
    }

    memcpy(snew, sourceOpt, len);
    *pString = (char*) _move snew;
  }

  else
  {
    *pString = NULL;
  }

  return RESULT_OK;
}


bool String_IsEmpty(const char* _opt psz)
{
  return psz == NULL || psz[0] == 0;
}



/*
  based on
  https://github.com/dspinellis/cscout/blob/084d64dc7a0c5466dc2d505c1ca16fb303eb2bf1/src/macro.cpp
*/



#include "Macro.h"
#include "String.h"
#include "..\Base\Array2.h"
#include <string.h>
#include <stdlib.h>
#include "PPToken.h"
#include <stdio.h>

#define ASSERT(x)



Macro* Macro_Create()
{
	Macro* p = (Macro*)malloc(sizeof(Macro));

	if (p != 0)
	{
		Macro t = MACRO_INIT;
		*p = t;
	}

	return p;
}

void Macro_Destroy(Macro * p)
{
	TokenArray2_Destroy(&p->FormalArguments);
	String2_Destroy(&p->Name);
	TokenArray2_Destroy(&p->TokenSequence);
}

void Macro_Delete(Macro * p)
{
	if (p != 0)
	{
		Macro_Destroy(p);
		free(p);
	}
}


bool FillIn(TokenArray* ts,
	bool get_more,
	TokenArray* removed);

void Glue(const TokenArray* lsI,
          const TokenArray* rsI,
          TokenArray* out);

// Return a new token sequence with hs added to the hide set of every element of ts
void HidenSetAdd(const TokenSet* hs,
                 const TokenArray* ts,
                 TokenArray* pOut)
{
  TokenArray2_Clear(pOut);


  for (int i = 0; i < ts->Size; i++)
  {
    PPToken* t = ts->pItems[i];

    for (int k = 0; k < hs->Size; k++)
    {
      TokenSet_Add(&t->HiddenSet, PPToken_Clone(hs->pItems[k]));
    }

    TokenArray2_Push(pOut, PPToken_Clone(t));
  }

  printf("hsadd returns: ");
  TokenArray2_Print(pOut);
  printf("\n");
}

void ExpandMacro(const TokenArray* pTokenSequence,
	        const MacroMap* macros,
            bool get_more,
            bool skip_defined,
            Macro* caller,
            TokenArray* pOutputSequence);

/*
Retorna o indice do primeiro token que não for espaço
a partir e incluindo o indice start.
Return -1 se não achar.
*/
int FindNoSpaceIndex(const TokenArray* pArray, int start)
{
  int result = -1;

  for (int i = start; i < pArray->Size; i++)
  {
    if (!PPToken_IsSpace(pArray->pItems[i]))
    {
      result = i;
      break;
    }
  }

  return result;
}

// Return s with all \ and " characters \ escaped
void AppendEscaped(StrBuilder2* strBuilder,
                   const char* source)
{
  while (*source)
  {
    switch (*source)
    {
      case '\\':
      case '"':
        StrBuilder2_AppendChar(strBuilder, '\\');

      // FALTHROUGH
      default:
        StrBuilder2_AppendChar(strBuilder, *source);
    }

    source++;
  }
}

/*
* Convert a list of tokens into a string as specified by the # operator
* Multiple spaces are converted to a single space, \ and " are
* escaped
*/
void AppendStringize(StrBuilder2* strBuilder, const TokenArray* ts)
{
  /*
  Each occurrence of white space between the argument’s
  preprocessing tokens becomes a single space character in
  the character string literal.
  */

  /*
  White space before the first preprocessing token and after the
  last preprocessing token composing the argument is deleted.
  */

  StrBuilder2_Append(strBuilder, "\"");

  bool seen_space = true;   // To delete leading spaces

  for (int i = 0; i < ts->Size; i++)
  {
    PPToken* pToken = ts->pItems[i];

    if (PPToken_IsSpace(pToken))
    {
      if (seen_space)
        continue;

      else
        seen_space = true;

      StrBuilder2_Append(strBuilder, " ");
    }

    else if (PPToken_IsStringLit(pToken))
    {
      seen_space = false;
      StrBuilder2_Append(strBuilder, "\\\"");
      AppendEscaped(strBuilder, pToken->Lexeme);
      StrBuilder2_Append(strBuilder, "\\\"");
    }

    else if (PPToken_IsCharLit(pToken))
    {
      seen_space = false;
      StrBuilder2_AppendChar(strBuilder, '\'');
      AppendEscaped(strBuilder, pToken->Lexeme);
      StrBuilder2_AppendChar(strBuilder, '\'');
    }

    else
    {
      seen_space = false;
      StrBuilder2_Append(strBuilder, pToken->Lexeme);
    }
  }

  StrBuilder2_Append(strBuilder, "\"");

  // Remove trailing spaces
  StrBuilder2_Trim(strBuilder);    
}


/*
* Substitute the arguments args appearing in the input sequence is
* Result is created in the output sequence os and finally has the specified
* hide set added to it, before getting returned.
*/
void SubstituteArgs(Macro *pMacro,
	                const MacroMap* macros,
                    const TokenArray* isOriginal,   //macro
                    const TokenArrayMap *args,
                    TokenSet* hs,
                    bool skip_defined,
                    Macro *pCaller,
                    TokenArray* pOutputSequence)
{
  TokenArray2_Clear(pOutputSequence);

  //Trabalha com uma copia
  TokenArray is = TOKENARRAY_INIT;
  TokenArray2_AppendCopy(&is, isOriginal);

  TokenArray os = TOKENARRAY_INIT;

  while (is.Size > 0)
  {

    printf("subst: is=");
    TokenArray2_Print(&is);
    printf(" os=");
    TokenArray2_Print(&os);
    printf("\n");

    PPToken* head = TokenArray2_PopFront(&is);

    if (PPToken_IsStringizingOp(head))
    {
      /*
      Each # preprocessing token in the replacement list for
      a function-like macro shall be followed by a parameter
      as the next preprocessing token in the replacement list.
      */

      // Stringizing operator
      int idx = FindNoSpaceIndex(&is, 0);
      TokenArray* aseq;

      if (idx != -1 &&
          args != NULL &&
          TokenArrayMap2_Lookup(args, is.pItems[idx]->Lexeme, &aseq))
      {
        /*
        If, in the replacement list, a parameter is immediately
        preceded by a # preprocessing token, both are replaced
        by a single character string literal preprocessing token that
        contains the spelling of the preprocessing token sequence
        for the corresponding argument.
        */
        StrBuilder2 strBuilder = STRBUILDER2_INIT;
        AppendStringize(&strBuilder, aseq);
        TokenArray2_Erase(&is, 0, idx + 1);
        TokenArray2_Push(&os, PPToken_Create(strBuilder.c_str));
        StrBuilder2_Destroy(&strBuilder);
        continue;
      }

    }

    else if (PPToken_IsConcatOp(head))
    {

      /*
      If, in the replacement list of a function-like macro,
      a parameter is immediately preceded or followed by
      a ## preprocessing token, the parameter is replaced by
      the corresponding argument’s preprocessing token sequence;
      */
      int idx = FindNoSpaceIndex(&is, 0);

      if (idx != -1)
      {
        TokenArray* aseq;

        if (TokenArrayMap2_Lookup(args, is.pItems[idx]->Lexeme, &aseq))
        {
          TokenArray2_Erase(&is, 0, idx + 1);

          // Only if actuals can be empty
          if (aseq->Size > 0)
          {
            TokenArray os2 = TOKENARRAY_INIT;
            Glue(&os, aseq, &os2);
            TokenArray2_Swap(&os2, &os);
            TokenArray2_Destroy(&os2);
          }
        }

        else
        {
          TokenArray t = TOKENARRAY_INIT;
          TokenArray2_Push(&t, PPToken_Clone(is.pItems[idx]));
          TokenArray2_Erase(&is, 0, idx + 1);

          TokenArray os2 = TOKENARRAY_INIT;
          Glue(&os, &t, &os2);
          TokenArray2_Swap(&os2, &os);
          TokenArray2_Destroy(&os2);
          TokenArray2_Destroy(&t);
        }

        continue;
      }
    }

    else
    {
      int idx = FindNoSpaceIndex(&is, 0);

      if (idx != -1 &&
          PPToken_IsConcatOp(is.pItems[idx]))
      {
        /*
        * Implement the following gcc extension:
        *  "`##' before a
        *   rest argument that is empty discards the preceding sequence of
        *   non-whitespace characters from the macro definition.  (If another macro
        *   argument precedes, none of it is discarded.)"
        * Otherwise, break to process a non-formal argument in the default way
        */
        TokenArray* aseq;

        if (!TokenArrayMap2_Lookup(args, head->Lexeme, &aseq))
        {
          /*
          if (m.get_is_vararg())
          {
          ti2 = find_nonspace(ti + 1, is.end());

          if (ti2 != is.end() && (ai = find_formal_argument(args, *ti2)) != args.end() && ai->second.size() == 0)
          {
          // All conditions satisfied; discard elements:
          // <non-formal> <##> <empty-formal>
          is.erase(is.begin(), ++ti2);
          continue;
          }
          }
          */
          // Non-formal arguments don't deserve special treatment
        }
        else
        {
          // Paste but not expand LHS, RHS

          // Only if actuals can be empty
          if (aseq->Size == 0)
          {
            // Erase including ##
            TokenArray2_Erase(&is, 0, idx + 1);

            int idx2 = FindNoSpaceIndex(&is, 0);

            if (idx2 != -1)
            {
              TokenArray* aseq2;

              if (!TokenArrayMap2_Lookup(args, is.pItems[idx2]->Lexeme, &aseq2))
              {
                // Erase the ## RHS
                TokenArray2_Erase(&is, 0, idx + 1);
                TokenArray2_AppendCopy(&os, aseq);
              }
            }
          }

          else
          {
            // Erase up to ##
            TokenArray2_Print(&is);
            printf("-\n");
            TokenArray2_Erase(&is, 0, idx);
            TokenArray2_Print(&is);
            printf("-\n");
            TokenArray2_AppendCopy(&os, aseq);
          }
        }

        continue;
      }

      TokenArray* argseq = NULL;

      if (args != NULL &&
          TokenArrayMap2_Lookup(args, head->Lexeme, &argseq))
      {
        //expand head
        TokenArray expanded = TOKENARRAY_INIT;
        ExpandMacro(argseq, macros, false, skip_defined, pCaller, &expanded);
        TokenArray2_AppendMove(&os, &expanded);
        TokenArray2_Destroy(&expanded);
        continue;
      }
    }

    TokenArray2_Push(&os, head);
  }

  TokenArray os2 = TOKENARRAY_INIT;
  HidenSetAdd(hs, &os, &os2);

  TokenArray2_Swap(pOutputSequence, &os2);

  TokenArray2_Destroy(&os);
  TokenArray2_Destroy(&os2);
  TokenArray2_Destroy(&is);
}

/*
* Return a macro argument token from tokens
* Used by gather_args.
* If get_more is true when tokens is exhausted read using pdtoken::getnext_noexpand
* (see explanation on that method's comment for why we use pdtoken, rather than pltoken)
* Leave in tokens the first token not gathered.
* If want_space is true return spaces, otherwise discard them
*/
void ArgToken(TokenArray* tokens,
              bool get_more,
              bool want_space,
              PPToken* token)
{
  PPToken *pToken = TokenArray2_PopFront(tokens);
  PPToken_Swap(pToken, token);
  PPToken_Delete(pToken);

  /*  if (want_space)
    {
      if (tokens->Size > 0)
      {
      Token *pToken = TokenArray2_PopFront(tokens);
      PPToken_Swap(pToken, token);
      PPToken_Destroy(pToken);
        return;
      }

      else if (get_more)
      {
        //Pdtoken t;
        //t.getnext_noexpand();
        //return (t);
      }

    else
    {
      String2_Set(&token->Lexeme, NULL);
      //return Ptoken(EOF, "");
    }
    }

    else
    {
      while (tokens->Size > 0 && PPToken_IsSpace(tokens->pItems[0]))
      {
      Token* p = TokenArray2_PopFront(tokens);
      PPToken_Delete(p);
      }

      if (tokens->Size > 0)
      {
      Token* p = TokenArray2_PopFront(tokens);
      PPToken_Swap(p, token);
      PPToken_Delete(p);

        return;
      }

      else if (get_more)
      {
        //Pdtoken t;

        //do
        //{
          //t.getnext_noexpand_nospc();
        //}
        //while (t.get_code() != EOF && t.is_space());

        //return (t);
      }

    else
    {
      String2_Set(&token->Lexeme, NULL);
      //return Ptoken(EOF, "");
    }
    }  */
}

/*
* Get the macro arguments specified in formal_args, initiallly by
* removing them from tokens, then, if get_more is true,
from pdtoken.getnext_noexpand.
* The opening bracket has already been gathered.
* Build the map from formal name to argument value args.
* Return in close the closing bracket token (used for its hideset)
* Return true if ok, false on error.
*/
bool GatherArgs(const char* name,
                TokenArray* tokens,
                const TokenArray* formal_args,
                TokenArrayMap* args,
                bool get_more,
                bool is_vararg,
                PPToken* close)
{
  PPToken t = TOKEN_INIT;

  for (int i = 0; i < formal_args->Size; i++)
  {
    TokenArray* pV = TokenArray2_Create();

    TokenArrayMap2_SetAt(args,
                        formal_args->pItems[i]->Lexeme,
                        pV);

    char terminate;

    if (i + 1 == formal_args->Size)
    {
      terminate = ')';
    }

    else if (is_vararg && i + 2 == formal_args->Size)
    {
      // Vararg last argument is optional; terminate with ) or ,
      terminate = '.';
    }

    else
    {
      terminate = ',';
    }

    int bracket = 0;

    // Get a single argument
    for (;;)
    {
      ArgToken(tokens, get_more, true, &t);
      printf("tokens=");
      TokenArray2_Print(tokens);
      printf("\n");

      if (bracket == 0 && (
            (terminate == '.' && (PPToken_IsChar(&t, ',') || PPToken_IsChar(&t, ')'))) ||
            (terminate != '.' && PPToken_IsChar(&t, terminate))))
      {
        break;
      }

      if (PPToken_IsChar(&t, '('))
      {
        bracket++;
      }

      else if (PPToken_IsChar(&t, ')'))
      {
        bracket--;
      }

      else if (PPToken_IsChar(&t, '\0')) //EOF
      {
        /*
        * @error
        * The end of file was reached while
        * gathering a macro's arguments
        */
        printf("macro [%s] EOF while reading function macro arguments", name);
        return (false);
      }

      else
      {
      }


      TokenArray2_Push(pV, PPToken_Clone(&t));
    }

    printf("Gather args returns: ");
    TokenArray2_Print(pV);
    printf("\n");

    // Check if varargs last optional argument was not supplied
    if (terminate == '.' && PPToken_IsChar(&t, ')'))
    {
      i++;
      TokenArray* pV2 = TokenArray2_Create();

      TokenArrayMap2_SetAt(args,
                          formal_args->pItems[i]->Lexeme,
                          pV2);

      // Instantiate argument with an empty value list
      //args[(*i).get_val()];
      break;
    }

    String2_Set(&close->Lexeme, t.Lexeme);
    //close = t;
  }

  if (formal_args->Size == 0)
  {
    ArgToken(tokens, get_more, false, &t);

    if (PPToken_IsChar(&t, ')'))
    {
      /*
      * @error
      * The arguments to a function-like macro did
      * not terminate with a closing bracket
      */
      printf("macro [%s] close bracket expected for function-like macro", name);
      return (false);
    }
  }

  //#endif
  return (true);
}

void ExpandMacro(const TokenArray* tsOriginal,
	const MacroMap* macros,
            bool get_more,
            bool skip_defined,
            Macro* caller,
            TokenArray* pOutputSequence2)
{
  TokenArray2_Clear(pOutputSequence2);

  TokenArray r = TOKENARRAY_INIT;

  TokenArray ts = TOKENARRAY_INIT;
  TokenArray2_AppendCopy(&ts, tsOriginal);

  printf("Expanding: ");
  TokenArray2_Print(&ts);
  printf("\n");

  while (ts.Size > 0)
  {
    printf("r = ");
    TokenArray2_Print(&r);
    printf("\n");

    PPToken* pHead =
      TokenArray2_PopFront(&ts);

    if (!PPToken_IsIdentifier(pHead))
    {
      TokenArray2_Push(&r, pHead);
      pHead = NULL; //moved
      continue;
    }

    Macro * pMacro = MacroMap2_Find(macros, pHead->Lexeme);

    if (pMacro == NULL)
    {
      // Nothing to do if the identifier is not a macro
      TokenArray2_Push(&r, pHead);
      pHead = NULL; //moved
      continue;
    }

    PPToken* pFound =
      TokenSet_Find(&pHead->HiddenSet, pMacro->Name);

    if (pFound)
    {
      // Skip the head token if it is in the hideset
      printf("Skipping (head is in HS)\n");
      TokenArray2_Push(&r, pHead);
      pHead = NULL;
      continue;
    }

    TokenArray removed_spaces = TOKENARRAY_INIT;

    printf("replacing for %s tokens=", pMacro->Name);
    TokenArray2_Print(&ts);
    printf("\n");

    if (!pMacro->bIsFunction)
    {
      // Object-like macro
      printf("Object-like macro\n");

      TokenSet hiddenSet = TOKENSET_INIT;
      TokenSetAppendCopy(&hiddenSet, &pHead->HiddenSet);
      TokenSet_Add(&hiddenSet, PPToken_Create(pHead->Lexeme));

      TokenArray s = TOKENARRAY_INIT;

      SubstituteArgs(pMacro,
		             macros,
                     &pMacro->TokenSequence,
                     NULL, //empty args
                     &hiddenSet,
                     skip_defined,
                     caller,
                     &s);

      TokenArray2_AppendMove(&s, &ts);
      TokenArray2_Swap(&s, &ts);

      TokenArray2_Destroy(&s);
      TokenSet_Destroy(&hiddenSet);

      caller = pMacro;
    }

    else if (FillIn(&ts, get_more, &removed_spaces) &&
             PPToken_IsOpenPar(ts.pItems[0]))
    {
      printf("Application of a function-like macro\n");

      // Map from formal name to value
      TokenArrayMap args = TOKENARRAYMAP_INIT;

      TokenArray2_PopFront(&ts);
      PPToken close = TOKEN_INIT;

      if (!GatherArgs(pHead->Lexeme,
                      &ts,
                      &pMacro->FormalArguments,
                      &args,
                      get_more,
                      false, /*m.is_vararg,*/
                      &close))
      {
        continue; // Attempt to bail-out on error
      }

      /*
      After the arguments for the invocation of a function-like
      macro have been identified, argument substitution takes place.
      */

      TokenSet hs = TOKENSET_INIT;

      //merge head and close
      SetIntersection(&pHead->HiddenSet,
                      &close.HiddenSet,
                      &hs);
      TokenSet_Add(&hs, PPToken_Create(pMacro->Name));

      TokenArray s = TOKENARRAY_INIT;

      SubstituteArgs(pMacro,
		             macros,
                     &pMacro->TokenSequence,
                     &args,
                     &hs,
                     skip_defined,
                     caller,
                     &s);

      TokenArray2_AppendMove(&s, &ts);
      TokenArray2_Swap(&s, &ts);
      caller = pMacro;

      TokenSet_Destroy(&hs);
      TokenArray2_Destroy(&s);

      TokenArrayMap2_Destroy(&args);
    }

    else
    {
      // Function-like macro name lacking a (
      printf("splicing: [");
      TokenArray2_Print(&removed_spaces);
      printf("]\n");
      TokenArray2_AppendMove(&removed_spaces, &ts);
      TokenArray2_Swap(&removed_spaces, &ts);
      TokenArray2_Push(&r, pHead);
      pHead = NULL; //moved
    }

    //TokenArray2_Contains(pHead->HiddenSet, pMacro->Name);
    TokenArray2_Destroy(&removed_spaces);
  }

  TokenArray2_Swap(&r, pOutputSequence2);

  TokenArray2_Destroy(&r);
  TokenArray2_Destroy(&ts);
}


/*
* Try to ensure that ts has at least one non-space token
* Return true if this is the case
* Return any discarded space tokens in removed
*/
bool FillIn(TokenArray* ts, bool get_more, TokenArray* removed)
{
  while (ts->Size > 0 &&
         PPToken_IsSpace(ts->pItems[0]))
  {
    TokenArray2_Push(removed, TokenArray2_PopFront(ts));
  }

  if (ts->Size > 0)
  {
    return true;
  }

  /*if (get_more)
  {
  Pdtoken t;

  for (;;)
  {
  t.getnext_noexpand();

  if (t.get_code() == EOF)
  return (false);

  else if (t.is_space())
  removed.push_back(t);

  else
  break;
  }

  ts.push_back(t);
  return (true);
  }*/

  return (false);
}




// Paste last of left side with first of right side

void Glue(const TokenArray* lsI,
          const TokenArray* rsI,
          TokenArray* out)
{
  TokenArray ls = TOKENARRAY_INIT;
  TokenArray2_AppendCopy(&ls, lsI);

  TokenArray rs = TOKENARRAY_INIT;
  TokenArray2_AppendCopy(&rs, rsI);

  TokenArray2_Clear(out);

  if (ls.Size == 0)
  {
    TokenArray2_Swap(out, &rs);
  }

  else
  {

    while (ls.Size > 0 &&
           PPToken_IsSpace(ls.pItems[ls.Size - 1]))
    {
      TokenArray2_Pop(&ls);
    }

    while (rs.Size > 0 && PPToken_IsSpace(rs.pItems[0]))
    {
      PPToken* tk = TokenArray2_PopFront(&rs);
      PPToken_Delete(tk);
    }

    if (ls.Size == 0 &&
        rs.Size == 0)
    {
      TokenArray2_Swap(out, &ls);
    }

    else
    {
      //Junta o ultimo token do lado esquerdo
      //com o primeiro do lado direito

      StrBuilder2 strNewLexeme = STRBUILDER2_INIT;

      if (ls.Size > 0)
      {
        printf("glue LS: ");
        printf("%s", ls.pItems[ls.Size - 1]->Lexeme);
        printf("\n");

        StrBuilder2_Append(&strNewLexeme, ls.pItems[ls.Size - 1]->Lexeme);
        TokenArray2_Pop(&ls);
      }

      if (rs.Size > 0)
      {
        printf("glue RS: ");
        printf("%s", rs.pItems[0]->Lexeme);
        printf("\n");
        StrBuilder2_Append(&strNewLexeme, rs.pItems[0]->Lexeme);
        TokenArray2_Pop(&rs);
      }

      TokenArray2_Push(&ls, PPToken_Create(strNewLexeme.c_str));
      StrBuilder2_Destroy(&strNewLexeme);

      TokenArray2_AppendMove(&ls, &rs);
      TokenArray2_Swap(out, &ls);
    }
  }

  printf("glue returns: ");
  TokenArray2_Print(out);
  printf("\n");

  TokenArray2_Destroy(&ls);
  TokenArray2_Destroy(&rs);
}

void ExpandMacroToText(const TokenArray* pTokenSequence,
	const MacroMap* macros,
	bool get_more,
	bool skip_defined,
	Macro* caller,
	StrBuilder2* strBuilder)
{
	StrBuilder2_Clear(strBuilder);
	TokenArray tks = TOKENARRAY_INIT;
	ExpandMacro(pTokenSequence,
		macros,
		get_more,
		skip_defined,
		caller,
		&tks);
	for (int i = 0; i < tks.Size; i++)
	{
		StrBuilder2_Append(strBuilder, tks.pItems[i]->Lexeme);
	}
	TokenArray2_Destroy(&tks);
}




int MacroMap2_SetAt(MacroMap* pMap,
	const char* Key,
	Macro* newValue)
{
	void *pPrevious;
	int r = Map2_SetAt((Map2*)pMap, Key, newValue, &pPrevious);
	Macro_Delete((Macro*)pPrevious);
	return r;
}

bool MacroMap2_Lookup(const MacroMap* pMap,
	const char*  Key,
	Macro** rValue)
{
	return Map2_Lookup((Map2*)pMap,
		Key,
		(void**)rValue);
}

Macro* MacroMap2_Find(const MacroMap* pMap, const char*  Key)
{
	void* p = NULL;
	Map2_Lookup((Map2*)pMap,
		Key,
		&p);
	return (Macro*)p;
}


bool MacroMap2_RemoveKey(MacroMap* pMap, const char*  Key)
{
	Macro *pItem;
	bool r = Map2_RemoveKey((Map2*)pMap, Key, (void**)&pItem);
	if (r)
	{
		Macro_Delete(pItem);
	}
	return r;
}

void MacroMap2_Init(MacroMap* p)
{
	MacroMap t = MACROMAP_INIT;
	*p = t;
}

void MacroMap2_Destroy(MacroMap* p)
{
	Map2_Destroy((Map2*)p);
}

MacroMap* MacroMap2_Create()
{
	MacroMap* p = (MacroMap*)malloc(sizeof * p);
	if (p)
	{
		MacroMap2_Init(p);
	}
	return p;
}

void MacroMap2_Delete(MacroMap * p)
{
	if (p != NULL)
	{
		MacroMap2_Destroy(p);
		free(p);
	}
}

void MacroMap2_Swap(MacroMap * pA, MacroMap * pB)
{
	MacroMap t = MACROMAP_INIT;
	*pA = *pB;
	*pB = t;
}

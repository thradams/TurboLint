
#include "Stream.h"
#include "StringEx.h"
#include <string.h>
#include <stdlib.h>
#include "StrBuilder.h"
#include <Shlwapi.h>
#include <ctype.h>


typedef wchar_t WCHAR;

#define _MAX_DRIVE 255
#define _MAX_DIR 255
#define _MAX_FNAME 255
#define _MAX_EXT 255
#define MAX_PATH 260

static void _splitpath2(const char* path, char* drv, char* dir, char* name, char* ext)
{
	const char* end; /* end of processed string */
	const char* p;      /* search pointer */
	const char* s;      /* copy pointer */

						 /* extract drive name */
	if (path[0] && path[1] == ':') {
		if (drv) {
			*drv++ = *path++;
			*drv++ = *path++;
			*drv = '\0';
		}
	}
	else if (drv)
		*drv = '\0';

	/* search for end of string or stream separator */
	for (end = path; *end && *end != ':'; )
		end++;

	/* search for begin of file extension */
	for (p = end; p>path && *--p != '\\' && *p != '/'; )
		if (*p == '.') {
			end = p;
			break;
		}

	if (ext)
		for (s = end; (*ext = *s++); )
			ext++;

	/* search for end of directory name */
	for (p = end; p>path; )
		if (*--p == '\\' || *p == '/') {
			p++;
			break;
		}

	if (name) {
		for (s = p; s<end; )
			*name++ = *s++;

		*name = '\0';
	}

	if (dir) {
		for (s = path; s<p; )
			*dir++ = *s++;

		*dir = '\0';
	}
}




bool IsInPath(const char * filePath, const char* path)
{
  while (*path)
  {
    if (toupper(*path) != toupper(*filePath))
    {
      return false;
    }

    if (*path == '\0')
      break;

    path++;
    filePath++;
  }

  return true;
}

bool IsFullPath(const char*  path)
{
  if (path != NULL)
  {
    if ((path[0] >= 'a' && path[0] <= 'z') ||
        (path[0] >= 'A' && path[0] <= 'Z'))
    {
      if (path[1] == ':')
      {
        if (path[2] == '\\')
        {
          //Ve se tem pontos ..\ 
          const char* p = &path[2];

          while (*p)
          {
            if (*p == '.' && *(p - 1) == '\\')
            {
              return false;
            }

            p++;
          }

          return true;
        }
      }
    }
  }

  return false;
}

bool FileExists(const char* fullPath)
{
  bool bFileExists = false;
  FILE* fp = fopen(fullPath, "rb");

  if (fp)
  {
    bFileExists = true;
    fclose(fp);
  }

  return bFileExists;
}

Result LoadFile(const char* filename, const char** out, size_t* szOut)
{
  Result result = RESULT_FAIL;
  size_t lSize = 0;
  FILE*  fp = (FILE* ) fopen(filename, "rb");

  if (fp)
  {
    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);
    char*  buffer = (char*)malloc(lSize + 1);

    if (buffer)
    {
      /*size_t fr =*/ fread(buffer, 1, lSize , fp);

      if (feof(fp))
      {
        //ok leu tudo
      }

      if (!ferror(fp))
      {
        //ok
        buffer[lSize] = '\0';
        *out = buffer;
        buffer = NULL;
        result = RESULT_OK;
        *szOut = lSize;
      }

      free(buffer);
    }

    fclose(fp);
  }

  return result;
}

void GetFullDir(const char* fileName, String* out)
{
  char buffer[MAX_PATH];
  /*DWORD r =*/ GetFullPathNameA(
    fileName,
    sizeof(buffer),
    buffer,
    NULL
  );
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char fname[_MAX_FNAME];
  char ext[_MAX_EXT];
  _splitpath2(buffer, drive, dir, fname, ext); // C4996
  StrBuilder s;// = STRBUILDER_INIT;
  StrBuilder_Init(&s, 100);
  StrBuilder_Append(&s, drive);
  StrBuilder_Append(&s, dir);
  String_Attach(out, StrBuilder_Release(&s));
  StrBuilder_Destroy(&s);
}


void GetFullPath(const char* fileName, String* out)
{
  char buffer[MAX_PATH];
  /*DWORD r =*/ GetFullPathNameA(
    fileName,
    sizeof(buffer),
    buffer,
    NULL
  );
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char fname[_MAX_FNAME];
  char ext[_MAX_EXT];
  _splitpath2(buffer, drive, dir, fname, ext); // C4996
  StrBuilder s = STRBUILDER_INIT;
  // StrBuilder_Init(&s, 100);
  StrBuilder_Append(&s, drive);
  StrBuilder_Append(&s, dir);
  StrBuilder_Append(&s, fname);
  StrBuilder_Append(&s, ext);
  String_Attach(out, StrBuilder_Release(&s));
  StrBuilder_Destroy(&s);
}

Result SStream_InitFile(SStream* pStream,
                        const char* fullPath)
{
  ASSERT(IsFullPath(fullPath));
  String_Init(&pStream->NameOrFullPath, fullPath);
  String_Init(&pStream->FullDir2, NULL);
  pStream->currentLine = 1;
  pStream->currentCol = 1;
  pStream->position = 0;
  Result result = LoadFile(fullPath, (const char**)&pStream->text,
                           &pStream->text_length);

  if (result == RESULT_OK)
  {
    //O objetivo aqui eh pegar o diretorio
    GetFullDir(fullPath, &pStream->FullDir2);

    if (pStream->text != NULL &&
        pStream->text[0] != '\0')
    {
      //unicode?
      pStream->currentChar = pStream->text[0];
    }

    else
    {
      pStream->currentChar = '\0';
    }
  }

  return result;
}

Result SStream_Init(SStream* pStream, const char* name, const char*  text)
{
  pStream->currentLine = 1;
  pStream->currentCol = 1;
  pStream->position = 0;
  String_Init(&pStream->text, text);
  String_Init(&pStream->NameOrFullPath, name);
  String_Init(&pStream->FullDir2, "");

  if (text != NULL)
  {
    pStream->text_length = strlen(text);
  }

  else
  {
    pStream->text_length = 0;
  }

  if (pStream->text != NULL &&
      pStream->text[0] != '\0')
  {
    //unicode?
    pStream->currentChar = pStream->text[0];
  }

  else
  {
    pStream->currentChar = '\0';
  }

  return RESULT_OK;
}


void SStream_Destroy(SStream* pStream)
{
  String_Destroy(&pStream->text);
  String_Destroy(&pStream->NameOrFullPath);
  String_Destroy(&pStream->FullDir2);
}


wchar_t SStream_LookAhead(SStream* pStream)
{
  if (pStream->position + 1 >= pStream->text_length)
  {
    return '\0';
  }

  return pStream->text[pStream->position + 1];
}

void SStream_Next(SStream* pStream)
{
  if (pStream->position >= pStream->text_length)
  {
    pStream->currentChar = L'\0';
    return;
  }

  pStream->currentCol++;
  pStream->position++;

  if (pStream->position == pStream->text_length)
  {
    pStream->currentChar = '\0';
  }

  else
  {
    pStream->currentChar = pStream->text[pStream->position];
  }

  if (pStream->currentChar == '\n')
  {
    pStream->currentLine++;
    pStream->currentCol = 0;
  }
}


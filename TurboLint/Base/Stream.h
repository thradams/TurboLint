#pragma once
#include "Result.h"
#include "StringEx.h"
#include <stdio.h>

typedef struct
{
    //name to identify this stream
    String NameOrFullPath;
    String FullDir2;

    //stream content and length
    String text;
    size_t text_length;

    size_t position;
    wchar_t currentChar;

    int currentLine;
    int currentCol;

} SStream;

void GetFullPath(const char* fileName, String* out);
void GetFullDir(const char* fileName, String* out);
bool IsFullPath(const char * path);
bool IsInPath(const char * filePath, const char* path);
bool FileExists(const char* fullPath);

Result SStream_Init(SStream* pfStream,
                    const char* name,
                    const char* psz);

Result SStream_InitFile(SStream* pfStream,
                        const char* fileName);

void SStream_Destroy(SStream* pfStream);

wchar_t SStream_LookAhead(SStream* pStream);

void SStream_Next(SStream* pStream);

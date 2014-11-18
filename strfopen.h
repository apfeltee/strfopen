
#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

struct STRFILE_tag
{
    char* data;
    size_t size;
    size_t written;
    FILE* handle;
    bool is_memstream;
};

typedef struct STRFILE_tag STRFILE;

STRFILE* strfopen();

STRFILE* strfopen_mem(void* buf, size_t sz, const char* mode);

void strfinish(STRFILE* buf);

void strfree(STRFILE* buf);

size_t strfprintf(STRFILE* dest, const char* fmt, ...);

size_t strfwritel(STRFILE* dest, const void* data, size_t membsize, size_t size);

size_t strfwrite(STRFILE* dest, const char* data, size_t sz);

size_t strfputs(STRFILE* dest, const char* str);

size_t strfputc(STRFILE* dest, char c);

char strfgetc(STRFILE* dest);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


#include "strfopen.h"

static STRFILE* strfopen_init()
{
    STRFILE* ret;
    if((ret = (STRFILE*)malloc(sizeof(STRFILE))))
    {
        ret->data = NULL;
        ret->size = 0;
        ret->written = 0;
        ret->is_memstream = false;
        return ret;
    }
    return NULL;
}

STRFILE* strfopen()
{
    STRFILE* ret;
    if((ret = strfopen_init()) != NULL)
    {
        if((ret->handle = open_memstream(&(ret->data), &(ret->size))))
        {
            ret->is_memstream = true;
            return ret;
        }
    }
    return NULL;
}

STRFILE* strfopen_mem(void* buf, size_t sz, const char* mode)
{
    STRFILE* ret;
    if((ret = strfopen_init()) != NULL)
    {
        ret->data = buf;
        ret->size = sz;
        if((ret->handle = fmemopen(ret->data, ret->size, mode)))
        {
            return ret;
        }
    }
    return NULL;
}

void strfinish(STRFILE* buf)
{
    fclose(buf->handle);
}

void strfree(STRFILE* buf)
{
    if(buf->is_memstream)
    {
        free(buf->data);
    }
    free(buf);
    buf = NULL;
}

size_t strfprintf(STRFILE* dest, const char* fmt, ...)
{
    size_t ret;
    va_list args;
    va_start(args, fmt);
    ret = vfprintf(dest->handle, fmt, args);
    dest->written += ret;
    va_end(args);
    return ret;
}

size_t strfwritel(STRFILE* dest, const void* data, size_t membsize, size_t size)
{
    size_t sz;
    sz = fwrite(data, membsize, size, dest->handle);
    dest->written += sz;
    return sz;
}

size_t strfwrite(STRFILE* dest, const char* data, size_t sz)
{
    return strfwritel(dest, data, sizeof(char), sz);
}

size_t strfputs(STRFILE* dest, const char* str)
{
    size_t sz;
    sz = fputs(str, dest->handle);
    dest->written += sz;
    return sz;
}

size_t strfputc(STRFILE* dest, char c)
{
    size_t sz;
    sz = fputc(c, dest->handle);
    dest->written += sz;
    return sz;
}

char strfgetc(STRFILE* dest)
{
    return fgetc(dest->handle);
}

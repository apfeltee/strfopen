
#include "strfopen.h"

int main(int argc, char* argv[])
{
    int i;
    STRFILE* buf;
    if((buf = strfopen()))
    {
        strfprintf(buf, "Hello %s!\n", "world");
        for(i=0; i<argc; i++)
        {
            strfprintf(buf, "  argv[%03d] = \"%s\"\n", i, argv[i]);
        }
        strfinish(buf);
        fprintf(stdout, "buffer(written=%zu, size=%zu):\n%s\n", buf->written, buf->size, buf->data);
        strfree(buf);
    }
    else
    {
        fprintf(stderr, "could not create STRFILE instance!\n");
    }
    return 0;
}

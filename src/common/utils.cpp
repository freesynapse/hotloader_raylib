
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>

#include "utils.h"


int copy_file(const std::string& src, const std::string& dst)
{
    int in, out;
    if ((in = open(src.c_str(), O_RDONLY)) == -1)
        return -1;
    if ((out = open(dst.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
    {
        close(in);
        return -1;
    }
    off_t bytesCopied = 0;
    struct stat st;
    fstat(in, &st);
    int res = sendfile(out, in, &bytesCopied, st.st_size);
    if (res != -1)
        fprintf(stdout, "INFO: copied file '%s' to '%s' (%ld bytes).\n", src.c_str(), dst.c_str(), bytesCopied);
    close(in);
    close(out);
    return res;
}


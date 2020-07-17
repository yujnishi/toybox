#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <utime.h>

int clear_file(const char* fname) {
    struct stat st;
    struct utimbuf ut;

    if ( stat(fname,&st) ) return -1;

    ut.actime  = st.st_atime;
    ut.modtime = st.st_mtime;
    truncate(fname,0);
    utime(fname,&ut);

    return 0;
}

int main(int argc,char* argv[]) {
    int i;

    for ( i = 1; i < argc; i++ ) clear_file(argv[i]);
    return 0;
}


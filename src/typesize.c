#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define printsize(type) printf("%s size is %d[Byte]\n",#type,sizeof(type))

int main() {
    printsize(char);
    printsize(int);
    printsize(long);
    printsize(short);
    printsize(float);
    printsize(double);
    printsize(void*);
    printsize(uid_t);
    printsize(gid_t);
    printsize(size_t);
    printsize(ssize_t);
    printsize(uid_t);
    printsize(suseconds_t);
    printsize(off_t);
    return 0;
}

#include <stdio.h>
#include <math.h>

double make_double(int sig,unsigned int e,unsigned long int n) {
    unsigned long int result;

    result = (sig>=0) ? 0 : ((unsigned long int)1)<<63;
    result |= ((unsigned long int)(e&0x7ff))<<52;
    result |= n&0xfffffffffffff;

    return *((double*)&result);
}

int getbit(unsigned char* s,int n) {
if ( n%8 == 0 ) fputc(' ',stdout);
    return (s[7-n/8]>>(7-(n%8)))&1;
}

int main() {
    double nums[] = { 0.0, 0.0, 1.0, 0.5, 0.25, 0.333, 100.0,255, M_PI, -3, -0.5 };
    double d;
    int n,i;

    int     exp;
    double  value;
    double  sig;

    nums[0] = make_double(1,1024,0);
    for ( n = 0; n < (sizeof(nums)/sizeof(nums[0])); n++ ) {
        d = nums[n];
        printf("%+15.10lf|0x%016llx|%d|",d,*(unsigned long long int*)&d,getbit((unsigned char*)&d,0));
        for ( i = 1; i < 12; i++ ) printf("%d",getbit((unsigned char*)&d,i));
        printf("|");
        for ( i = 12; i < (sizeof(d)*8); i++ ) printf("%d",getbit((unsigned char*)&d,i));
        printf("|\n");

        sig = ((*(unsigned long long int*)&d)>>63)&1;
        exp = ((*(unsigned long long int*)&d)>>52)&0x07ff;
        value = (*(unsigned long long int*)&d)&0x3ffffffffffff;
        printf("sig = %d, exp = %d(%02x), value = %d(%02x)\n",(int)sig,(int)exp,(int)exp,(int)value,(int)value);

        value = d;
        sig = frexp(value, &exp);
        printf("%g = frexp(%g, %d)\n", sig, value, exp);
        printf("%g = ldexp(%g,%d)\n",ldexp(d,1),exp);
        printf("value = %g\n", pow(2.0, (double)exp) * sig);
    }


    return 0;
}

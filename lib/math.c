#include <stdio.h>
#include <errno.h>
#include <math.h>

unsigned long long int expdbl(double d,int* sig,int* exp) {
    unsigned long long int val;

    *sig = d>=0.0 ? 1 : -1;
    *exp = ((*(unsigned long long int*)&d)>>52)&0x07ff;
    val = *(unsigned long long int*)&d;
    val &= 0x3ffffffffffff;
    return val;
}

double impdbl(int sig,int exp,unsigned long long int val) {
    unsigned long long int d;

    sig = sig>=0 ? 0 : 1;

    d = 0;
    d |= ((unsigned long long int)(sig&1))<<63;
    d |= ((unsigned long long int)(exp&0x07ff))<<52;
    d |= ((unsigned long long int)(val&0x3ffffffffffff));
    return *((double*)&d);
}

double fabs(double x) {
    return (x>=0) ? x : -x;
}

double sin(double x) {
    int i,n,f;
    double result;
    double d,t,q;

    x = fabs(x);
    if ( x >= 2.0*M_PI ) return sin(x-(2.0*M_PI));
    if ( x >= M_PI )   return -sin(x-M_PI);
    if ( x >= M_PI/2.0 )   return 1-sin(x-(M_PI/2.0));

    result = 0;
    t = 1.0;
    f = 1;
    for ( n = 1; t != 0.0; n += 2 ) {
        // 分子
        q = 1;
        for ( i = 0; i < n; i++ ) q *= x;

        // 分母
        d = 1;
        for ( i = 2; i <= n; i++ ) d *= i;

        t = q/d;
        result += f*t;

        f *= -1;
    } 

    return result;
}

double log(double x) {
    double d,c,m,r;
    int i,n,s;

    if ( x == 0 ) {
        errno = ERANGE;
        return -HUGE_VAL;
    }
    if ( x < 0 ) {
        errno = EDOM;
        return NAN;
    }

    if ( x == 1 ) return 0;
    if ( x >= 1 ) return log(x/exp(1))+1;

    r = 0;
    n = 1;
    s = -1;
    do {
        s *= -1;

        c = x-1;
        for ( i = 1; i < n; i++ ) c *= x-1;

        m = n;

        d = s * c / m;
        r += d;

        n++;
    } while ( d );

    return r;


}



#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <ctime>
#include "rsa.h"

int main()
{
    RSA rsa;
    big_num a(1769),b(550),c;
    c=rsa.inverse_mod(b,a);
    a.short_print("a=");
    b.short_print("b=");
    c.short_print("c=");
}
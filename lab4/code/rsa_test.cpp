#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include "rsa.h"

int main()
{/*
    big_num a(4875);
    a.short_print("a=");
    big_num b(7);
    //big_num c=a.add(b);
    //big_num c=a.power(2);
    //big_num c=a.mod(b);
    //big_num c=a.sub(b);
    big_num c=a.div(b);
    c.short_print("c=");
    int w=a.same(b);
    /*
    RSA a;
    big_num b=a.create_512_big_num();
    b.bin_print();
    */

    big_num a(193);
    big_num b(3);
    big_num c=a.power(b);
    c.short_print("c=");
    //big_num a=big_num(48);
    a.short_print("a=");
}
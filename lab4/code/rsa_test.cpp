#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include "rsa.h"

int main()
{
    big_num a(43);
    a.bin_print();
    big_num b(2);
    //big_num c=a.add(b);
    //big_num c=a.power(2);
    //big_num c=a.mod(b);
    //big_num c=a.sub(b);
    c.bin_print();

    /*
    RSA a;
    big_num b=a.create_512_big_num();
    b.bin_print();
    */
}
#include<iostream>
#include<cmath>
#include"des_ip.h"
#include"des_array.h"
#include"des_sbox.h"
using namespace std;
char* origin;
bool* buffer;
bool* des_key;
int main()
{
    origin=new char[2000];
    cin.getline(origin,2000);
    buffer=new bool[64];
    pre(origin,buffer);
    des(buffer);
    return 0;
}
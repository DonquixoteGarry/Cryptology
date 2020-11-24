#include<iostream>
#include<cmath>
#include"des.h"
using namespace std;
char* buffer;

int main()
{
    buffer=new char[64];
    cin.getline(buffer,64);
    ip(buffer);
    
}
#include<iostream>
#include<cmath>
#include<string.h>
#include"des_array.h"
using namespace std;

void resort(bool* buffer,int* orderlist)
{
    bool* newbuffer=new bool[64];
    for(int i=0;i<64;i++)
    {
        newbuffer[i]=buffer[orderlist[i]];
    }
    for(int i=0;i<64;i++)
    {
        buffer[i]=newbuffer[i];
    }
    delete[] newbuffer;
}

void ip(bool* buffer){resort(buffer,desorderlist);}

void inverse_ip(bool* buffer){resort(buffer,inverse_desorderlist);}

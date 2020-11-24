#include<iostream>
#include<cmath>
#include"array.h"
using namespace std;


char* left(char* buffer){return &buffer[0];}
char* right(char* buffer){return &buffer[32];}

void resort(char* buffer,int* orderlist)
{
    char* newbuffer=new char[64];
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

void ip(char* buffer)
{//initial permutation
    resort(buffer,desorderlist);
}

void inverse_ip(char* buffer)
{
    resort(buffer,inverse_desorderlist);
}

void f(char* buffer,char* key)
{

}

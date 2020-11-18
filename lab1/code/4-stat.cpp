#include<iostream>
#include"lab1.h"

using namespace std;

char *buffer;
    
int main()
{
    buffer=new char[255];
    cout<<"-----analysing-----\ncrypt message:  ";
    cin.getline(buffer,255);
    stat(buffer);
    cout<<"-----map OK-----"<<endl;
    return 0;
}
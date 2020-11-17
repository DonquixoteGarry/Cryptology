#include<iostream>
#include"lab1.h"

using namespace std;

char *buffer, *result;
    
int main()
{
    buffer=new char[255];
    result=new char[255];
    cout<<"-----maping-----\nuncrypt message:  ";
    cin.getline(buffer,255);
    map(buffer,result);
    cout<<"crypt message:   "<<result<<endl;
    cout<<"-----map OK-----"<<endl;
    return 0;
}
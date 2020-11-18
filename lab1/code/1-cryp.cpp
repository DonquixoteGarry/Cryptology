#include<iostream>
#include"lab1.h"

using namespace std;

int flag,offset;
char *buffer, *result;
    
int main()
{
    buffer=new char[255];
    result=new char[255];
    cout<<"-----cryping-----\nuncrypt message:  ";
    cin.getline(buffer,255);
    cout<<"offset:  ";
    cin >> offset;
    cryp(offset,buffer,result);
    cout<<"crypt message:   "<<result<<endl;
    cout<<"-----cryp OK-----"<<endl;
    return 0;
}
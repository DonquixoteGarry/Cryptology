#include<iostream>
#include"lab1.h"

using namespace std;

int flag,offset;
char *buffer, *result;
    
int main()
{
    buffer=new char[255];
    result=new char[255];
    cout<<"-----anticryping-----\ncryped message:";
    cin.get(buffer, 255);
    anticryp(buffer);
    cout<<"-----anticryp OK-----"<<endl;
    //else cout<<">>> WRONG COMMAND!"<<endl;
    return 0;
}
#include<iostream>
#include"lab1.h"


char maplist[28]= "uvwxyzpqrstklmnofghijabcde*";

using namespace std;

char *buffer, *result;
    
int main()
{
    buffer=new char[2000];
    result=new char[2000];
    cout<<"-----maping-----\nuncrypt message:  \n";
    cin.getline(buffer,2000);
    map(l_alphabet,maplist,buffer,result);
    cout<<"\ncrypt message:   \n"<<result<<endl;
    cout<<"-----map OK-----"<<endl;
    return 0;
}
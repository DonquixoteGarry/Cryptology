#include<iostream>
#include"lab1.h"

char maplist[28]="uvwxyzpqrstklmnofghijabcde*";

char maplist2[28]="LNEDGFCBHI**OAZRMSTV*W*PYU*";


using namespace std;

char *buffer, *result;
    
int main()
{
    buffer=new char[255];
    result=new char[255];
    cout<<"-----maping-----\nuncrypt message:  ";
    cin.getline(buffer,255);
    //map(maplist,buffer,result);
    map(maplist2,buffer,result);
    cout<<"crypt message:   "<<result<<endl;
    cout<<"-----map OK-----"<<endl;
    return 0;
}
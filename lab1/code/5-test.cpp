#include<iostream>
#include"lab1.h"

using namespace std;

char *buffer;
    
int main()
{
    buffer=new char[2000];
    cout<<"-----test-----\ncrypt message:  \n";
    cin.getline(buffer,2000,'\n');
    char char1,char2;
    bool* flag=new bool[strlen(buffer)];
    for(int i=0;i<strlen(buffer);i++) flag[i]=true;
    while(1)
    {
        cout<<"\nori_char:";
        cin>>char1;
        cout<<"new_char:";
        cin>>char2;
        change(buffer,flag,char1,char2);
        if(char1==char2) cout<<"\n->NEW message:   \n\n"<<buffer<<endl<<endl;
        if(char1=='*') break;
    }
    cout<<"-----cryp OK-----"<<endl;
    return 0;
}
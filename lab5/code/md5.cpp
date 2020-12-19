#include <iostream>
#include <string>
#include "md5.h"
using namespace std;

int main()
{
    string choose;
    while(1)
    {
        cout<<"\n\n-----new process-----\n1-encrypt / 2-snow-test / 3-quit\n";
        cin>>choose;
        if(choose=="3")
        {
            cout<<"\n-----over-----\n";
            break;
        }
        if(choose=="1")
        {
            MD5 md5;
            string input;
            cin>>input;
            string output=md5.encrypt(input);
            cout<<output<<endl;
        }
        if(choose=="2")
        {
            MD5 md5;
            string input;
            cin>>input;
            string ori_output=md5.encrypt(input);
            cout<<"input="<<input<<endl;
            cout<<"output="<<ori_output<<endl;
            int whole_change=0;
            for(int i=0;i<8;i++)
            {
                input+="+";
                string output=md5.encrypt(input);
                cout<<"input="<<input<<endl;
                cout<<"output="<<output<<endl;
                int change_byte=md5.byte_change(output,ori_output);
                cout<<"change "<<change_byte<<" bytes\n\n";
                whole_change+=change_byte;
            }
            cout<<"average change "<<double(whole_change)/8<<" bytes\n\n";  
        }
        else
        {
            cout<<">>>wrong command\n";
        }
    }
    return 0;

}
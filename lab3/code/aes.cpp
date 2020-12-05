#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include "aes.h"

using namespace std;

int main()
{
    int order;
    cout<<"\nplease input task code:  1-encrypt / 2-decrypt / 3-test-snow-fall / 4-quit";
    while(cin>>order)
    {
        if(order==1)
        {
            cout<<"\nplease input plaintext(32-hex):\n";
            string plaintext;
            cin>>plaintext;
            cout<<"please input key(32-hex):\n";
            string aes_128_key;
            cin>>aes_128_key;
            //code...
        }
        if(order==2)
        {
            cout<<"\nplease input cryptedtext(32-hex):\n";
            string cryptedtext;
            cin>> cryptedtext;
            cout<<"\nplease input key(32-hex):\n";
            string aes_128_key;
            cin>>aes_128_key;
            //code...
        }
        if(order==3)
        {
            //code...
        }
        if(order==4)
            return 0;
        else
        {
            cout<<"\ntask code error";
            cout<<"\n\n-----new task-----\n\n";
        }
    }

}
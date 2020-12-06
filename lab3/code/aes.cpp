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

            
            AES aes1;
            aes1.setkey(aes_128_key);
            string result;
            aes1._aes_encrypt(plaintext,result);
            cout<<"result of encryption(32-hex):"<<result<<"\n";
        }
        if(order==2)
        {
            cout<<"\nplease input cryptedtext(32-hex):\n";
            string cryptedtext;
            cin>> cryptedtext;
            cout<<"\nplease input key(32-hex):\n";
            string aes_128_key;
            cin>>aes_128_key;
            
            AES aes1;
            aes1.setkey(aes_128_key);
            string result;
            aes1._aes_decrypt(cryptedtext,result);
            cout<<"result of decryption(32-hex):"<<result<<"\n";
        }
        if(order==3)
        {
            AES aes1;
            string aes_128_key;
            cout<<"\nplease input key(32-hex):\n";
            cin>>aes_128_key;
            aes1.setkey(aes_128_key);

            string origin_plaintext,origin_cryptedtext;
            origin_plaintext="00000000000000000000000000000000";
            aes1._aes_encrypt(origin_plaintext,origin_cryptedtext);

            int total_change_bit=0,temp_change;
            string temp_plaintext,temp_cryptedtext;
            temp_plaintext=copy(origin_plaintext);

            for(int i=0;i<8;i++)
            {
                temp_plaintext=[i]='1';
                aes1._aes_encrypt(temp_plaintext,temp_cryptedtext);
                temp_change=aes1.change_bit(origin_cryptedtext,temp_cryptedtext)
                total_change_bit+=temp_change;

                cout<<"plaintext changed "<<i<<" bits,and cryptedtext changed ";
                cout<<temp_change<<" bits\n"
            }
            cout<<"average: cryptedtext changed "<<total_change_bit/8<<" bits\n";

            total_change_bit=0;
            temp_cryptedtext=copy(origin_cryptedtext);
            
            for(int i=0;i<8;i++)
            {
                if(temp_cryptedtext[i]=='1')
                    temp_cryptedtext[i]='0';
                if(temp_cryptedtext[i]=='0')
                    temp_cryptedtext[i]='1';
                aes1._aes_decrypt(temp_cryptedtext,temp_plaintext);
                temp_change=aes1.change_bit(origin_plaintext,temp_plaintext);
                total_change_bit+=temp_change;

                cout<<"cryptedtext changed "<<i<<" bits,and plaintext changed ";
                cout<<temp_change<<" bits\n"
            }
            cout<<"average: plaintext changed "<<total_change_bit/8<<" bits\n";
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
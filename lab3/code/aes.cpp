#include <iostream>
#include <string>
#include "aes.h"

using namespace std;

int main()
{
    int order;
    cout<<"\nplease input task code:  1-encrypt / 2-decrypt / 3-test-snow-fall / 4-quit\n\n";
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
            string result=aes1._aes_encrypt(aes_128_key,plaintext);
            cout<<"result of encryption(32-hex):\n"<<result<<"\n";
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
            string result=aes1._aes_decrypt(aes_128_key,cryptedtext);
            cout<<"result of decryption(32-hex):\n"<<result<<"\n";
        }
        if(order==3)
        {
            AES aes1;
            string aes_128_key;
            cout<<"\nplease input key(32-hex):\n";
            cin>>aes_128_key;

            string origin_plaintext,origin_cryptedtext;
            origin_plaintext="00000000000000000000000000000000";
            origin_cryptedtext=aes1._aes_encrypt(aes_128_key,origin_plaintext);

            int total_change_bit=0;
            string temp_plaintext,temp_cryptedtext;
            temp_plaintext=aes1.mycopy(origin_plaintext);

            for(int i=0;i<8;i++)
            {
                temp_plaintext[i]='1';
                temp_cryptedtext=aes1._aes_encrypt(aes_128_key,temp_plaintext);
                int temp_change=aes1.change_bit(origin_cryptedtext,temp_cryptedtext);
                total_change_bit+=temp_change;

                cout<<"plaintext changed "<<i+1<<" bits,and cryptedtext changed ";
                cout<<temp_change<<" bits\n";
            }
            cout<<"average: cryptedtext changed "<<total_change_bit/8<<" bits\n";

            total_change_bit=0;
            temp_cryptedtext=aes1.mycopy(origin_cryptedtext);
            
            for(int i=0;i<8;i++)
            {
                if(temp_cryptedtext[i]=='1')
                    temp_cryptedtext[i]='0';
                else
                    temp_cryptedtext[i]='1';
                temp_plaintext=aes1._aes_decrypt(aes_128_key,temp_cryptedtext);
                int temp_change=aes1.change_bit(origin_plaintext,temp_plaintext);
                total_change_bit+=temp_change;

                cout<<"cryptedtext changed "<<i+1<<" bits,and plaintext changed ";
                cout<<temp_change<<" bits\n";
            }
            cout<<"average: plaintext changed "<<total_change_bit/8<<" bits\n";
        }
        if(order==4)
        {
            cout<<"\n\n-----program exit-----\n\n";
            return 0;
        }
        if(!(order==1||order==2||order==3||order==4))
        {
            cout<<"\ntask code error";
            cout<<"\n\n-----new task-----\n\n";
            cout<<"\nplease input task code:  1-encrypt / 2-decrypt / 3-test-snow-fall / 4-quit\n\n";
        }
    }

}
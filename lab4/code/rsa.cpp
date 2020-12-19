#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include "rsa.h"

using namespace std;

int main()
{
    int choose;
    cout<<"\n-----new process-----\n1-encrypt / 2-decrypt / 3-exit\n\n";
    while(cin>>choose)
    {
        if(choose==3)
        {
            cout<<"\n-----quit-----\n";
            break;
        }
        if(choose==1)
        {
            RSA rsa;
            cout<<"give little prime (like 17,19,23):\n";
            int _e;
            cin>>_e;
            big_num one(1);
            big_num e(_e);
            big_num p=rsa.create_512_prime();
            big_num q=rsa.create_512_prime();
            big_num eula=(p.sub(one)).mul(q.sub(one));
            big_num n=p.mul(q);
            big_num inverse=rsa.inverse_mod(e,eula);
            cout<<"public key: (N,E)\n";
            eula.short_print("N=");
            e.short_print("E=");
            cout<<"private key: (N,D)\n";
            n.short_print("N=");
            inverse.short_print("D=");
            cout<<"give binary plaintext (like 010000100110110100101011110)\n";
            string plaintext_string;
            big_num plaintext(plaintext_string);
            big_num cryptedtext=plaintext.mod_power(e,n);
            cryptedtext.short_print("cryptedtext is:");
        }
        if(choose==2)
        {
            RSA rsa;
            cout<<"give little prime (like 17,19,23):\n";
            int _e;
            cin>>_e;
            big_num one(1);
            big_num e(_e);
            big_num p=rsa.create_512_prime();
            big_num q=rsa.create_512_prime();
            big_num eula=(p.sub(one)).mul(q.sub(one));
            big_num n=p.mul(q);
            big_num inverse=rsa.inverse_mod(e,eula);
            cout<<"public key: (N,E)\n";
            n.short_print("N=");
            e.short_print("E=");
            cout<<"private key: (N,D)\n";
            eula.short_print("N=");
            inverse.short_print("D=");
            cout<<"give binary cryptedtext (like 010000100110110100101011110)\n";
            string cryptedtext_string;
            big_num cryptedtext(cryptedtext_string);
            big_num plaintext=cryptedtext.mod_power(inverse,n);
            plaintext.short_print("plaintext is:");
        }
    }
    return 0;
}

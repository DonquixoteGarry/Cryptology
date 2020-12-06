#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include "aes.h"

using namespace std;

//3CA10B2157F01916902E1380ACC107BD
//45 64 71 B0 12 94 68 A6 82 BA 7B 26 2E 7B 7C 9B
//C97A63B0E5F29CA7FD7826822B6E67E5
int main()
{
    AES aes1;
    string plaintext;
    cin>>plaintext;
    string key;
    cin>>key;

    //cout<<aes1.column_mix(key)<<endl;
    //cout<<aes1.key_extend(key)<<endl;
    //cout<<aes1.hex_xor(key,plaintext)<<endl;
    //cout<<aes1.byte_multi(key,plaintext)<<endl;
    //cout<<aes1.byte_multi(plaintext,key);
    cout<<aes1._aes_encrypt(key,plaintext)<<endl;
    return 0;
}
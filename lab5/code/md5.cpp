#include <iostream>
#include <string>
#include "md5.h"
using namespace std;

int main()
{
    MD5 md5;
    string input;
    cin>>input;
    string s=md5.encrypt(input);
    cout<<s;
    return 0;
}
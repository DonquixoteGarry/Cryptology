#include <iostream>
#include <string>
#include "array.h"
using namespace std;

class MD5
{
public:
    unsigned int extend_byte_len,origin_byte_len;
    unsigned int reg_a,reg_b,reg_c,reg_d;

    unsigned int shift(unsigned int x,int n)
    {
        unsigned int temp1=x<<n;
        unsigned int temp2=x>>(32-n);
        unsigned int result=temp1|temp2;
        return result;
    }

    unsigned int func(unsigned int x,unsigned int y,unsigned int z,int func_type)
    {
        if(func_type==0)
            return (x&y)|(~x&z);
        if(func_type==1)
            return (x&z)|(y&~z);
        if(func_type==2)
            return x^y^z;
        if(func_type==3)
            return y^(x|~z);
    }

    string int_hex_sub(int reg_value)
    {
        string output;
        unsigned int one_byte;
        for(int i=0;i<4;i++)
        {
            string temp;
            one_byte=((reg_value>>i*8)%(1<<8));
            for (int j = 0; j < 2; j++)
            {
                temp.insert(0,1,hex_val[one_byte%16]);
                one_byte=one_byte/16;
            }
            output+=temp;
        }
        return output;
    }

    unsigned int* extend(string origin_input)
    {
        unsigned int bit_128_set_num;
        unsigned int *extend_input;
        origin_byte_len=origin_input.size();

        bit_128_set_num=((origin_byte_len+8)/64)+1;
        extend_byte_len=bit_128_set_num*16;
        extend_input=new unsigned int[extend_byte_len];
        

        for (unsigned int i = 0; i < bit_128_set_num*16; i++)
            extend_input[i]=0;
        for (unsigned int i=0; i <origin_byte_len; i++)
            extend_input[i>>2]|=(origin_input[i])<<((i%4)*8);

        extend_input[origin_byte_len>>2]|=0x80<<(((origin_byte_len%4))*8);
        extend_input[bit_128_set_num*16-2]=origin_byte_len*8;

        return extend_input;
    }

    void HMD5(unsigned int *bit_128_set)
    {
        unsigned int a,b,c,d,f,g,temp;
        a=reg_a;
        b=reg_b;
        c=reg_c;
        d=reg_d;
        for (unsigned int i = 0; i < 64; i++)
        {
            f=func(b,c,d,i/16);
            if(i<16)        
                g=i;
            if(i<32&&i>=16) 
                g=(5*i+1)%16;
            if(i<48&&i>=32) 
                g=(3*i+5)%16;
            if(i>=48)       
                g=(7*i)%16;
            temp=d;
            d=c;
            c=b;
            b=b+shift((a+f+T[i]+bit_128_set[g]),left_shift_list[i]);
            a=temp;
        }
        reg_a+=a;
        reg_b+=b;
        reg_c+=c;
        reg_d+=d;
    }

    string encrypt(string plaintext)
    {
        reg_a=reg_init[0];
        reg_b=reg_init[1];
        reg_c=reg_init[2];
        reg_d=reg_init[3];
        unsigned int *extend_input=extend(plaintext);
        for(unsigned int i=0;i<extend_byte_len/16;i++)
        {
            unsigned int bit_128_set[16];
            for(unsigned int j=0;j<16;j++)
                bit_128_set[j]=extend_input[i*16+j];
            HMD5(bit_128_set);
        }
        string result=int_hex_sub(reg_a)+int_hex_sub(reg_b)+int_hex_sub(reg_c)+int_hex_sub(reg_d);
        return result;
    }

    int byte_change(string str1,string str2)
    {
        int change_byte_num=0;
        for(int i=0;i<32;i++)
        {
            if(str1[i]!=str2[i])
                change_byte_num++;
        }
        return change_byte_num;
    }
};
#include <iostream>
#include <string>
#include "array.h"
using namespace std;

#define shift(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))    
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

class MD5
{
public:
    unsigned int strlength;
    unsigned int reg_a,reg_b,reg_c,reg_d;

    string encrypt(string plaintext)
    {
        reg_a=reg_init[0];
        reg_b=reg_init[1];
        reg_c=reg_init[2];
        reg_d=reg_init[3];
        unsigned int *strByte=extend(plaintext);
        for(unsigned int i=0;i<strlength/16;i++)
        {
            unsigned int set[16];
            for(unsigned int j=0;j<16;j++)
                set[j]=strByte[i*16+j];
            HMD(set);
        }
        string result;
        result=changeHex(reg_a)+(changeHex(reg_b))+(changeHex(reg_c))+(changeHex(reg_d));
        return result;
    }

    string changeHex(int a)
    {
        int b;
        string str1;
        string str="";
        for(int i=0;i<4;i++)
        {
            str1="";
            b=((a>>i*8)%(1<<8))&0xff;   //逆序处理每个字节
            for (int j = 0; j < 2; j++)
            {
                str1.insert(0,1,str16[b%16]);
                b=b/16;
            }
            str+=str1;
        }
        return str;
    }

    unsigned int* extend(string str)
    {
        unsigned int set=((str.length()+8)/64)+1;//以512位,64个字节为一组
        unsigned int *strByte=new unsigned int[set*16];    //64/4=16,所以有16个整数
        strlength=set*16;
        for (unsigned int i = 0; i < set*16; i++)
            strByte[i]=0;
        for (unsigned int i=0; i <str.length(); i++)
        {
            strByte[i>>2]|=(str[i])<<((i%4)*8);//一个整数存储四个字节，i>>2表示i/4 一个unsigned int对应4个字节，保存4个字符信息
        }
        strByte[str.length()>>2]|=0x80<<(((str.length()%4))*8);//尾部添加1 一个unsigned int保存4个字符信息,所以用128左移
        /*
        *添加原长度，长度指位的长度，所以要乘8，然后是小端序，所以放在倒数第二个,这里长度只用了32位
        */
        strByte[set*16-2]=str.length()*8;
        return strByte;
    }

    void HMD(unsigned int M[])
    {
        unsigned int f,g;
        unsigned int a=reg_a;
        unsigned int b=reg_b;
        unsigned int c=reg_c;
        unsigned int d=reg_d;
        for (unsigned int i = 0; i < 64; i++)
        {
            if(i<16)
            {
                f=F(b,c,d);
                g=i;
            }
            if (i<32&&i>=16)
            {
                f=G(b,c,d);
                g=(5*i+1)%16;
            }
            if(i<48&&i>=32)
            {
                f=H(b,c,d);
                g=(3*i+5)%16;
            }
            if(i>=48)
            {
                f=I(b,c,d);
                g=(7*i)%16;
            }
            unsigned int tmp=d;
            d=c;
            c=b;
            b=b+shift((a+f+k[i]+M[g]),s[i]);
            a=tmp;
        }
        reg_a+=a;
        reg_b+=b;
        reg_c+=c;
        reg_d+=d;
    }
};
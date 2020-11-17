#include<iostream>
#include<iomanip>
#include<cmath>
#include<string.h>

using namespace std;

char h_alphabet[28] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ*";
char l_alphabet[28] = "abcdefghijklmnopqrstuvwxyz*";
char maplist[28]="uvwxyzpqrstklmnofghijabcde*";

int freq[26];
float perc[26];

int trans(char alphabet)
{
    for(int i=0;i<26;i++)
    {
        if((alphabet== l_alphabet[i])||(alphabet == h_alphabet[i]))
        return i;
    }   
    if((int(alphabet)>65)&&(int(alphabet)<90)) return (int(alphabet)-65);
    if((int(alphabet)>97)&&(int(alphabet)<122)) return (int(alphabet)-97);    
    return 26;
}

char deal(char ori, int offset)
{
    if(trans(ori)!=26)
    {
        return l_alphabet[(trans(ori) + offset) % 26];
    }
    if (ori == ' ') return ' ';
    else return '*';
}

void cryp(int offset,char *buffer,char* result)
{
    for (int i = 0; i < strlen(buffer); i++)
    {
        result[i] = deal(buffer[i], offset);
    }
    result[strlen(buffer)] = '\0';
    return;
}

void anticryp(char *crypt)
{
    char* testmessage=new char[255];
    cout<<"\noffset"<<"\t\t"<<"result"<<endl;
    for(int j=25;j>=0;j--)
    {
        cryp(j,crypt,testmessage);
        cout<<(26-j)<<"\t\t"<<testmessage<<endl;
    }
    return;
}

void map(char* buffer, char* result)
{
    int len=strlen(buffer);
    int i=0,j=0;
    while(i<len)
    {
        result[i]=maplist[trans(buffer[i])];
        i++;
    }
    result[len]='\0';
    return;
}

void stat(char* buffer)
{
    int len=strlen(buffer);
    for(int i=0;i<26;i++) freq[i]=0;
    for(int i=0;i<len;i++)
    {
        freq[trans(buffer[i])]++;
    }
    cout<<"\nletters\t\t"<<"times"<<"\t\tfreqence\n\n";
    for(int i=0;i<26;i++)
    {
        perc[i]=100*(float(freq[i])/len);
        cout<<l_alphabet[i]<<"\t\t"<<freq[i]<<"\t\t"<<setiosflags(ios::fixed)<<setprecision(4)<<perc[i] <<" \%"<<endl;
    }     
}
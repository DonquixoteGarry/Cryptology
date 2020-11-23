# lab1实验报告

## 一.移位密码实现

根据移位密码实验的实验原理的部分讲解,编写移位密码的加密程序和解密程序.

### 1.加密程序`1-cryp.cpp`

加密程序`1-cryp.cpp`代码如下

```c++
#include<iostream>
#include"lab1.h"

using namespace std;

int flag,offset;
char *buffer, *result;
    
int main()
{
    buffer=new char[255];
    result=new char[255];
    cout<<"-----cryping-----\nuncrypt message:  ";
    cin.getline(buffer,255);
    cout<<"offset:  ";
    cin >> offset;
    cryp(offset,buffer,result);
    cout<<"crypt message:   "<<result<<endl;
    cout<<"-----cryp OK-----"<<endl;
    return 0;
}
```

使用`VC`编译器将以上代码编译完成后,运行程序`1-cryp.exe`.

先后输入明文和在移位置换表中的向右偏移量,即可得到密文.

![1](1.png)

### 2.解密程序`2-anticryp.cpp`

加密程序`2-anticryp.cpp`代码如下

```c++
#include<iostream>
#include"lab1.h"

using namespace std;

int flag,offset;
char *buffer, *result;
    
int main()
{
    buffer=new char[255];
    result=new char[255];
    cout<<"-----anticryping-----\ncryped message:";
    cin.get(buffer, 255);
    anticryp(buffer);
    cout<<"-----anticryp OK-----"<<endl;
    //else cout<<">>> WRONG COMMAND!"<<endl;
    return 0;
}
```

使用`VC`编译器将以上代码编译完成后,运行程序`2-anticryp.exe`.

输入密文后,程序自动输出向右偏移量从`0`到`25`情况下得到的明文,选取其中具有合理翻译的明文作为解密结果.

![2](2.png)

## 二.移位密码破解尝试

已知密文如下

```c
cnkxk gxk eua juotm
```

使用破解程序`2-anticryp.exe`,得到输出如下

```
offset          result
1               bmjwj fwj dtz itnsl
2               alivi evi csy hsmrk
3               zkhuh duh brx grlqj
4               yjgtg ctg aqw fqkpi
5               xifsf bsf zpv epjoh
6               where are you doing
7               vgdqd zqd xnt cnhmf
8               ufcpc ypc wms bmgle
9               tebob xob vlr alfkd
10              sdana wna ukq zkejc
11              rczmz vmz tjp yjdib
12              qbyly uly sio xicha
13              paxkx tkx rhn whbgz
14              ozwjw sjw qgm vgafy
15              nyviv riv pfl ufzex
16              mxuhu qhu oek teydw
17              lwtgt pgt ndj sdxcv
18              kvsfs ofs mci rcwbu
19              jurer ner lbh qbvat
20              itqdq mdq kag pauzs
21              hspcp lcp jzf oztyr
22              grobo kbo iye nysxq
23              fqnan jan hxd mxrwp
24              epmzm izm gwc lwqvo
25              dolyl hyl fvb kvpun
26              cnkxk gxk eua juotm
```

可得到偏移量为`6`.原明文`where are you doing`.

## 三.单表置换密码加密和解密尝试

### 1.单表置换密码加密和解密的实现

加密程序和解密程序为`3-cryp.exe`和`3-anticryp.exe`,可调用函数`map`,根据表`a`和表`b`将原文`s`映射为`s'` .

在加密和解密时只要调换`map`函数中参数`a`和`b`的位置即可.

加密程序如下

```c++
#include<iostream>
#include"lab1.h"
using namespace std;

char maplist[28]= "uvwxyzpqrstklmnofghijabcde*";
char *buffer, *result;
    
int main()
{
    buffer=new char[2000];
    result=new char[2000];
    cout<<"-----maping-----\nuncrypt message:  \n";
    cin.getline(buffer,2000);
    map(l_alphabet,maplist,buffer,result);
    cout<<"\ncrypt message:   \n"<<result<<endl;
    cout<<"-----map OK-----"<<endl;
    return 0;
}
```

解密程序如下

```c++
#include<iostream>
#include"lab1.h"
using namespace std;

char maplist[28]= "uvwxyzpqrstklmnofghijabcde*";
char *buffer, *result;
    
int main()
{
    buffer=new char[2000];
    result=new char[2000];
    cout<<"-----maping-----\nuncrypt message:  \n";
    cin.getline(buffer,2000);
    map(maplist,l_alphabet,buffer,result);
    cout<<"\ncrypt message:   \n"<<result<<endl;
    cout<<"-----map OK-----"<<endl;
    return 0;
}
```

设置以下单表置换密码表

| 明文 | a    | b    | c    | d    | e    | f    | g    | h    | i    | j    | k    | l    | m    | n    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 密文 | u    | v    | w    | x    | y    | z    | p    | q    | r    | s    | t    | k    | l    | m    |

| 明文 | o    | p    | q    | r    | s    | t    | u    | v    | w    | x    | y    | z    |      |      |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 密文 | n    | o    | f    | g    | h    | i    | j    | a    | b    | c    | d    | e    |      |      |

原明文如下 

```c
where there is a will there is a way
```

密文如下

```c
csziz ksziz tj v ctmm ksziz tj v cve
```

![3](3.png)

## 四.解密所给密文

### 1.统计字母出现频率

编写程序`4-stat.cpp`统计密文中字母出现频率,如下

```
#include<iostream>
#include"lab1.h"
using namespace std;
char *buffer;

int main()
{
    buffer=new char[255];
    cout<<"-----analysing-----\ncrypt message:  ";
    cin.getline(buffer,255);
    stat(buffer);
    cout<<"-----map OK-----"<<endl;
    return 0;
}
```

函数`stat`定义如下

```c++
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
        cout<<l_alphabet[i]<<"\t\t"<<freq[i]<<"\t\t";
        cout<<setiosflags(ios::fixed)<<setprecision(4)<<perc[i] <<" \%"<<endl;
    }
    return;
}
```

### 2.具体推断替换表

根据以下根据,依序进行推断

| 推断依据(依序)               | 推断结果       |
| ---------------------------- | -------------- |
| t,e字母统计概率较高          | S->T,C->E      |
| the,that出现频率高           | C->E,I->H      |
| to出现频率高                 | M->O           |
| is,in出现频率高              | J->I,B->N,R->S |
| oi相连的常见单词为point      | X->P           |
| 待解密单词形似from           | P->R,Q->M      |
| 待解密单词形似possible       | H->B,A->L      |
| 待解密单词形似who,way,wishes | V->W           |
| 待解密单词形似original       | E->G           |
| 待解密单词形似such           | Z->U,G->C      |
| 待解密单词形似unauthorized   | O->Z           |
| 待解密单词形似recovered      | T->V           |
| 解密完成,以下字母对应原字符  | Y,F,D          |
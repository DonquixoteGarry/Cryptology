#include <iostream>
#include <string>
#include <cmath>
#include <map>
using namespace std;

class big_num
{
public:
    bool value[1024];
    big_num()
    {
        for(int i=0;i<1024;i++)
            value[i]=0;
    }

    big_num(int _value)
    {//init a big_num less than 2^16(65536)
        int temp=_value;
        for(int i=1024-16;i<1024;i++)
        {
            int temp2=temp;
            temp=temp%int(pow(2,1023-i));
            if(temp==temp2) value[i]=0;
            else value[i]=1;
        }
        for(int i=0;i<1024-16;i++) value[i]=0;
    }

    void mycopy(big_num copyer)
    {
        for(int i=0;i<1024;i++)
            value[i]=copyer.value[i];
    }

    //roll_order=0 means first append,start at bit-512
    //use to generate 512-bit prime
    void append(int append_value,int roll_order)
    {   
        int temp=append_value;
        for(int i=0;i<16;i++)
        {
            int temp2=temp;
            temp=temp%int(pow(2,15-i));
            if(temp==temp2) value[512+roll_order*16+i]=0;
            else value[512+roll_order*16+i]=1;
        }
    }

    big_num add(big_num bn2)
    {
        big_num bn3;
        bool up;
        up=0;
        int temp_sum;
        for(int i=1023;i>=0;i--)
        {
            temp_sum=value[i]+bn2.value[i]+up;
            
            if(temp_sum>1) up=1;
            else up=0;

            if(temp_sum%2==0) bn3.value[i]=0;
            else bn3.value[i]=1;
        }
        return bn3;
    }

    big_num sub(big_num bn2)
    {//bn1-bn2=bn3
        big_num bn3;
        bool down;
        down=0;
        int temp_sum;
        for(int i=1023;i>=0;i--)
        {
            temp_sum=value[i]-bn2.value[i]-down;

            if(temp_sum<0) down=1;
            else down=0;

            if(temp_sum%2==0) bn3.value[i]=0;
            else bn3.value[i]=1;
        }
        return bn3;
    }

    big_num left_shift(int step)
    {
        big_num bn3;
        if(step>0)
        {
            for(int i=0;i<1024-step;i++)
                bn3.value[i]=value[i+step];
            for(int i=1024-step;i<1024;i++)
                bn3.value[i]=0;
            return bn3;
        }
        else
        {
            for(int i=0;i<0-step;i++)
                bn3.value[i]=0;
            for(int i=0-step;i<1024;i++)
                bn3.value[i]=value[i+step];
            return bn3;
        }
    }

    big_num mul(big_num bn2)
    {
        big_num mul_result;
        for(int i=0;i<1024;i++)
        {
            if(value[i]==1)
                mul_result=mul_result.add(bn2.left_shift(1023-i));
        }
        return mul_result;
    }

    bool more(big_num bn2)
    {//equal is true
        for(int i=0;i<1024;i++)
        {
            if(value[i]&&!bn2.value[i]) return true;
            if(!value[i]&&bn2.value[i]) return false;
        }
        return true;
    }

    bool more(int _other)
    {//equal is true
    //most is 65536
        big_num other(_other);
        for(int i=0;i<1024;i++)
        {
            if(value[i]&&!other.value[i]) return true;
            if(!value[i]&&other.value[i]) return false;
        }
        return true;
    }

    big_num mod(big_num bn2)
    {
        //this>bn2
        big_num bn3;
        if(bn2.is_zero())
        {
            cout<<"\n>>>syntax error:div 0,result set zero\n\n";
            return bn3; 
        }
        for(int i=0;i<1024;i++)
            bn3.value[i]=value[i];
        int max_step;
        bool high_bit_get1,high_bit_get2;
        high_bit_get1=false;
        high_bit_get2=false;
        for(int i=0;i<1024;i++)
        {
            if(value[i]&&!high_bit_get1) 
            {
                high_bit_get1=true;
                max_step=i;
            }
            if(bn2.value[i]&&!high_bit_get2)
            {
                high_bit_get2=true;
                max_step=i-max_step;
                break;
            }
            if(high_bit_get2&&high_bit_get1)break;
        }
        for(int i=max_step;i>=0;i--)
        {
            if(bn3.more(bn2.left_shift(i)))
            {
                bn3=bn3.sub(bn2.left_shift(i));   
            }
        }
        return bn3;
    }

    big_num div(big_num bn2)
    {
        //this>bn2
        big_num bn3;
        if(bn2.is_zero())
        {
            cout<<"\n>>>syntax error:div 0,result set zero\n\n";
            return bn3; 
        }
        for(int i=0;i<1024;i++)
            bn3.value[i]=value[i];
        int max_step;
        bool high_bit_get1,high_bit_get2;
        high_bit_get1=false;
        high_bit_get2=false;
        for(int i=0;i<1024;i++)
        {
            if(value[i]&&!high_bit_get1) 
            {
                high_bit_get1=true;
                max_step=i;
            }
            if(bn2.value[i]&&!high_bit_get2)
            {
                high_bit_get2=true;
                max_step=i-max_step;
                break;
            }
            if(high_bit_get2&&high_bit_get1)break;
        }
        big_num div_result;
        for(int i=max_step;i>=0;i--)
        {
            if(bn3.more(bn2.left_shift(i)))
            {
                div_result.value[1023-i]=1;
                bn3=bn3.sub(bn2.left_shift(i));   
            }
        }
        return div_result;;
    }


    big_num power(int times)
    {
        big_num ori,result;
        result.value[1023]=1;
        for(int i=0;i<1024;i++) 
            ori.value[i]=value[i];
        for(int i=0;i<times;i++) 
            result=result.mul(ori);
        return result;
    }

    big_num power(big_num _times)
    {
        big_num times,ori,result,one(1);
        times.mycopy(_times);
        result.value[1023]=1;
        for(int i=0;i<1024;i++) 
            ori.value[i]=value[i];
        while(!times.is_zero())
        {
            result=result.mul(ori);
            times=times.sub(one);
        }
        return result;
    }

    big_num mod_mul(big_num _bn2,big_num mod_num)
    {
        big_num answer(0);
        big_num bn2;
        big_num result;
        for(int i=0;i<1024;i++)
        {
            bn2.value[i]=_bn2.value[i];
            result.value[i]=value[i];
        }
        while(!bn2.is_zero())
        {
            if(bn2.value[1023])
            {
                big_num temp=answer.add(result);
                answer=temp.mod(mod_num);
            }
            result=result.left_shift(1);
            result=result.mod(mod_num);
            bn2=bn2.left_shift(-1);
        }
        return answer;
    }

    big_num mod_power(big_num _times,big_num mod_num)
    {
        big_num times;
        times.mycopy(_times);
        big_num answer(1),result;
        for(int i=0;i<1024;i++)
            result.value[i]=value[i];
        while(!times.is_zero())
        {
            if(times.value[1023])
                answer=answer.mod_mul(result,mod_num);
            result=result.mod_mul(result,mod_num);
            times=times.left_shift(-1);
        }
        return answer;
    }

    bool is_zero()
    {
        for(int i=0;i<1024;i++)
            if(value[i]==1) return false;
        return true;
    }

    void hex_print(string alert="default")
    {
        if(alert!="default")cout<<endl<<alert<<":"<<endl;
        else cout<<"\nhex-value:"<<endl;
        if(is_zero())
        {
            cout<<"\n>>>value is zero.\n\n";
            return;
        }
        for(int i=0;i<256;i++)
        {
            int temp=0;
            for(int j=0;j<4;j++)
                if(value[4*i+j]) temp+=pow(2,3-j);
            char ch;
            if(temp<10) ch='0'+temp;
            else ch='A'+temp-10;
            cout<<ch;
        }
        cout<<endl;
    }

    void bin_print(string alert="default")
    {
        if(alert!="default")cout<<endl<<alert<<":"<<endl;
        else cout<<"\nbin-value:"<<endl;
        if(is_zero())
        {
            cout<<"\n>>>value is zero.\n\n";
            return;
        }
        for(int i=0;i<1024;i++)
        {
            char ch;
            if(value[i]) ch='1';
            else ch='0';
            cout<<ch;
        }
        cout<<endl;
    }

    void short_print(string alert="default")
    {
        if(alert!="default")cout<<endl<<alert<<":"<<endl;
        else cout<<"\nshorten-bin-value:"<<endl;
        if(is_zero())
        {
            cout<<"\n>>>value is zero.\n\n";
            return;
        }
        int i;
        for(i=0;;i++)
        {
            if(value[i])break;
        }
        for(;i<1024;i++)
        {
            char ch;
            if(value[i]) ch='1';
            else ch='0';
            cout<<ch;
        }
        cout<<endl;
    }

    bool same(big_num maybe_same)
    {
        big_num ori,diff;
        bool result=true;
        for(int i=0;i<1024;i++)
        {
            ori.value[i]=value[i];
            if(ori.value[i]!=maybe_same.value[i])
                result=false;
        }
        return result;
    }

    bool is_prime(int _times=20)
    {   //use Miller-Rabin test
        //two_times :2's times,is the k of (x=2^k * m)
        //odd: the odd m of (x=2^k * m)
        //use to big prime>1000
        int prime_array[21]={3,5,7,11, 13,17,19,23,  29,31,37,41, 43,47,53,59, 61,67,71,73};
        big_num two_times,odd,ori,temp,temp2;
        big_num one(1),two(2);
        for(int i=0;i<1024;i++)
            ori.value[i]=value[i];
        temp=ori.sub(one);
        while(1)
        {
            temp2=temp.mod(two);
            if(temp2.is_zero())
            {
                two_times=two_times.add(one);
                temp=temp.div(two);
            }
            else break;
        }
        odd.mycopy(temp);
        int times=_times;
        int i=0;
        big_num _temp;
        while(i<times)
        {
            big_num a(prime_array[i++]);
            big_num b=a.mod_power(odd,ori);
            for(big_num j(1);two_times.more(j);j=j.add(one))
            {
                _temp=b.mod_mul(b,ori);
                big_num ori_1=ori.sub(one);
                if(_temp.same(one)&&!b.same(one)&&!(b.same(ori_1)))
                    return false;
                b.mycopy(_temp);
            }
            if(!b.same(one))
                return false;
        }
        return true;
    }

};

class signed_big_num
{
public:
    bool sign;//(1)>=0 is positive,(0)<0 is negative
    big_num main_value;
    signed_big_num() { sign=true; }
    signed_big_num add(signed_big_num sbn2)
    {
        signed_big_num sbn3;
        big_num temp;
        if(sign&&sbn2.sign)
            temp=main_value.add(sbn2.main_value);
        if(!sign&&!sbn2.sign)
        {
            temp=main_value.add(sbn2.main_value);
            sign=false;
        }
        if(!sign&&sbn2.sign)
        {
            if(main_value.more(sbn2.main_value))
            {
                temp=main_value.sub(sbn2.main_value);
                sign=false;
            }
            else temp=sbn2.main_value.sub(main_value);
        }
        if(sign&&!sbn2.sign)
        {
            if(sbn2.main_value.more(main_value))
            {
                temp=sbn2.main_value.sub(main_value);
                sign=false;
            }
            else temp=main_value.sub(sbn2.main_value);
        }
        sbn3.main_value.mycopy(temp);
        return sbn3;
    }

    signed_big_num sub(signed_big_num sbn2)
    {
        signed_big_num sbn3,temp_sbn1,temp_sbn2;
        for(int i=0;i<1024;i++)
            temp_sbn1.value[i]=value[i];
        temp_sbn1.sign=sign;
        temp_sbn2.mycopy(sbn2.main_value);
        temp_sbn2.sign=!sbn2.sign;
        sbn3=temp_sbn1.add(temp_sbn2);
    }
}

class RSA
{
public:
    big_num big_num_seed;
    bool seed_is_set;
    RSA(){seed_is_set=false;}

    big_num create_512_big_num()
    {
        big_num the_big_num;
        srand((unsigned)time(NULL));
        for(int i=0;i<32;i++)
        {
            int random_num=rand()%65536;
            the_big_num.append(random_num,i);
        }
        return the_big_num;
    }

    big_num create_512_prime()
    {
        big_num the_big_num;
        while(1)
        {
            if(seed_is_set=false)
            {
                the_big_num=create_512_big_num();
                seed_is_set=true;
            }
            else
            {
                big_num two(2);
                the_big_num=big_num_seed.add(two);
            }
            the_big_num.value[512]=1;
            the_big_num.value[1023]=1;
            big_num_seed.mycopy(the_big_num);
            if(!the_big_num.is_prime())continue;
            break;
        }
        return the_big_num;
    }

    big_num inverse_mod(big_num _ori,big_num _mod_num)
    {//extend-ecuild-algorithm


    }
};
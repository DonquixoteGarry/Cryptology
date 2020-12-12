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
        for(int i=0;i<1024-step;i++)
            bn3.value[i]=value[i+step];
        for(int i=1024-step;i<1024;i++)
            bn3.value[i]=0;
        return bn3;
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
        bool result;
        for(int i=0;i<1024;i++)
            ori.value[i]=value[i];
        diff=ori.sub(maybe_same);
        result=ori.is_zero();
        //if(result) cout<<"the same\n";
        //else cout<<"not the same\n";
        return result;
    }

    bool is_prime(int _times=21)
    {   //use Miller-Rabin test
        //two_times :2's times,is the k of (x=2^k * m)
        //odd: the odd m of (x=2^k * m)
        //use to big prime>1000
        int prime_array[21]={3,5,7,11, 13,17,19,23,29, 31,37,41,43,47, 53,59,61,67,71, 73,79};
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
        odd.short_print("odd=");
        two_times.short_print("time=");
        //int times=_times;
        
        /*
            code
        */
        return true;
    }

};

class RSA
{
public:
    big_num big_num_seed;
    bool seed_is_set;

    big_num create_512_big_num()
    {
        big_num the_big_num;
        srand((unsigned)time(NULL));
        for(int i=0;i<32;i++)
        {
            int random_num=rand()%65536;
            //cout<<"random is"<<oct_num<<endl;
            the_big_num.append(random_num,i);
        }
        the_big_num.value[512]=1;
        the_big_num.value[1023]=1;
        return the_big_num;
    }

    bool prime_test(big_num maybe_prime)
    {
        return maybe_prime.is_prime();
    }
};
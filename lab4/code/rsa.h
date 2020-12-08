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

    void mycopy(big_num* origin)
    {
        for(int i=0;i<1024;i++)
            value[i]=origin->value[i];
    }

    //roll_order=0 means first append
    //use to generate 512-bit prime
    void append(int append_value,int roll_order)
    {   int temp=append_value;
        for(int i=15;i>=0;i++)
        {
            int temp2=temp;
            temp=temp%(pow(2,i));
            if(temp==temp2) value[1024+roll_order*16+15-i]=0;
            else value[1024+roll_order*16+15-i]=1;
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

            if((temp_sum==0)&&(temp_sum=-2) bn3.value[i]=0;
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
        int temp_sum;
        for(int i=0;i<1024;i++)
        {
            if(value[i]==1)
            {
                temp_sum=bn2.left_shift(1023-i);
                mul_result=mul_result.add(temp_sum);
            }
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

    big_num mod(big_num bn2)
    {
        big_num bn3;
        bn3.mycopy(this);
        int max_step;

        for(int i=0;i<1024;i++)
        {
            if(value[i]) max_step=i;
            if(bn2.value[i])
            {
                max_step=i-max_step;
                break;
            }
        }
        for(int i=max_step;i<=0;i--)
        {
            if(bn3.more(bn2.left_shift(i)))
                bn3=bn3.sub(bn2.left_shift(i));
        }
        return bn3;
    }

    bool is_zero()
    {
        for(int i=0;i<1024;i++)
            if(value[i]==1) return false;
        return true;
    }

}

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
            int oct_num=rand()%65536;
            big_num.append(oct_num,i);
        }
        return big_num;
    }



    bool prime_test(big_num maybe_prime)
    {

    }
}
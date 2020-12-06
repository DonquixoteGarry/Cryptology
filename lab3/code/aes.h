#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include "array.h"

using namespace std;

// f/codefiles/cryptology/lab3/code
//reference: https://blog.csdn.net/gulang03/article/details/81175854

class AES
{//AES-128
public:
    //string aes_plaintext,
    string aes_key;
    string aes_44_row_key;
    //aes_encrypt_text;
    bool aes_key_is_set;
    map<char, string> hex_binary_map;
	map<string, string> binary_hex_map;
    map<char, int> hex_order_map;
    AES()
    {
        aes_key_is_set=false;

        hex_binary_map['0'] = "0000"; hex_binary_map['1'] = "0001"; hex_binary_map['2'] = "0010"; 
		hex_binary_map['3'] = "0011"; hex_binary_map['4'] = "0100"; hex_binary_map['5'] = "0101"; 
		hex_binary_map['6'] = "0110"; hex_binary_map['7'] = "0111"; hex_binary_map['8'] = "1000"; 
		hex_binary_map['9'] = "1001"; hex_binary_map['A'] = "1010"; hex_binary_map['B'] = "1011"; 
		hex_binary_map['C'] = "1100"; hex_binary_map['D'] = "1101"; hex_binary_map['E'] = "1110"; 
		hex_binary_map['F'] = "1111"; hex_binary_map['a'] = "1010"; hex_binary_map['b'] = "1011"; 
		hex_binary_map['c'] = "1100"; hex_binary_map['d'] = "1101"; hex_binary_map['e'] = "1110"; 
		hex_binary_map['f'] = "1111";
		
		binary_hex_map["0000"] = "0"; binary_hex_map["0001"] = "1"; binary_hex_map["0010"] = "2"; 
		binary_hex_map["0011"] = "3"; binary_hex_map["0100"] = "4"; binary_hex_map["0101"] = "5"; 
		binary_hex_map["0110"] = "6"; binary_hex_map["0111"] = "7"; binary_hex_map["1000"] = "8"; 
		binary_hex_map["1001"] = "9"; binary_hex_map["1010"] = "a"; binary_hex_map["1011"] = "b"; 
		binary_hex_map["1100"] = "c"; binary_hex_map["1101"] = "d"; binary_hex_map["1110"] = "e"; 
		binary_hex_map["1111"] = "f";

        hex_order_map['0'] = 0 ; hex_order_map['1'] = 1 ; hex_order_map['2'] = 2 ;
        hex_order_map['3'] = 3 ; hex_order_map['4'] = 4 ; hex_order_map['5'] = 5 ;
        hex_order_map['6'] = 6 ; hex_order_map['7'] = 7 ; hex_order_map['8'] = 8 ;
        hex_order_map['9'] = 9 ; hex_order_map['A'] = 10; hex_order_map['B'] = 11;
        hex_order_map['C'] = 12; hex_order_map['D'] = 13; hex_order_map['E'] = 14;
        hex_order_map['F'] = 15; hex_order_map['a'] = 10; hex_order_map['b'] = 11;
        hex_order_map['c'] = 12; hex_order_map['d'] = 13; hex_order_map['e'] = 14;
        hex_order_map['f'] = 15; 
    }

    void set_key(string input_key)
    {
        aes_key = mycopy(input_key);
        aes_key_is_set = true;
        aes_44_row_key=key_extend(aes_key);
    }

    //extend the 4-row key to 44-row key
    //32-hex to 32-hex
    string key_extend(string key_4_row)
    {
        string key_44_row=mycopy(key_4_row);
        int roll_order=0;
        for(int row=4;row<44;row++)
        {
            if(row%4==0)
            {
                //key_44_row+=bin_hex_sub(bin_xor(hex_bin_sub(select_row_key(key_44_row,row-4)),hex_bin_sub(row_T_func(select_row_key(key_44_row,row-1)),roll_order)));
                key_44_row+=hex_xor(select_row_key(key_44_row,row-4),row_T_func(select_row_key(key_44_row,row-1),roll_order));
                
                roll_order++;
            }    
            else
            {   
                //key_44_row+=bin_hex_sub(bin_xor(hex_bin_sub(select_row_key(key_44_row,row-4)),hex_bin_sub(select_row_key(key_44_row,row-1))));
                key_44_row+=hex_xor(select_row_key(key_44_row,row-4),select_row_key(key_44_row,row-1));
            }
        }
        return key_44_row;
    }

    //use to copy
    string mycopy(string input)
    {
        string output;
        for (int i = 0; i<input.size(); i++)
			output.push_back(input[i]);
        return output;
    }

    //trans the hex text to binary text by a certain map
	string hex_bin_sub(string input)
	{
		string output;
		for (int i = 0; i<input.size(); i++)
			output += hex_binary_map[input[i]];
		return output;
	}

	//trans the binary text to hex text by a certain map
	string bin_hex_sub(string input)
	{
		string output;
		for (int i = 0; i<input.size() / 4; i++)
		{
			string temp;
			for (int k = i * 4; k<(i + 1) * 4; k++)
				temp.push_back(input[k]);
			output += binary_hex_map[temp];
		}
		return output;
	}
    
    //left shift for string (binary) ,as an alternative of "<<"
    string left_shift(string origin,int shift_step)
    {
        string output;
        for(int i=0;i<origin.size();i++)
            output+='0';
        if(shift_step==0) 
            return mycopy(origin);
        else
        {
            for(int i=0;i<origin.size()-shift_step;i++)
                output[i]=origin[i+shift_step];
        }
        return output;
    }

    //loop left shift for row (hex)
    string row_loop_left_shift(string origin_hex,int shift_step)
    {
        string output;
        for(int i=shift_step;i<origin_hex.size();i++)
            output.push_back(origin_hex[i]);
        for(int i=0;i<shift_step;i++)
            output.push_back(origin_hex[i]);
        return output;
    }

    //xor for string (binary) ,as an alternative of "^"
    string bin_xor(string bin_op1,string bin_op2)
    {
        string output;
        for(int i=0;i<bin_op1.size();i++)
        {
            if(bin_op1[i]==bin_op2[i])
                output+='0';
            else
                output+='1';
        }
        return output;
    }
    
    //
    string hex_xor(string hex_op1,string hex_op2)
    {
        string output1,output2;
        string bin_op1=hex_bin_sub(hex_op1);
        string bin_op2=hex_bin_sub(hex_op2);
        output1=bin_xor(bin_op1,bin_op2);
        output2=bin_hex_sub(output1);
        return output2;
    }

    //8-bit multiply with 8-bit in GF(8)
    //2-hex,2-hex to 2-hex
    string byte_multi(string hex_op1,string hex_op2)
    {
        string bin_op1 = hex_bin_sub(hex_op1);
        string bin_op2 = hex_bin_sub(hex_op2);
        string output = "00000000";
        string array[8];
        array[0]=mycopy(bin_op1);
        for(int i=1;i<8;i++)
        {
            if(array[i-1][0]=='1')
                array[i]=bin_xor(left_shift(array[i-1],1),"00011011");
            else
                array[i]=left_shift(array[i-1],1);
        }

        for(int i=0;i<8;i++)
        {
            if(bin_op2[7-i]=='1')
                output=bin_xor(output,array[i]);
        }
        output=bin_hex_sub(output);
        return output;
    }

    //byte substitution
    //32-hex to 32-hex
    string byte_sub(string input)
    {
        string output;
        for(int i=0;i<input.size()/2;i++)
        {
            char temp1,temp2;
            string temp_main;
            for(int j=i*2;j<i*2+2;j++)
            {
                temp1=input[i*2];
                temp2=input[i*2+1];
                temp_main=mycopy(S_box[hex_order_map[temp1]][hex_order_map[temp2]]);
            }
            output += temp_main;
        }
        return output;
    }

    //reversed byte substitution
    //32-hex to 32-hex
    string rev_byte_sub(string input)
    {
        string output;
        for(int i=0;i<input.size()/2;i++)
        {
            char temp1,temp2;
            string temp_main;
            for(int j=i*2;j<i*2+2;j++)
            {
                temp1=input[i*2];
                temp2=input[i*2+1];    
                temp_main=mycopy(revS_box[hex_order_map[temp1]][hex_order_map[temp2]]);
            }
            output += temp_main;
        }
        return output;
    }

    //row shift substitution
    //there obey AES-128's rule (below)
    //32-hex to 32-hex 
    string row_shift(string input)
    {
        string output;
        for(int i=0;i<16;i++)
        {
            for(int j=2*row_shift_list[i];j<2*row_shift_list[i]+2;j++)
                output+=input[j];
        }
        return output;
    }

    //reversed row shift substitution
    //there obey AES-128's rule (below)
    //32-hex to 32-hex
    string rev_row_shift(string input)
    {
        string output;
        for(int i=0;i<16;i++)
        {
            for(int j=2*rev_row_shift_list[i];j<2*rev_row_shift_list[i]+2;j++)
                output+=input[j];
        }
        return output;
    }

    //select certain byte in target row and column
    //32-hex to 2-hex(selected)
    string select_byte(string hex_input,int row_order,int column_order)
    {
        string output,temp;
        temp+=hex_input[8*row_order+2*column_order];
        temp+=hex_input[8*row_order+2*column_order+1];
        output=mycopy(temp);
        return output;
    }

    //select certain row in target row
    //32-hex to 8-hex(selected)
    string select_row_key(string hex_input,int row_order)
    {
        string output;
        for(int i=0;i<4;i++)
            output+=select_byte(hex_input,row_order,i);
        return output;
    }

    //select roll key(128-bin,32-hex,4-row) in 44-row whole key
    //roll order=0 means first roll key (different from initial 128-bin key)
    string select_roll_key(string key_44_row,int roll_order)
    {
        string output;
        for(int i=0;i<4;i++)
            output+=select_row_key(key_44_row,roll_order*4+i+4);
        return output;
    }

    //TODO this code might be wrong(make mistakes about column or row )
    //column mix substitution
    //multiply with certain matrix in GF(8),byte with byte,8-bit with 8-bit)
    //trans 32-hex to 32-hex
    //already debugged
    string column_mix(string input)
    {
        string output;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                string temp="00";
                for(int k=0;k<4;k++)
                    temp=hex_xor(temp,byte_multi(select_byte(input,i,k),column_mix_list[k][j]));
                output+=temp;
            }
        }
        return output;
    }

    //debugged
    string rev_column_mix(string input)
    {
        string output;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                string temp="00";
                for(int k=0;k<4;k++)
                    temp=hex_xor(temp,byte_multi(select_byte(input,i,k),rev_column_mix_list[k][j]));
                output+=temp;
            }
        }
        return output;
    }

    //T function to row
    //8-hex(a row) to 8-hex
    //roll_order is 0 means first roll
    string row_T_func(string input_row,int roll_order)
    {
        string temp1=row_loop_left_shift(input_row,2);
        string temp2=byte_sub(temp1);
        string temp3=hex_xor(temp2,row_const[roll_order]);
        return temp3;
    }
    
    //32-hex,32-hex to 32-hex
    string  _aes_encrypt(string _aes_key,string aes_plaintext)
    {
        set_key(_aes_key);
        string temp1=hex_xor(aes_plaintext,_aes_key);
        
        string roll_temp=mycopy(temp1);
        for(int i=0;i<9;i++)
        {
            roll_temp=byte_sub(roll_temp);
            roll_temp=row_shift(roll_temp);
            roll_temp=column_mix(roll_temp);
            roll_temp=hex_xor(select_roll_key(aes_44_row_key,i),roll_temp);
        }

        string temp2=mycopy(roll_temp);
        temp2=byte_sub(temp2);
        temp2=row_shift(temp2);
        temp2=hex_xor(select_roll_key(aes_44_row_key,9),temp2);
        string output=mycopy(temp2);
        return output;
    }

    string _aes_decrypt(string _aes_key,string aes_plaintext)
    {
        set_key(_aes_key);
        string temp1=hex_xor(aes_plaintext,select_roll_key(aes_44_row_key,9));
        
        string roll_temp=mycopy(temp1);
        for(int i=8;i>=0;i--)
        {
            roll_temp=rev_row_shift(roll_temp);
            roll_temp=rev_byte_sub(roll_temp);
            roll_temp=hex_xor(select_roll_key(aes_44_row_key,i),roll_temp);
            roll_temp=rev_column_mix(roll_temp);
            
        }

        string temp2=mycopy(roll_temp);
        temp2=rev_row_shift(temp2);
        temp2=rev_byte_sub(temp2);
        temp2=hex_xor(_aes_key,temp2);
        string output=mycopy(temp2);
        return output;
    }

    //count how many nyte
    //32-hex,32-hex to int
    int change_bit(string origin,string other)
    {
        string bin_origin=hex_bin_sub(origin);
        string bin_other=hex_bin_sub(other);

        int count=0;
        for(int i=0;i<bin_origin.size();i++)
        {
            if(bin_origin[i]!=bin_other[i])
                count++;
        }
        return count;
    }


};
#include <map>
#include <iostream>
#include <string>
#include <cmath>
#include "array.h"

using namespace std;

class AES
{//AES-128
public:
    string aes_plaintext,aes_key,aes_encrypt_text;
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
        aes_key = copy(input_key);
        aes_key_is_set = true;
    }
    //use to copy
    string copy(string input)
    {
        string output;
        for (int i = 0; i<input.size(); i++)
			output += input[i];
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
        for(int i=0;i<strlen(origin);i++)
            output+='0';
        if(shift_step==0) 
            return copy(origin);
        else
        {
            for(int i=0;i<strlen(origin)-shift_step;i++)
                output[i]=origin[i+shift_step];
        }
        return output;
    }

    //xor for string (binary) ,as an alternative of "^"
    string bin_xor(string bin_op1,string bin_op2)
    {
        string output;
        for(int i=0;i<strlen(bin_op1);i++)
        {
            if(bin_op1[i]==bin_op2[i])
                output+='0';
            else
                output+='1';
        }
        return output;
    }

    //8-bit multiply with 8-bit in GF(8)
    //2-hex,2-hex to 8-bin
    string byte_multi(string hex_op1,string hex_op2)
    {
        string bin_op1 = hex_bin_sub(hex_op1);
        string bin_op2 = hex_bin_sub(hex_op2);
        string output = "00000000";
        for(int i=0;i<8;i++)
        {
            if(bin_op2[7-i]=='1')
                output=bin_xor(output,left_shift(bin_op1,i));
        }
        return output;
    }

    //byte substitution
    //32-hex to 32-hex
    void byte_sub(string input,string output)
    {
        for(int i=0;i<16;i++)
        {
            char temp1,temp2;
            string temp_main;
            for(int j=i*2;j<i*2+2;j++)
            {
                temp1=input[i*2];
                temp2=input[i*2+1];
                temp_main=copy(S_box[hex_order_map[temp1]][hex_order_map[temp2]]);
            }
            output += temp_main;
        }
    }

    //reversed byte substitution
    //32-hex to 32-hex
    void rev_byte_sub(string input,string output)
    {
        for(int i=0;i<16;i++)
        {
            char temp1,temp2;
            string temp_main;
            for(int j=i*2;j<i*2+2;j++)
            {
                temp1=input[i*2];
                temp2=input[i*2+1];    
                temp_main=copy(revS_box[hex_order_map[temp1]][hex_order_map[temp2]]);
            }
            output += temp_main;
        }
    }

    //row shift substitution
    //there obey AES-128's rule (below)
    //32-hex to 32-hex 
    void row_shift(string input,string output)
    {
        for(int i=0;i<16;i++)
        {
            for(int j=2*row_shift_list[i];j<2*row_shift_list[i]+2;j++)
                output+=input[j];
        }
    }

    //reversed row shift substitution
    //there obey AES-128's rule (below)
    //32-hex to 32-hex
    void rev_row_shift(string input,string output)
    {
        for(int i=0;i<16;i++)
        {
            for(int j=2*rev_row_shift_list[i];j<2*rev_row_shift_list[i]+2;j++)
                output+=input[j];
        }
    }

    //select certain byte in target row and column
    //32-hex to 8-bin(selected)
    string select_byte(string hex_input,int row_order,int column_order)
    {
        string output.temp;
        temp+=hex_input[8*i+2*j];
        temp+=hex_input[8*i+2*j+1];
        output=hex_bin_sub(temp);
        return output;
    }

    //TODO this code might be wrong(make mistakes about column or row )
    //column mix substitution
    //multiply with certain matrix in GF(8),byte with byte,8-bit with 8-bit)
    //trans 32-hex to 32-hex
    void column_mix(string input,string output)
    {
        string output;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                string temp="00000000";
                for(int k=0;k<4;k++)
                    temp=bin_xor(temp,byte_multi(column_mix_list[i][k],column_mix_list[k][j]));
                output+=bin_hex_sub(temp);
            }
        }
    }

    //TODO similar with column_mix
    void rev_column_mix(string input,string output)
    {
        string output;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                string temp="00000000";
                for(int k=0;k<4;k++)
                    temp=bin_xor(temp,byte_multi(rev_column_mix_list[i][k],rev_column_mix_list[k][j]));
                output+=bin_hex_sub(temp);
            }
        }
    }

    


};
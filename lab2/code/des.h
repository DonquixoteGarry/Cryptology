#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include "array.h"

using namespace std;

class DES
{
public:
	int des_plaintext[64], des_encrypt_text[64], des_key[64];
	bool des_key_is_set;
	map<char, string> hex_binary_map;
	map<string, string> binary_hex_map;
	DES()
	{
		des_key_is_set = false;

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
	}
	
	// to set the key , type 'bin' to input binary key , type 'hex' to input hex key
	void set_key(string key, string type)
	{
		des_key_is_set = true;
		if (type == "hex") key = hex_bin_sub(key);
		for (int i = 0; i<key.size(); i++)
			des_key[i] = key[i] - '0';
		return;
	};                                	
	
	// to encrypt input plaintext and return encrypted text,
	// by the way of certain kind of input type(input_type) or output type(output_type)
	string encrypt(string input, string input_type, string output_type)
	{
		if (!des_key_is_set)
		{
			cout<<"no key set yet"<<endl;
			return 0;
		}
		input = (input_type == "hex") ? hex_bin_sub(input) : input;
		for (int i = 0; i<input.size(); i++)
			des_plaintext[i] = input[i] - '0';

		des_deal(des_plaintext, des_encrypt_text, des_key);

		string output;
		for (int i = 0; i<64; i++)
			output.push_back(des_encrypt_text[i] + '0');

		output = (output_type == "hex") ? bin_hex_sub(output) : output;
		return output;
	}

	// to decrypt input encrypted text and return plaintext,
	// by the way of certain kind of input type(input_type) or output type(output_type)
	string decrypt(string input, string input_type, string output_type)
	{
		if (!des_key_is_set)
		{
			cout<<"no key set yet"<<endl;
			return 0;
		}
		input = (input_type == "hex") ? hex_bin_sub(input) : input;
		for (int i = 0; i<input.size(); i++)
			des_encrypt_text[i] = input[i] - '0';

		de_des_deal(des_encrypt_text, des_plaintext, des_key);

		string output;
		for (int i = 0; i<64; i++)
			output.push_back(des_plaintext[i] + '0');

		output = (output_type == "hex") ? bin_hex_sub(output) : output;
		return output;
	}

	//get the key
	string getkey(string type)
	{
		string key;
		for (int i = 0; i<key.size(); i++)
			key.push_back(des_key[i] + '0');
		return key;
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

	//the IP(initial permutation)
	void IP(const int input[64], int output[64])
	{																																																	//然后，进行置换并生成IP置换结果
		for (int i = 0; i<64; i++)
			output[i] = input[IP_list[i] - 1];
		return;
	}

	//the E-expand , expand the 32-bit to 48-bit
	void e_sub(const int input[32], int output[48])
	{
		for (int i = 0; i<48; i++)
			output[i] = input[E_expand_list[i] - 1];
		return;
	}

	//the left-shift at binary type
	void leftshift(int left_shift_list[56], int shift_step)
	{
		int temp2[56];
		for (int i = 0; i<28; i++)
			temp2[i] = left_shift_list[(i + shift_step) % 28];
		for (int i = 28; i<56; i++)
			temp2[i] = left_shift_list[(i - 28 + shift_step) % 28 + 28];
		for (int i = 0; i<56; i++)
			left_shift_list[i] = temp2[i];
		return;
	}

	//the key substitution at a certain roll_order(0-15)
	//different roll left-shift different bits
	//trans 64-bit key to 48-bit key
	void keyRollSub(int roll_order, const int input[64], int output[48])
	{
		int temp[56];
		for (int i = 0; i<56; i++)
			temp[i] = input[PC_1_list[i] - 1];
		for (int i = 0; i<roll_order; i++)
			leftshift(temp, roll_step_list[i]);
		for (int i = 0; i<48; i++)
			output[i] = temp[PC_2_list[i] - 1];
		return;
	}

	//the S box substitution
	//trans 48-bit  to 32-bit 
	void s_box_sub(const int input[48], int output[32])
	{	
		for (int i = 0; i<8; i++)
		{
			int row = input[i * 6] * 2 + input[i * 6 + 5] * 1;
			int col = input[i * 6 + 1] * 8 + input[i * 6 + 2] * 4 + input[i * 6 + 3] * 2 + input[i * 6 + 4] * 1;
			int res = S_Box[i][row][col];
			for (int k = 3; k >= 0; k--)
			{
				output[i * 4 + k] = res % 2;
				res /= 2;
			}
		}
		return;
	}

	//the P box substitution
	//trans 32-bit  to 32-bit 
	void p_box_sub(const int input[32], int output[32])
	{
		for (int i = 0; i<32; i++)
			output[i] = input[P_box[i] - 1];
		return;
	}

	//the reversed IP
	void revIP(const int input[64], int output[64])
	{
		for (int i = 0; i<64; i++)
			output[i] = input[revIP_list[i] - 1];
		return;
	}

	//single-roll encrypt by using key at a certain roll(0-15)
	//64-bit input divide to two parts (left 32-bit/right 32 bit) and process differently
	//return two parts of 32-bit text(encrypted)
	void roll_sub(const int left_input[32], const int right_input[32], int left_output[32], int right_output[32], int roll_key[48])
	{
		for (int i = 0; i<32; i++) 
			left_output[i] = right_input[i];
		
		int right_input_2[48];
		e_sub(right_input, right_input_2);
		
		int right_input_3[48];
		for (int i = 0; i<48; i++) 
			right_input_3[i] = right_input_2[i] ^ roll_key[i];
		
		int right_input_4[32],right_input_5[32];
		s_box_sub(right_input_3, right_input_4);
		p_box_sub(right_input_4, right_input_5);
		
		int right_input_6[32];
		for (int i = 0; i<32; i++) 
			right_input_6[i] = right_input_5[i] ^ left_input[i];

		for (int i = 0; i<32; i++) 
			right_output[i] = right_input_6[i];
	}

	//whole des-encrypt
	void des_deal(int input[64], int output[64], int key[64])
	{
		int input_2[64];
		IP(input, input_2);
		int left_input[32], right_input[32], left_output[32], right_output[32], roll_key[48];
		for (int i = 0; i<64; i++)
		{
			if (i >= 0 && i<32)
				left_input[i] = input_2[i];
			else
				right_input[i - 32] = input_2[i];
		}
		for (int i = 1; i <= 16; i++)
		{
			keyRollSub(i, key, roll_key);
			roll_sub(left_input, right_input, left_output, right_output, roll_key);
			for (int i = 0; i<32; i++)
			{
				left_input[i] = left_output[i];
				right_input[i] = right_output[i];
			}
		}
		int tempres[64];
		for (int i = 0; i<64; i++)
		{
			if (i >= 0 && i<32)
				tempres[i] = right_output[i];
			else
				tempres[i] = left_output[i - 32];
		}
		revIP(tempres, output);
		return;
	}

	//whole des-encrypt
	void de_des_deal(int input[64], int output[64], int key[64])
	{
		int input_2[64];
		IP(input, input_2);
		int left_input[32], right_input[32], left_output[32], right_output[32], roll_key[48];
		for (int i = 0; i<64; i++)
		{
			if (i >= 0 && i<32)
				left_input[i] = input_2[i];
			else
				right_input[i - 32] = input_2[i];
		}
		for (int i = 16; i >= 1; i--)
		{
			keyRollSub(i, key, roll_key);   
			roll_sub(left_input, right_input, left_output, right_output, roll_key);
			for (int i = 0; i<32; i++)
			{
				left_input[i] = left_output[i];
				right_input[i] = right_output[i];
			}
		}
		int tempres[64];
		for (int i = 0; i<64; i++)
		{
			if (i >= 0 && i<32)
				tempres[i] = right_output[i];
			else
				tempres[i] = left_output[i - 32];
		}
		revIP(tempres, output);
		return;
	}
};

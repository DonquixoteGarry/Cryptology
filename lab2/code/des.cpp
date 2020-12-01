#include "des.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	while (1) 
	{	
		cout << "1 to encrpty / " << "2 to decrpty / "<< "3 to test avalanche effect / "<< "4 to quit" << endl;
		int op_flag;
		cin >> op_flag;
		if (op_flag == 1)
		{
			DES des = DES();
			string plaintext,key,encrypt_text;
			cout << "plaintext(16 hex chars):";
			cin >> plaintext;
			cout << "key(16 hex chars):";
			cin >> key;
			des.set_key(key, "hex");
			encrypt_text = des.encrypt(plaintext, "hex", "hex");
			cout << "encrypt result(16 hex chars): " << encrypt_text << endl;
		}
		if (op_flag == 2)
		{
			DES des = DES();
			string plaintext,key,encrypt_text;
			cout << " encrypt_text(16 hex chars):";
			cin >> encrypt_text;
			cout << "key(16 hex chars):";
			cin >> key;
			plaintext = des.decrypt(encrypt_text, "hex", "hex");
			cout << "decrypt result(16 hex chars): " << plaintext << endl;
		}
		if (op_flag == 3)
		{
			DES des = DES();
			string plaintext,key,encrypt_text;
			int change_sum=0;
			cout << "plaintext(16 hex chars):";
			cin >> plaintext;
			
			cout << "key(16 hex chars):";
			cin >> key;

			des.set_key(key, "hex");

			encrypt_text = des.encrypt(plaintext, "hex", "hex");
			cout << "encrypt result(16 hex chars): " << encrypt_text << endl;

			string bin_plaintext = des.hex_bin_sub(plaintext);
			string bin_key = des.hex_bin_sub(key);

			for (int i = 0; i <= 7; i++)
			{
				DES des1 = DES();
				string plaintext1,encrypt_text1,bin_encrypt_text1,bin_encrypt_text;
				if (bin_plaintext[i] == '0') bin_plaintext[i] = '1';
				else bin_plaintext[i] = '0';
				
				des1.set_key(key, "hex");
				
				plaintext1 = des1.bin_hex_sub(bin_plaintext);
				encrypt_text1 = des1.encrypt(plaintext1, "hex", "hex");
				bin_encrypt_text1 = des1.hex_bin_sub(encrypt_text1);
				bin_encrypt_text = des1.hex_bin_sub(encrypt_text);
				
				int change_once = 0;
				for (int j = 0; j <= bin_encrypt_text.length(); j++)
					if (bin_encrypt_text1[j] != bin_encrypt_text[j]) change_once++;
					
				cout << "plaintext changed " << i + 1 << " bits " << ",cryped_text changed "<<change_once<<" bits"<<endl;;
				change_sum += change_once;
			}

			cout << endl << endl;
			for (int i = 0; i <= 7; i++)
			{
				DES des1 = DES();
				string key1,encrypt_text1,bin_encrypt_text1,bin_encrypt_text;
				if (bin_key[i] == '0') bin_key[i] = '1';
				else bin_key[i] = '0';
				key1 = des1.bin_hex_sub(bin_key);
				des1.set_key(key1, "hex");

				encrypt_text1 = des1.encrypt(plaintext, "hex", "hex");
				bin_encrypt_text1 = des1.hex_bin_sub(encrypt_text1);
				bin_encrypt_text = des1.hex_bin_sub(encrypt_text);

				int change_once = 0;
				for (int j = 0; j <= 63; j++)
					if (bin_encrypt_text1[j] != bin_encrypt_text[j]) change_once++;

				cout << "key changed " << i + 1 << " bits" << ",cryped_text " << change_once<<" bits" << endl;;
				change_sum += change_once;
			}
			cout << endl << "average is changing " << float(change_sum) / 16.00 <<"  bits\n";
		}
		if (op_flag == 4) break;
		system("pause");
		cout << "\n-----new process going-----\n" << endl;
	}
	return 0;

}
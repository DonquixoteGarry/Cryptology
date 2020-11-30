#include "mydes.h"
#include <iostream>
#include <string>
/**********对于数据初始置换过程的声明****************/

//数据初始置换表

using namespace std;

int main(void)
{
	while (1) 
	{	
		cout << "1 to encrpty / " << "2 to decrpty / "<< "3 to test avalanche effect / "<< "4 to quit" << endl;
		int choose;
		cin >> choose;
		if (choose == 1)
		{
			DES des = DES();
			string plaintext,key,enpt;
			cout << "plaintext(16 hex chars):";
			cin >> plaintext;
			cout << "key(16 hex chars):";
			cin >> key;
			des.key(key, "0x");
			enpt = des.encrypt(plaintext, "0x", "0x");
			cout << "encrypt result(16 hex chars): " << enpt << endl;

		}
		if (choose == 2)
		{
			DES des = DES();
			string plaintext,key,enpt;
			cout << " enpt(16 hex chars):";
			cin >> enpt;
			cout << "key(16 hex chars):";
			cin >> key;
			plaintext = des.decrypt(enpt, "0x", "0x");
			cout << "decrypt result(16 hex chars): " << plaintext << endl;

		}
		if (choose == 3)
		{
			DES des = DES();
			string plaintext,key,enpt;
			int total=0, average=0;
			cout << "plaintext(16 hex chars):";
			cin >> plaintext;
			
			cout << "key(16 hex chars):";
			cin >> key;

			des.key(key, "0x");

			enpt = des.encrypt(plaintext, "0x", "0x");
			cout << "encrypt result(16 hex chars): " << enpt << endl;

			string binplaintext = des.hexToBinary(plaintext);
			string binkey = des.hexToBinary(key);

			for (int i = 0; i <= 7; i++)
			{
				DES des1 = DES();
				string plaintext1,enpt1,binenpt1,binenpt;
				if (binplaintext[i] == '0') binplaintext[i] = '1';
				else binplaintext[i] = '0';
				
				des1.key(key, "0x");
				
				plaintext1 = des1.binToHexto(binplaintext);
				enpt1 = des1.encrypt(plaintext1, "0x", "0x");
				binenpt1 = des1.hexToBinary(enpt1);
				binenpt = des1.hexToBinary(enpt);
				
				int change = 0;
				for (int j = 0; j <= binenpt.length(); j++)
				{
					
					if (binenpt1[j] != binenpt[j]) change++;
				}
				cout << "plaintext changed " << i + 1 << " bits " << ",cryped_text changed "<<change<<" bits"<<endl;;
				total += change;
			}

			cout << endl << endl;
			for (int i = 0; i <= 7; i++)
			{
				DES des1 = DES();
				string key1,enpt1,binenpt1,binenpt;
				if (binkey[i] == '0') binkey[i] = '1';
				else binkey[i] = '0';
				key1 = des1.binToHexto(binkey);
				des1.key(key1, "0x");

				enpt1 = des1.encrypt(plaintext, "0x", "0x");
				binenpt1 = des1.hexToBinary(enpt1);
				binenpt = des1.hexToBinary(enpt);
				int change = 0;
				for (int j = 0; j <= 63; j++)
				{
					if (binenpt1[j] != binenpt[j]) change++;
				}

				cout << "key changed " << i + 1 << " bits" << ",cryped_text " << change<<" bits" << endl;;
				total += change;
			}
			cout << endl << "average is changing " << float(total) / 16.00 <<"  bits\n";
		}
		if (choose == 4) break;
		cout << "\n-----new process going-----\n" << endl;
	}
	return 0;

}
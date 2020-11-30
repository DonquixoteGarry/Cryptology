#include "mydes.h"
#include <iostream>
#include <string>
/**********对于数据初始置换过程的声明****************/

//数据初始置换表

using namespace std;

int main(void)
{

	/*int result_key[16][48];//十六轮的子密钥存储在这个二维数组中
	int initial_key[64]={0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	};

	get_key(initial_key,result_key);//计算获取了16个轮密钥

	//输出16个轮密钥
	for (int i = 0; i <= 15; i++)
	{
	cout << "第" << i + 1 << "轮的论密钥结果为:    ";
	for (int j = 0; j <= 47; j++)
	{
	cout << result_key[i][j];
	}
	cout << endl;
	}

	int data[64] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	};
	initial_trans(data);
	int R_data[32];
	int L_data[32];
	data_separate(data,  R_data,  L_data);

	for (int i = 0; i <= 15; i++) turn_function(R_data,  L_data, i,   result_key);

	for (int i = 0; i <= 31; i++)
	{
	data[i] = L_data[i];
	data[i + 32] = R_data[i];
	}
	reinitial_trans(data);
	for (int i = 0; i < 63; i++)
	cout << data[i];*/
	while (1) {
		
		cout << "select menu:" << endl;
		cout << "1.encrpty:" << endl;
		cout << "2.decrpty:" << endl;
		cout << "3:Avalanche effect" << endl;
		cout << "4:quit" << endl;
		int choose;
		cin >> choose;
		if (choose == 1)
		{
			string plain;
			cout << "plain:";
			cin >> plain;
			string key;
			cout << "key:";
			cin >> key;
			string enpt;

			DES des = DES();
			des.key(key, "0x");

			enpt = des.encrypt(plain, "0x", "0x");
			cout << "encrypt result: " << enpt << endl;

		}
		else if (choose == 2)
		{
			string enpt;
			cout << " enpt:";
			cin >> enpt;
			string key;

			cout << "key:";
			cin >> key;
			

			DES des = DES();	
			string plain;
			plain = des.decrypt(enpt, "0x", "0x");
			cout << "decrypt result: " << plain << endl;
			

		}
		else if (choose == 3)
		{

			int total=0;
			int average=0;
			string plain;
			cout << "plain:";
			cin >> plain;
			
			string key;
			cout << "key:";
			cin >> key;
			string enpt;

			DES des = DES();
			des.key(key, "0x");

			enpt = des.encrypt(plain, "0x", "0x");
			cout << "encrypt result: " << enpt << endl;



			string binplain = des.hexToBinary(plain);
			string binkey = des.hexToBinary(key);

			for (int i = 0; i <= 7; i++)
			{
				
				
					if (binplain[i] == '0') binplain[i] = '1';
					else binplain[i] = '0';
					
					DES des1 = DES();
					des1.key(key, "0x");
					
					string plain1 = des1.binToHexto(binplain);
					string enpt1;
					enpt1 = des1.encrypt(plain1, "0x", "0x");
					string binenpt1 = des1.hexToBinary(enpt1);
					string binenpt = des1.hexToBinary(enpt);
					int change = 0;
					
					for (int j = 0; j <= binenpt.length(); j++)
					{
						
						if (binenpt1[j] != binenpt[j]) change++;
					}


					cout << "plaintext changed " << i + 1 << " bits " << ",cryped_text changed "<<change<<" 位"<<endl;;
					total += change;
			}

			cout << endl << endl;
			for (int i = 0; i <= 7; i++)
			{


				if (binkey[i] == '0') binkey[i] = '1';
				else binkey[i] = '0';

				DES des1 = DES();
				string key1 = des1.binToHexto(binkey);
				des1.key(key1, "0x");

				
				string enpt1;
				enpt1 = des1.encrypt(plain, "0x", "0x");
				string binenpt1 = des1.hexToBinary(enpt1);
				string binenpt = des1.hexToBinary(enpt);
				int change = 0;
				for (int j = 0; j <= 63; j++)
				{
					if (binenpt1[j] != binenpt[j]) change++;
				}


				cout << "key changed " << i + 1 << " bits" << ",cryped_text " << change<<" bits" << endl;;
				total += change;
			}
			cout << endl << "average：" << float(total) / 16.00;
		}
		else if (choose == 4)
		{
			break;
		}
		
		cout << "another turn" << endl;
		
	}
	return 0;

}
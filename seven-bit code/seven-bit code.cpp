#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	ifstream in;
	ofstream out;
	string text = "";
	char chr;
	in.open("input.txt", ios::binary);
	out.open("output.txt", ios::binary);

	if (in.is_open())
	{
		while (in)
		{
			in.get(chr);
			text = text + chr;
		}

		text = text.substr(0, text.length() - 1);
		bool flag;
		int vib;
		cout << "Enter: 1 - encrypt; 2 - decrypt" << endl;
		cin >> vib;
		switch (vib)
		{
		case 1:
			flag = 0;
			break;
		case 2:
			flag = 1;
			break;
		default:
			cout << "Unknown command." << endl;
			system("pause");
			return 1;
			break;
		}

		if (!flag)
		{
			while (text.length() % 7 != 0)
				text = text + " ";
			for (int i = 0; i < text.length(); i += 7)
			{
				// an array with 7 characters to be encoded
				unsigned char temp[7];
				for (int j = 0; j < 7; j++)
					temp[j] = text[i + j];
				// seven-bit code
				unsigned char sevenbit = 0;
				// filling in the seven-bit code, casting to unsigned char is necessary in order for the extra bits to be discarded
				for (int j = 0; j < 7; j++)
					sevenbit = ((sevenbit << 1) | (unsigned char(temp[j] << 7) >> 7));
				// write changed symbols to file:
				// 1.the last bit is discarded
				// 2.the first j bits are discarded
				// 3.the first j - 1 bits from the next byte are added
				for (int j = 0; j < 6; j++)
				{
					unsigned char symbol = (unsigned char(temp[j] >> 1) << (j + 1)) | (temp[j + 1] >> (7 - j));
					out.write((char*)&symbol, sizeof(symbol));
				}
				// forming and writing the last byte
				sevenbit = sevenbit | (unsigned char(temp[6] >> 1) << 7);
				out.write((char*)&sevenbit, sizeof(sevenbit));
			}
		}
		else
		{
			if (text.length() % 7 != 0)
			{
				cout << "It is not possible to decrypt the file." << endl;
				system("pause");
				return 1;
			}
			for (int i = 0; i < text.length(); i += 7)
			{
				// array with 7 characters to decode
				unsigned char temp[7];
				for (int j = 0; j < 7; j++)
					temp[j] = text[i + j];
				// seven-bit code
				unsigned char sevenbit = unsigned char(temp[6] << 1) >> 1;
				// decode the character:
				// 1.the last j + 1 bits are discarded
				// 2.if not the first bit, then the last 8 - j bits from the previous byte are added
				// 3.A character from a seven-bit code is added to the end
				for (int j = 0; j < 7; j++)
				{
					unsigned char symbol = unsigned char(temp[j] >> (j + 1)) << 1 | (j != 0 ? temp[j - 1] << (8 - j) : 0) | (sevenbit >> 6);
					sevenbit = unsigned char(sevenbit << 2) >> 1;
					out.write((char*)&symbol, sizeof(symbol));
				}
			}
		}
		out.close();
		in.close();
		cout << "Done." << endl;
	}
	else
		cout << "The file is not open." << endl;
	system("pause");
	return 0;
}
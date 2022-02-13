#include <iostream>
#include <regex>
#include <fstream>
#include <string>
using namespace std;
int getInt(string textOfFile) {
	int returnValue = 0;
	for (int i = 0; i < textOfFile.length(); i++) {
		switch (textOfFile[i])
		{
		case 'I':
			returnValue += 1;
			break;
		case 'V':
			returnValue += 5;
			break;
		case 'X':
			returnValue += 10;
			break;
		case 'L':
			returnValue += 50;
			break;
		case 'C':
			returnValue += 100;
			break;
		case 'D':
			returnValue += 500;
			break;
		case 'M':
			returnValue += 1000;
			break;
		}
		if (i > 0) {
			if ((textOfFile[i] == 'V' || (textOfFile[i] == 'X')) && (textOfFile[i - 1] == 'I')) returnValue -= 2;
			if ((textOfFile[i] == 'L' || (textOfFile[i] == 'C')) && (textOfFile[i - 1] == 'X')) returnValue -= 20;
			if ((textOfFile[i] == 'M' || (textOfFile[i] == 'D')) && (textOfFile[i - 1] == 'C')) returnValue -= 200;
		}
	}
	return returnValue;
}

int main()
{
	regex rx("^(M{0,3})(D?C{0,3}|C[DM])(L?X{0,3}|X[LC])(V?I{0,3}|I[VX])$");
	setlocale(LC_ALL, "ru");
	ifstream ifile;
	int maxRomanNumeral = 0;
	string textOfFile;
	string nameOfFile;
	do {
		cout << "Введите название файла, с его расширением. (Например : test.txt)" << endl;
		getline(cin, nameOfFile);
		ifile.open(nameOfFile);
		if (!ifile) {
			cout << "Неверное имя файла." << endl;
			system("pause");
			system("cls");
		}
	} while (!ifile);
	int i = 0;
	while (ifile >> textOfFile) {
		if (regex_match(textOfFile, rx)) {
			if (getInt(textOfFile) > maxRomanNumeral) {
				maxRomanNumeral = getInt(textOfFile);
			}
		}
	}
	cout << "Максимальное римское число в тексте = " << maxRomanNumeral;
	ifile.close();
}

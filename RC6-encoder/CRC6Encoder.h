#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

/*
	Класс шифрования.
*/
class CRC6Encoder
{
private:
	int m_sizeKey; //размер ключа в байтах.
	int m_sizeText; //размер текста в байтах.

	BYTE* m_keyOfByte; //байтовое представление ключа.
	BYTE* m_textOfByte; //байтовое представление текста.

	static const int m_round=20; //число раундов.
	static const int m_w=32; //размер слова.

	static const DWORD m_Pw=0xB7E15163; //константа эпсилона.
	static const DWORD m_Qw=0x9E3779B9; //константа з. сечения.

	DWORD m_L[64]; ////массив из "c" слов ключа;	т.к. макс. размер ключа мб 8*64=256 бит.
	DWORD m_S[44]; //таблица ключей для 20 раундов (2*r+4);



	DWORD offset(DWORD ofs); //сдвиг.
	DWORD leftRotate(DWORD var, DWORD ofs); //вращение влево.
	DWORD rightRotate(DWORD var, DWORD ofs); //вращение вправо.

	BYTE* readFile(string pathFile, int& size); //чтение файла.
	void readKey(string pathToKeyFile); //считывание ключа.
	void readText(string pathToTextFile); //считывание текста.

	void extensionKey(); //расширение ключа.
	void encryptBlock(const BYTE* pIn, BYTE* pOut); //шифрование блоков текста.
	void encrypt(string pathToEncodeFile); //шифрование текста.

public:
	CRC6Encoder(string pathToKeyFile, string pathToTextFile, string pathToEncodeFile);
	CRC6Encoder();
	~CRC6Encoder();
};
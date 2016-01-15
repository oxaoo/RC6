#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

/*
	����� ����������.
*/
class CRC6Encoder
{
private:
	int m_sizeKey; //������ ����� � ������.
	int m_sizeText; //������ ������ � ������.

	BYTE* m_keyOfByte; //�������� ������������� �����.
	BYTE* m_textOfByte; //�������� ������������� ������.

	static const int m_round=20; //����� �������.
	static const int m_w=32; //������ �����.

	static const DWORD m_Pw=0xB7E15163; //��������� ��������.
	static const DWORD m_Qw=0x9E3779B9; //��������� �. �������.

	DWORD m_L[64]; ////������ �� "c" ���� �����;	�.�. ����. ������ ����� �� 8*64=256 ���.
	DWORD m_S[44]; //������� ������ ��� 20 ������� (2*r+4);



	DWORD offset(DWORD ofs); //�����.
	DWORD leftRotate(DWORD var, DWORD ofs); //�������� �����.
	DWORD rightRotate(DWORD var, DWORD ofs); //�������� ������.

	BYTE* readFile(string pathFile, int& size); //������ �����.
	void readKey(string pathToKeyFile); //���������� �����.
	void readText(string pathToTextFile); //���������� ������.

	void extensionKey(); //���������� �����.
	void encryptBlock(const BYTE* pIn, BYTE* pOut); //���������� ������ ������.
	void encrypt(string pathToEncodeFile); //���������� ������.

public:
	CRC6Encoder(string pathToKeyFile, string pathToTextFile, string pathToEncodeFile);
	CRC6Encoder();
	~CRC6Encoder();
};
#include <fstream>
#include "CRC6Decoder.h"

using namespace std;

CRC6Decoder::CRC6Decoder(string pathToKeyFile, string pathToTextFile, string pathToDecodeFile)
{
	readKey(pathToKeyFile);
	extensionKey();
	readText(pathToTextFile);
	decrypt(pathToDecodeFile);
}

CRC6Decoder::CRC6Decoder(){}

CRC6Decoder::~CRC6Decoder(){}

//считывание ключа.
void CRC6Decoder::readKey(string pathToKeyFile)
{
	m_sizeKey=0; //размер ключа в байтах.
	m_keyOfByte=readFile(pathToKeyFile, m_sizeKey);
}

//считывание текста.
void CRC6Decoder::readText(string pathToTextFile)
{
	m_sizeText=0; //размер текста в байтах.
	m_textOfByte=readFile(pathToTextFile, m_sizeText);
}

//считывание файла.
BYTE* CRC6Decoder::readFile(string pathToFile, int& size)
{
	ifstream file(pathToFile, ios::binary|ios::ate);
	ifstream::pos_type length=file.tellg();
	
	BYTE* pData=new BYTE[length];
	file.seekg(0, ios::beg);
	file.read((char*) pData, length);
	pData[length]=0;

	file.close();

	size=length;
	return (pData);
}

//расширение ключа.
void CRC6Decoder::extensionKey()
{
	m_S[0]=m_Pw;
	for (int i=1; i<(2*m_round+4); i++)
		m_S[i]=m_S[i-1]+m_Qw;
	

	memset(m_L, 0, 64); //обнуление массива L.
	memmove(m_L, m_keyOfByte, m_sizeKey); //размещение ключа в массиве L.

	int numWordOfL=m_sizeKey/4; //количество слов(4*8-бит=32-бита) из которых состоит ключ.
	int i=0, j=0;
	DWORD A=0, B=0;

	int v=3*(2*m_round+4);

	for (int t=1; t<v; t++)
	{
		A=leftRotate(m_S[i]+A+B, offset(3));
		m_S[i]=A;

		B=leftRotate(m_L[j]+A+B, offset(A+B));
		m_L[j]=B;

		i=(i+1) % (2*m_round+4);
		j=(j+1) % numWordOfL;
	}

}

//смещение.
DWORD CRC6Decoder::offset(DWORD ofs)
{
	int lgOfs=log((double) m_w)/log(2.0);
	ofs=ofs<<(m_w-lgOfs);
	ofs=ofs>>(m_w-lgOfs);

	return (ofs);
}

//вращение вправо.
DWORD CRC6Decoder::leftRotate(DWORD var, DWORD ofs)
{
	DWORD t1, t2;
	
	t1=var>>(m_w-ofs);
	t2=var<<ofs;
	t2=t2|t1;

	return (t2);
}

//вращение влево.
DWORD CRC6Decoder::rightRotate(DWORD var, DWORD ofs)
{
	DWORD t1, t2;
	
	t1=var<<(m_w-ofs);
	t2=var>>ofs;
	t2=t2|t1;

	return (t2);
}

//дешифрование блока.
void CRC6Decoder::decryptBlock(const BYTE* pIn, BYTE* pOut)
{
	DWORD M[4];

	memmove(M, pIn, sizeof(M));

	M[2]=M[2]-m_S[2*m_round+3];
	M[0]=M[0]-m_S[2*m_round+2];

	for (int i=m_round-1; i>=0; i--)
	{
		DWORD temp=M[0];
		M[0]=M[3];
		M[3]=M[2];
		M[2]=M[1];
		M[1]=temp;

		DWORD u=leftRotate(M[3]*(2*M[3]+1), offset((DWORD) log((double) m_w)/log(2.0)));
		DWORD t=leftRotate(M[1]*(2*M[1]+1), offset((DWORD) log((double) m_w)/log(2.0)));

		M[2]=rightRotate(M[2] - m_S[2 * i + 1], offset(t))^u;
		M[0]=rightRotate(M[0] - m_S[2 * i], offset(u))^t;
	}

	M[3]=M[3]-m_S[1];
	M[1]=M[1]-m_S[0];

	memmove(pOut, M, sizeof(M));
}

//дешифрование.
void CRC6Decoder::decrypt(string pathToDecodeFile)
{
	BYTE* blockIn;
	BYTE* blockOut;

	ofstream file(pathToDecodeFile, ios::binary|ios::ate);
	for (int i=0; i<m_sizeText; i+=16)
	{
		blockOut=new BYTE[16];
		blockIn=&m_textOfByte[i];
		decryptBlock(blockIn, blockOut);
		file.write((char*) blockOut, 16);
	}

	file.close();
}

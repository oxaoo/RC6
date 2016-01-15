#include "CRC6Decoder.h"

int main(int argc, char* argv[])
{
	if (argc>=2)
	{
		cout<<argv[1]<<" "<<argv[2]<<" "<<argv[3]<<endl;
		CRC6Decoder rc6e(argv[1], argv[2], argv[3]);
	}
	else
	{
		string pathToKeyFile="E:\\key.txt";
		string pathToTextFile="E:\\encode.txt";
		string pathToDecodeFile="E:\\decode.txt";

		CRC6Decoder rc6e(pathToKeyFile, pathToTextFile, pathToDecodeFile);
		//cout<<"Error input argumets."<<endl;
	}
	system("pause");
	return 0;
}
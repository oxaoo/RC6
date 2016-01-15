#include "CRC6Encoder.h"

int main(int argc, char* argv[])
{
	if (argc>=4)
	{
		cout<<argv[1]<<" "<<argv[2]<<" "<<argv[3]<<endl;
		CRC6Encoder rc6e(argv[1], argv[2], argv[3]);
	}
	else
	{
		string pathToKeyFile="E:\\key.txt";
		string pathToTextFile="E:\\text.txt";
		string pathToEncodeFile="E:\\encode.txt";

		CRC6Encoder rc6e(pathToKeyFile, pathToTextFile, pathToEncodeFile);
		//cout<<"Error input argumets."<<endl;
	}
	system("pause");
	return 0;
}
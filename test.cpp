#include <iostream>
#include "Array.h"

int main()
{
	/*std::cout << "<";
	char* a=new char[10];
	std::cin.getline(a,10);
	std::cout << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		std::cout << a[i] << "---" << (int)a[i] << std::endl;;
	}
	std::cout << std::endl;
	delete[]a;*/

	//Arry x;
	//Arry y(2);
	//y.setElement(0, 0);
	//y.setElement(1, 1);
	//std::cout << "y[0] = " << (int)y.getElement(0) << " y[1] = " << (int)y.getElement(1) << std::endl;;
	//y.addElement(2);
	//std::cout << "new y[2] = " << (int)y.getElement(2) << std::endl;

	std::cout << "> ";
	unsigned char* str = new unsigned char[1000];
	std::cin.getline((char*)(str), 1000);
	Arry command;
	for (int i = 0; i < 1000; ++i)
	{
		if (str[i] != ' ')
		{
			command.addElement(str[i]);
		}
		else
		{
			break;
		}
	}
	command.addElement('\0');

	std::cout << command.getSize() << std::endl;

	if ((const char*)(command.m_bytes) == "load")
	{
		std::cout << "hi"<<std::endl;
		//todo:
	}
	delete[] str;

	std::system("pause");
	return 0;
}
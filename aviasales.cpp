#include <iostream>
#include <fstream>
#include "Array.h"

int main()
{
	do//todo: добавить остановку
	{
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

		if (command.m_bytes[0] == 'l' and command.m_bytes[1] == 'o' and command.m_bytes[2] == 'a' and command.m_bytes[3] == 'd')
		{
			//todo:
		}
		delete[] str;
	} while (true);
}
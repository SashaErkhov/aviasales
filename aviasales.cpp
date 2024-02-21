#include <iostream>
#include <fstream>
#include "Array.h"

int main()
{
	do//todo: добавить остановку
	{
		std::cout << "> ";
		unsigned char str = new unsigned char[1000];
		std::cin.getline(str, 1000);
		Arry command;
		for (int i = 0; i < 1000; ++i)
		{
			if (str[i] != ' ')
			{
				command.addElement(' ');
			}
			else
			{
				break;
			}
		}
		command.addElement('\0');
		if (command.m_bytes == "load")
		{
			//todo:
		}
		delete[] str;
	} while (true);
}
#include <iostream>
#include <fstream>
#include "Array.h"
#include "DataTime.h"
#include "AviaTickets.h"

int main()
{
	const unsigned int strSize = 1000;
	unsigned char* str = new unsigned char[strSize];
	DataBase DB;
	unsigned int IDnow = 0;
	do
	{
		std::cout << "> ";
		std::cin.getline((char*)(str), strSize);
		Arry command;
		for (int i = 0; i < strSize; ++i)
		{
			if (!(str[i] == ' ' or str[i] == 0))//отрабатывает случай если мы написали команду без аргументов
			{
				command.addElement(str[i]);
			}
			else
			{
				break;
			}
		}
		if (command.m_bytes[0] == 'q' and command.m_bytes[1] == 'u' and
			command.m_bytes[2] == 'i' and command.m_bytes[3] == 't' and command.size == 4)
		{
			break;
		}
		else if (command.m_bytes[0] == 'l' and command.m_bytes[1] == 'o' and 
			command.m_bytes[2] == 'a' and command.m_bytes[3] == 'd' and command.size==4)
		{
			try
			{
				IDnow = DB.load(str, strSize);
			}
			catch (const char* error)
			{
				std::cout << error;
			}
		}
		else if (command.m_bytes[0] == 's' and command.m_bytes[1] == 'a' and
			command.m_bytes[2] == 'v' and command.m_bytes[3] == 'e' and command.size == 4)
		{
			try
			{
				DB.save(str, strSize);
			}
			catch (const char* error)
			{
				std::cout << error;
			}
		}
		else if (command.m_bytes[0] == 'a' and command.m_bytes[1] == 'd' and
			command.m_bytes[2] == 'd' and command.size == 3)
		{
			try 
			{
				DB.addElement(AviaTickets(str, strSize, ++IDnow));
			}
			catch (const char* error)
			{
				std::cout << error << std::endl;
			}
			catch (unsigned char day)
			{
				std::cout << "Day value is invalid: " << (int)day << std::endl;
			}
		}
		else if (command.m_bytes[0] == 'd' and command.m_bytes[1] == 'e' and
			command.m_bytes[2] == 'l' and command.m_bytes[3] == 'e' and 
			command.m_bytes[4] == 't' and command.m_bytes[5] == 'e' and command.size == 6)
		{
			Arry id;
			for (int i = 7; i < strSize; ++i)
			{
				if (str[i] != 0)
				{
					id.addElement(str[i]);
				}
			}
			if (id.size == 0)
			{
				std::cout << "Unknown command" << std::endl;
				continue;
			}
			DB.deleteDB((unsigned int)std::atoi((char*)id.m_bytes));
		}
		else if (command.m_bytes[0] == 'c' and command.m_bytes[1] == 'l' and
			command.m_bytes[2] == 'e' and command.m_bytes[3] == 'a' and
			command.m_bytes[4] == 'r' and command.size == 5)
		{
			DB.clearDB();
		}
		else if (command.m_bytes[0] == 'p' and command.m_bytes[1] == 'r' and
			command.m_bytes[2] == 'i' and command.m_bytes[3] == 'n' and
			command.m_bytes[4] == 't' and command.size == 5)
		{
			DB.print();
		}
		else if (command.m_bytes[0] == 's' and command.m_bytes[1] == 'c' and
			command.m_bytes[2] == 'h' and command.m_bytes[3] == 'e' and
			command.m_bytes[4] == 'd' and command.m_bytes[5] == 'u' and
			command.m_bytes[6] == 'l' and command.m_bytes[7] == 'e' and command.size == 8)
		{
			DB.schedule(str, strSize);
		}
		else if (command.m_bytes[0] == 'f' and command.m_bytes[1] == 'r' and
			command.m_bytes[2] == 'o' and command.m_bytes[3] == 'm' and command.size == 4)
		{
			DB.fromTo(str, strSize);
		}
		else if (command.m_bytes[0] == 'f' and command.m_bytes[1] == 'i' and
			command.m_bytes[2] == 'n' and command.m_bytes[3] == 'd' and command.size == 4)
		{
			DB.find(str, strSize);
		}
		else if (command.m_bytes[0] == 'b' and command.m_bytes[1] == 'u' and
			command.m_bytes[2] == 'y' and command.size == 3)
		{
			DB.buy(str, strSize);
		}
		else if (command.m_bytes[0] == 'e' and command.m_bytes[1] == 'x' and
			command.m_bytes[2] == 'p' and command.m_bytes[3] == 'o' and
			command.m_bytes[4] == 'r' and command.m_bytes[5] == 't' and command.size == 6)
		{
			try
			{
				DB.exportDB(str, strSize);
			}
			catch (const char* error)
			{
				std::cout << error;
			}
		}
		else if(command.size!=0)
		{
			std::cout << "Unknown command: ";
			for (int i = 0; i < command.size; ++i)
			{
				std::cout << command.m_bytes[i];
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Unknown command" << std::endl;
		}
	} while (true);
	delete[] str;
	return 0;
}
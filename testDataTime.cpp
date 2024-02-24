#include <iostream>
#include "DataTime.h"

int main()
{
	std::cout << "I'm working!" << std::endl;
	/*try
	{
		DataTime x("20.11.2233 12:20",16);
		std::cout << "test = 20.11.2233 12:20" << std::endl;
		std::cout <<"real = " << x << std::endl;
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}
	try
	{
		DataTime x("01.01.01 00:01", 14);
		std::cout << "test = 01.01.01 00:01" << std::endl;
		std::cout << "real = " << x << std::endl;
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}*/
	/*try
	{
		DataTime x("1.1.1 0:12", 10);
		std::cout << "test = 1.1.1 0:12" << std::endl;
		std::cout << "real = " << x << std::endl;
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}*/
	/*try
	{
		DataTime x("12.01.2034 12:01", 16);
		std::cout << "test = 12.01.2034 12:01" << std::endl;
		std::cout << "real = " << x << std::endl;
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}*/
	std::cout << "test = 44.01.2034 12:01" << std::endl;
	try
	{
		DataTime x("44.01.2034 12:01", 16);
		std::cout << "real = " << x << std::endl;
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}
	catch (unsigned char* error)
	{
		for (int i = 0; i < 100; ++i)
		{
			if (error[i] != '\0')
			{
				std::cout << error[i];
			}
			else
			{
				break;
			}
		}
	}
	/*std::cout << "test = 01.13.2034 12:01" << std::endl;
	try
	{
		DataTime x("01.13.2034 12:01", 16);
		std::cout << "real = " << x << std::endl;
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}
	std::cout << "test = 29.02.2023 12:01" << std::endl;
	try
	{
		DataTime x("29.02.2023 12:01", 16);
		std::cout << "real = " << x << std::endl;
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}*/

	std::system("pause");
	return 0;
}
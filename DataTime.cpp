#include "DataTime.h"
#include "Array.h"
#include <iostream>

const char* fooError(const char* phraze,unsigned short size, const Arry& data)
{
	Arry error;
	error.addPhraze(phraze, size);
	for (int i = 0; i < data.size; ++i)
	{
		error.addElement(data.m_bytes[i]);
	}
	error.addElement('\0');
	return (const char*)error.m_bytes;
}

DataTime::DataTime(const char* input,unsigned int size)//может бросать исключения
{
	Arry data;
	bool ok=false;
	for (int i = 0; i < size; ++i)
	{
		if (input[i] != ' ')
		{
			data.addElement((unsigned char)input[i]);
		}
		else
		{
			ok = true;
			break;
		}
	}
	if (!ok)
	{
		throw "Unknown command";
	}
	Arry time;
	for (int i = (data.size+1); i < size; ++i)
	{
		time.addElement((unsigned char)input[i]);
	}
	short cnt = 0;
	for (int i = 0; i < data.size; ++i)
	{
		if (!('0' <= data.m_bytes[i] <= '9') and !(data.m_bytes[i] == '.'))
		{
			throw fooError("Wrong date format: ",19, data);
		}
		else if (data.m_bytes[i] == '.')
		{
			++cnt;
		}
	}
	if (cnt != 2)
	{
		throw fooError("Wrong date format: ",19, data);
	}
	Arry dayStr;
	for (int i = 0; i < data.size; ++i)
	{
		if (data.m_bytes[i] != '.')
		{
			dayStr.addElement(data.m_bytes[i]);
		}
		else
		{
			break;
		}
	}
	day = std::atoi((const char*)dayStr.m_bytes);
	if ((day < 1) or (day > 31))
	{
		throw fooError("Day value is invalid: ",22, dayStr);
	}
	Arry monthStr;
	for (int i = (dayStr.size + 1); i < data.size; ++i)
	{
		if (data.m_bytes[i] != '.')
		{
			monthStr.addElement(data.m_bytes[i]);
		}
		else
		{
			break;
		}
	}
	month = std::atoi((const char*)monthStr.m_bytes);
	if ((month < 1) or (month > 12))
	{
		throw fooError("Month value is invalid: ",24, monthStr);
	}
	Arry yearStr;
	for (int i = (dayStr.size+monthStr.size + 2); i < data.size; ++i)
	{
		yearStr.addElement(data.m_bytes[i]);
	}
	year = std::atoi((const char*)yearStr.m_bytes);
	if (month == 2 and day == 29)
	{
		if (year % 100 == 0)
		{
			if (year % 400 != 0)
			{
				throw fooError("Wrong date format: ",19, data);
			}
		}
		else
		{
			if (year % 4 != 0)
			{
				throw fooError("Wrong date format: ",19, data);
			}
		}
	}
	else if (month == 2 and day > 29)
	{
		throw fooError("Wrong date format: ",19, data);
	}
	cnt = 0;
	for (int i = 0; i < time.size; ++i)
	{
		if (!('0' <= time.m_bytes[i] <= '9') and !(time.m_bytes[i] == ':'))
		{
			throw fooError("Wrong time format: ",19, time);
		}
		else if (time.m_bytes[i] == ':')
		{
			++cnt;
		}
	}
	if (cnt != 1)
	{
		throw fooError("Wrong time format: ",19, time);
	}
	Arry hoursStr;
	for (int i = 0; i < time.size; ++i)
	{
		if (time.m_bytes[i] != ':')
		{
			hoursStr.addElement(time.m_bytes[i]);
		}
		else
		{
			break;
		}
	}
	Arry minutesStr;
	for (int i = (hoursStr.size + 1); i < time.size; ++i)
	{
		minutesStr.addElement(time.m_bytes[i]);
	}
	hours = std::atoi((const char*)hoursStr.m_bytes);
	minutes = std::atoi((const char*)minutesStr.m_bytes);
	if (hours < 0 or hours>24 or minutes < 0 or minutes>60)
	{
		throw fooError("Time value is invalid: ",23, time);
	}
}

DataTime::DataTime()
{
	day = 1;
	month = 1;
	year = 0;
	hours = 0;
	minutes = 0;
}

std::ostream& operator<<(std::ostream& out, const DataTime& x)
{
	if (x.getDay() < 10)
	{
		out << '0' << x.getDay();
	}
	else
	{
		out << x.getDay();;
	}
	out << '.';
	if (x.getMonth() < 10)
	{
		out << '0' << x.getMonth();
	}
	else
	{
		out << x.getMonth();
	}
	out << '.';
	if (x.getYear() < 10)
	{
		out << "000" << x.getYear();
	}
	else if (x.getYear() < 100)
	{
		out << "00" << x.getYear();
	}
	else if (x.getYear() < 1000)
	{
		out << "0" << x.getYear();
	}
	else
	{
		out << x.getYear();
	}
	out << ' ';
	if (x.getHours() < 10)
	{
		out<< '0' << x.getHours();
	}
	else
	{
		out << x.getHours();
	}
	out << ':';
	if (x.getMinutes() < 10)
	{
		out << '0' << x.getMinutes();
	}
	else
	{
		out << x.getMinutes();
	}
	return out;
}
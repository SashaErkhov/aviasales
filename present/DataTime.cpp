#include "DataTime.h"
#include "Array.h"
#include <iostream>

Arry fooError(const char* phraze,unsigned short size, const Arry& data)
{
	Arry error;
	error.addPhraze(phraze, size);
	for (int i = 0; i < data.size; ++i)
	{
		error.addElement(data.m_bytes[i]);
	}
	error.addElement('\0');
	return error;
}

DataTime::DataTime(const char* input,unsigned int size)//может бросать исключения
{
	Arry data;
	bool ok=false;
	for (int i = 0; i < size; ++i)
	{
		if (input[i] != ' ' and input[i]!=0)
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
	for (unsigned long long i = (data.size+1); i < size; ++i)
	{
		time.addElement((unsigned char)input[i]);
	}
	short cnt = 0;
	for (int i = 0; i < data.size; ++i)
	{
		if (!('0' <= data.m_bytes[i] and data.m_bytes[i] <= '9') and !(data.m_bytes[i] == '.') and
			!(data.m_bytes[i] == '\0'))
		{
			throw fooError("Wrong date format: ",19, data);
		}
		if (data.m_bytes[i] == '.')
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
	if (dayStr.size == 4)
	{
		throw fooError("Wrong date format: ", 19, data);
	}
	dayStr.addElement('\0');
	day = std::atoi((const char*)dayStr.m_bytes);
	if ((day < 1) or (day > 31))
	{
		//throw fooError("Day value is invalid: ",22, dayStr);
		throw day;
	}
	Arry monthStr;
	for (unsigned long long i = (dayStr.size); i < data.size; ++i)
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
	monthStr.addElement('\0');
	month = std::atoi((const char*)monthStr.m_bytes);
	if ((month < 1) or (month > 12))
	{
		throw fooError("Month value is invalid: ",24, monthStr);
	}
	Arry yearStr;
	for (unsigned long long i = (dayStr.size+monthStr.size); i < data.size; ++i)
	{
		yearStr.addElement(data.m_bytes[i]);
	}
	yearStr.addElement('\0');
	year = std::atoi((const char*)yearStr.m_bytes);
	if (month == 2 and day == 29)
	{
		if (year % 100 == 0)
		{
			if (year % 400 != 0)
			{
				//throw fooError("Wrong date format: ",19, data);
				throw day;
			}
		}
		else
		{
			if (year % 4 != 0)
			{
				throw day;
				//throw fooError("Wrong date format: ",19, data);
			}
		}
	}
	else if (month == 2 and day > 29)
	{
		throw day;
		//throw fooError("Wrong date format: ",19, data);
	}
	cnt = 0;
	if (time.size == 0)
	{
		hours = 0;
		minutes = 0;
		return;
	}
	if (time.m_bytes[0] == ' ') { time.m_bytes[0] = '0'; }
	for (int i = 0; i < time.size; ++i)
	{
		if (time.m_bytes[i] == '\0')
		{
			break;
		}
		if (!('0' <= time.m_bytes[i] and time.m_bytes[i] <= '9') and !(time.m_bytes[i] == ':'))
		{
			throw fooError("Wrong time format: ",19, time);
		}
		if (time.m_bytes[i] == ':')
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
	for (unsigned long long i = (hoursStr.size + 1); i < time.size; ++i)
	{
		minutesStr.addElement(time.m_bytes[i]);
	}
	hoursStr.addElement('\0');
	hours = std::atoi((const char*)hoursStr.m_bytes);
	minutesStr.addElement('\0');
	minutes = std::atoi((const char*)minutesStr.m_bytes);
	if (hours < 0 or hours>=24 or minutes < 0 or minutes>=60)
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
	if (x.getDay() < 10)
	{
		out << '0' << x.getDay();
	}
	else
	{
		out << x.getDay();;
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

bool DataTime::operator<(const DataTime& right) const
{
	if (this->year < right.year) { return true; }
	if (this->year > right.year) { return false; }
	if (this->month < right.month) { return true; }
	if (this->month > right.month) { return false; }
	if (this->day < right.day) { return true; }
	if (this->day > right.day) { return false; }
	if (this->hours < right.hours) { return true; }
	if (this->hours > right.hours) { return false; }
	if (this->minutes < right.minutes) { return true; }
	if (this->minutes > right.minutes) { return false; }
	return false;
}

DataTime::DataTime(short day, short month, short year, short hours, short minutes)
{
	this->day = day;
	this->month = month;
	this->year = year;
	this->hours = hours;
	this->minutes = minutes;
}

void DataTime::printTime()const
{
	if (this->getHours() < 10)
	{
		std::cout << '0' << this->getHours();
	}
	else
	{
		std::cout << this->getHours();
	}
	std::cout << ':';
	if (this->getMinutes() < 10)
	{
		std::cout << '0' << this->getMinutes();
	}
	else
	{
		std::cout << this->getMinutes();
	}
}
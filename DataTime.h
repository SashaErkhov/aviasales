#pragma once
#ifndef DATA_TIME_CLASS_PVM_2023
#define DATA_TIME_CLASS_PVM_2023

#include <iostream>

class DataTime;
std::ostream& operator<<(std::ostream& out, const DataTime& x);

class DataTime
{
private:
	unsigned char day;
	unsigned char month;
	unsigned short year;
	unsigned char hours;
	unsigned char minutes;
public:
	DataTime(const char* input, unsigned int size);
	DataTime();
	short getDay() const { return day; }
	short getMonth() const { return month; }
	short getYear() const { return year; }
	short getHours() const { return hours; }
	short getMinutes() const { return minutes; }
};

#endif // !DATA_TIME_CLASS_PVM_2023
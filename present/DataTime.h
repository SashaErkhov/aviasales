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
	DataTime(short day, short month, short year, short hours, short minutes);
	unsigned short getDay() const { return day; }
	unsigned short getMonth() const { return month; }
	unsigned short getYear() const { return year; }
	unsigned short getHours() const { return hours; }
	unsigned short getMinutes() const { return minutes; }
	bool operator<(const DataTime& right) const;
	void printTime()const;
};

#endif // !DATA_TIME_CLASS_PVM_2023

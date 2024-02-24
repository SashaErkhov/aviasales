#pragma once
#ifndef AVIASALES_CLASS_PVM_2023
#define AVIASALES_CLASS_PVM_2023

#include "DataTime.h"

class AviaTickets
{
private:
	char nomberOfFlight[7];
	char airportFrom[3];
	char airportTo[3];
	DataTime DTFrom;
	DataTime DTTo;
	unsigned long long int cntTickets;
	long double priceTickets;
	unsigned int ID;
public:
	AviaTickets(char* nomberOfFlight, char* airportFrom, char* airportTo,
		const DataTime& DTFrom,const DataTime& DTTo, unsigned long long int cntTickets,
		long double priceTickets,unsigned int ID);
	AviaTickets(const unsigned char* str, unsigned int strSize,unsigned int ID);
	AviaTickets();
	bool operator<(const AviaTickets& right)const;
	bool operator<=(const AviaTickets& right)const;
	unsigned int getID()const { return ID; }
	unsigned long long int getCntTickets()const { return cntTickets; }
};

class DataBase
{
private:
	AviaTickets* data;
	unsigned short size;
public:
	DataBase(unsigned long long int size=0);
	~DataBase();
	void addElement(const AviaTickets& input);
	AviaTickets getElement(unsigned long long int pos);
	void setElement(unsigned long long int pos, const AviaTickets& value);
	void deleteDB(unsigned int ID);
	void clearDB();
	void sortingData();
	void sortingPrice();
	void print();
};

#endif // !AVIASALES_CLASS_PVM_2023

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
public:
	AviaTickets(char* nomberOfFlight, char* airportFrom, char* airportTo,
		const DataTime& DTFrom,const DataTime& DTTo, unsigned long long int cntTickets,
		long double priceTickets);
};

class DataBase
{
private:
	AviaTickets* data;
	unsigned short size;
public:
	DataBase();
	~DataBase();
};

#endif // !AVIASALES_CLASS_PVM_2023

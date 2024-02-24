#include "AviaTickets.h"
#include "DataTime.h"

AviaTickets::AviaTickets(char* nomberOfFlight, char* airportFrom, char* airportTo,
	const DataTime& DTFrom, const DataTime& DTTo, unsigned long long int cntTickets,
	long double priceTickets)
{
	for (int i = 0; i < 7; ++i)
	{
		this->nomberOfFlight[i] = nomberOfFlight[i];
	}
	for (int i = 0; i < 3; ++i)
	{
		this->airportFrom[i] = airportFrom[i];
		this->airportTo[i] = airportTo[i];
	}
	this->DTFrom = DTFrom;
	this->DTTo = DTTo;
	this->cntTickets = cntTickets;
	this->priceTickets = priceTickets;
}

DataBase::DataBase()
{
	size = 0;
	data = new AviaTickets[0];
}

DataBase::~DataBase()
{
	delete[]data;
}
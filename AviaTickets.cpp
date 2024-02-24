#include "AviaTickets.h"
#include "DataTime.h"
#include "Array.h"

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

bool fooKons(Arry& x, const unsigned char* str, unsigned int startIndex,unsigned int strSize)
{
	for (int i = startIndex; i < strSize; ++i)
	{
		if (str[i] != ',' and str[i] != 0)
		{
			x.addElement(str[i]);
		}
		else if (str[i] == ',')
		{
			return true;
		}
	}
	return false;
}

AviaTickets::AviaTickets()
{
	for (int i = 0; i < 7; ++i)
	{
		nomberOfFlight[i] = 'A';
	}
	for (int i = 0; i < 3; ++i)
	{
		airportFrom[i] = 'A';
		airportTo[i] = 'A';
	}
	DTFrom = DataTime();
	DTTo= DataTime();
	cntTickets=0;
	priceTickets=0;
}

AviaTickets::AviaTickets(const unsigned char* str, unsigned int strSize)
{
	//add номер_рейса, аэропорт_вылета, аэропорт_прибытия, дата_и_время_вылета, дата_и_время_прилёта, количество_билетов, цена
	//add CA-909, PKX, SVO, 19.02.2024 8:40, 19.02.2024 17:00, 5, 80499
	if (strSize < 53)
	{
		throw "Unknown command";
	}
	Arry newNomFli;
	if ( (!fooKons(newNomFli,str,4,strSize)) or newNomFli.size>7)
	{
		throw "Unknown command";
	}
	for (int i = 0; i < newNomFli.size; ++i)
	{
		nomberOfFlight[i] = (char)newNomFli.m_bytes[i];
		if (nomberOfFlight[i] == ',' or nomberOfFlight[i] == ';' or nomberOfFlight[i] == '\"' or nomberOfFlight[i] == ' ')
		{
			throw "Unknown command";
		}
	}
	unsigned int index = 4 + newNomFli.size + 2;
	Arry airFrom;
	if ((!fooKons(airFrom, str, index, strSize)) or airFrom.size > 3)
	{
		throw "Unknown command";
	}
	for (int i = 0; i < airFrom.size; ++i)
	{
		airportFrom[i] = (char)airFrom.m_bytes[i];
		if (airportFrom[i] == ',' or airportFrom[i] == ';' or airportFrom[i] == '\"' or airportFrom[i] == ' ')
		{
			throw "Unknown command";
		}
	}
	index += airFrom.size + 2;
	Arry airTo;
	if ((!fooKons(airTo, str, index, strSize)) or airTo.size > 3)
	{
		throw "Unknown command";
	}
	for (int i = 0; i < airTo.size; ++i)
	{
		airportTo[i] = (char)airTo.m_bytes[i];
		if (airportTo[i] == ',' or airportTo[i] == ';' or airportTo[i] == '\"' or airportTo[i] == ' ')
		{
			throw "Unknown command";
		}
	}
	Arry dtFrom;
	index += airTo.size + 2;
	if (!fooKons(dtFrom, str, index, strSize))
	{
		throw "Unknown command";
	}
	Arry dtTo;
	index += dtFrom.size + 2;
	if (!fooKons(dtTo, str, index, strSize))
	{
		throw "Unknown command";
	}
	try
	{
		DataTime tmpFrom((char*)dtFrom.m_bytes, dtFrom.size);
		DataTime tmpTo((char*)dtTo.m_bytes, dtTo.size);
	}
	catch (const char* error)
	{
		throw error;
	}
	catch (unsigned char day)
	{
		throw day;
	}
	this->DTFrom = DataTime((char*)dtFrom.m_bytes,dtFrom.size);
	this->DTTo = DataTime((char*)dtTo.m_bytes, dtTo.size);
	index += dtTo.size + 2;
	Arry cnt;
	if (!fooKons(cnt, str, index, strSize))
	{
		throw "Unknown command";
	}
	this->cntTickets = std::atoi((char*)cnt.m_bytes);
	Arry price;
	index += cnt.size + 2;
	if (!fooKons(price, str, index, strSize))
	{
		throw "Unknown command";
	}
	this->priceTickets = std::atof((char*)price.m_bytes);
}

DataBase::DataBase(unsigned long long int size)
{
	this->size = size;
	data = new AviaTickets[size];
}

DataBase::~DataBase()
{
	delete[]data;
}

AviaTickets DataBase::getElement(unsigned long long int pos)
{
	return data[pos];
}

void DataBase::setElement(unsigned long long int pos, const AviaTickets& value)
{
	data[pos] = value;
}

void DataBase::addElement(const AviaTickets& input)
{
	DataBase tmp(size + 1);
	for (int i = 0; i < size; ++i)
	{
		tmp.setElement(i, (*this).getElement(i));
	}
	tmp.data[size] = input;
	std::swap(data, tmp.data);
	++size;
}
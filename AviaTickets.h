#pragma once
#ifndef AVIASALES_CLASS_PVM_2023
#define AVIASALES_CLASS_PVM_2023

#include "DataTime.h"

class AviaTickets;
std::ostream& operator<<(std::ostream& out, const AviaTickets& x);

class AviaTickets
{
private:
	char nomberOfFlight[8];
	char airportFrom[4];
	char airportTo[4];
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
	AviaTickets(const AviaTickets& X);
	bool operator<(const AviaTickets& right)const;
	bool operator<=(const AviaTickets& right)const;
	AviaTickets& operator=(const AviaTickets& X);
	unsigned int getID()const { return ID; }
	const char* getNomFli()const { return nomberOfFlight; }
	const char* getAirFrom()const { return airportFrom; }
	const char* getAirTo()const { return airportTo; }
	DataTime getDataFrom()const { return DTFrom; }
	DataTime getDataTo()const { return DTTo; }
	unsigned long long int getCntTickets()const { return cntTickets; }
	long double getPrice()const { return priceTickets; }
	void setCntTickets(unsigned long long int x) { cntTickets = x; }
};

class DataBase
{
private:
	AviaTickets* data;
	unsigned long long int size;
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
	void sortingNom();
	void print();
	void schedule(const unsigned char* str, unsigned int strSize);
	unsigned int load(unsigned char* str, unsigned int strSize);
	void save(unsigned char* str, unsigned int strSize) const;
	void fromTo(const unsigned char* str, unsigned int strSize);
	void find(const unsigned char* str, unsigned int strSize);
	void buy(const unsigned char* str, unsigned int strSize);
	void exportDB(const unsigned char* str, unsigned int strSize);
};

#endif // !AVIASALES_CLASS_PVM_2023

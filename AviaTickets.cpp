#include "AviaTickets.h"
#include "DataTime.h"
#include "Array.h"
#include <iostream>
#include <fstream>

AviaTickets::AviaTickets(char* nomberOfFlight, char* airportFrom, char* airportTo,
	const DataTime& DTFrom, const DataTime& DTTo, unsigned long long int cntTickets,
	long double priceTickets,unsigned int ID)
{
	for(int i=0;i<8;++i)
	{
		this->nomberOfFlight[i] = nomberOfFlight[i];
	}
	for (int i = 0; i < 4; ++i)
	{
		this->airportFrom[i] = airportFrom[i];
		this->airportTo[i] = airportTo[i];
	}
	this->DTFrom = DTFrom;
	this->DTTo = DTTo;
	this->cntTickets = cntTickets;
	this->priceTickets = priceTickets;
	this->ID = ID;
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
	nomberOfFlight[7] = '\0';
	for (int i = 0; i < 3; ++i)
	{
		airportFrom[i] = 'A';
		airportTo[i] = 'A';
	}
	airportFrom[3] = '\0';
	airportTo[3] = '\0';
	DTFrom = DataTime();
	DTTo= DataTime();
	cntTickets=0;
	priceTickets=0;
	ID = 0;
}

AviaTickets::AviaTickets(const unsigned char* str, unsigned int strSize,unsigned int ID)
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
	newNomFli.addElement('\0');
	for (int i = 0; i < newNomFli.size; ++i)
	{
		nomberOfFlight[i] = (char)newNomFli.m_bytes[i];
		if (nomberOfFlight[i] == ',' or nomberOfFlight[i] == ';' or nomberOfFlight[i] == '\"' or nomberOfFlight[i] == ' ')
		{
			throw "Unknown command";
		}
		if ('A' <= nomberOfFlight[i] <= 'Z')
		{
			nomberOfFlight[i] += 20;
		}
	}
	for (int i = newNomFli.size+1; i < 8; ++i)
	{
		nomberOfFlight[i] = '\0';
	}
	unsigned int index = 4 + newNomFli.size + 2;
	Arry airFrom;
	if ((!fooKons(airFrom, str, index, strSize)) or airFrom.size > 3)
	{
		throw "Unknown command";
	}
	airFrom.addElement('\0');
	for (int i = 0; i < airFrom.size; ++i)
	{
		airportFrom[i] = (char)airFrom.m_bytes[i];
		if (airportFrom[i] == ',' or airportFrom[i] == ';' or airportFrom[i] == '\"' or airportFrom[i] == ' ')
		{
			throw "Unknown command";
		}
		if ('A' <= airportFrom[i] <= 'Z')
		{
			airportFrom[i] += 20;
		}
	}
	for (int i = airFrom.size + 1; i < 4; ++i)
	{
		airportFrom[i] = '\0';
	}
	index += airFrom.size + 2;
	Arry airTo;
	if ((!fooKons(airTo, str, index, strSize)) or airTo.size > 3)
	{
		throw "Unknown command";
	}
	airTo.addElement('\0');
	for (int i = 0; i < airTo.size; ++i)
	{
		airportTo[i] = (char)airTo.m_bytes[i];
		if (airportTo[i] == ',' or airportTo[i] == ';' or airportTo[i] == '\"' or airportTo[i] == ' ')
		{
			throw "Unknown command";
		}
		if ('A' <= airportTo[i] <= 'Z')
		{
			airportTo[i] += 20;
		}
	}
	for (int i = airTo.size + 1; i < 4; ++i)
	{
		airportTo[i] = '\0';
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
		this->DTFrom = DataTime((char*)dtFrom.m_bytes, dtFrom.size);
		this->DTTo = DataTime((char*)dtTo.m_bytes, dtTo.size);
	}
	catch (const char* error)
	{
		throw error;
	}
	catch (unsigned char day)
	{
		throw day;
	}
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
	this->ID = ID;
	if (DTTo < DTFrom)
	{
		throw "Wrong arrival time";
	}
}

bool AviaTickets::operator<(const AviaTickets& right)const
{
	if (this->DTFrom.getYear() < right.DTFrom.getYear()) { return true; }
	if (this->DTFrom.getMonth() < right.DTFrom.getMonth()) { return true; }
	if (this->DTFrom.getDay() < right.DTFrom.getDay()) { return true; }
	if (this->DTFrom.getHours() < right.DTFrom.getHours()) { return true; }
	if (this->DTFrom.getMinutes() < right.DTFrom.getMinutes()) { return true; }
	return false;
}

bool AviaTickets::operator<=(const AviaTickets& right)const
{
	if (this->priceTickets < right.priceTickets)
	{
		return true;
	}
	else if (this->priceTickets == right.priceTickets)
	{
		return (*this) < right;
	}
	return false;
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

void DataBase::deleteDB(unsigned int ID)
{
	unsigned int index=-1;
	for (int i = 0; i < size; ++i)
	{
		if (this->data[i].getID() == ID)
		{
			index = i;
		}
	}
	if (index == -1) { return; }
	DataBase tmp(size - 1);
	for (int i = 0; i < index; ++i)
	{
		tmp.data[i] = this->data[i];
	}
	for (int i = index + 1; i < size; ++i)
	{
		tmp.data[i] = this->data[i];
	}
	std::swap(tmp.data, this->data);
	std::swap(tmp.size, this->size);
}

void DataBase::clearDB()
{
	for (int i = 0; i < size; ++i)
	{
		if (this->data[i].getCntTickets() == 0)
		{
			this->deleteDB(this->data[i].getID());
		}
	}
}

void DataBase::sortingData()
{
	// make heap
	for (int i = size / 2; i >= 0; --i) {
		// shift down each element
		int pos = i;
		int posMaxChild;
		while ((posMaxChild = 2 * pos + 1) < size) {
			if (posMaxChild + 1 < size) {
				if (data[posMaxChild] < data[posMaxChild + 1]) {
					++posMaxChild;
				}
			}
			if (data[pos] < data[posMaxChild]) {
				std::swap(data[pos], data[posMaxChild]);
				pos = posMaxChild;
			}
			else {
				break;
			}
		}
	}
	// shift down each element
	int heapSize = size;
	for (int step = 1; step < size; ++step) {
		if (data[heapSize - 1] < data[0]) {
			std::swap(data[heapSize - 1], data[0]);
		}
		--heapSize;
		int position = 0;
		int posMaxChild;
		while ((posMaxChild = 2 * position + 1) < heapSize) {// Пока есть левый потомок
			if (posMaxChild + 1 < heapSize) { // Есть ещё кто-то и справа
				if (data[posMaxChild] < data[posMaxChild + 1]) {
					++posMaxChild;
				}
			}
			if (data[position] < data[posMaxChild]) {
				std::swap(data[position], data[posMaxChild]);
				position = posMaxChild;
			}
			else {
				break;
			}
		}
	}
}

void DataBase::sortingPrice()
{
	// make heap
	for (int i = size / 2; i >= 0; --i) {
		// shift down each element
		int pos = i;
		int posMaxChild;
		while ((posMaxChild = 2 * pos + 1) < size) {
			if (posMaxChild + 1 < size) {
				if (data[posMaxChild] <= data[posMaxChild + 1]) {
					++posMaxChild;
				}
			}
			if (data[pos] <= data[posMaxChild]) {
				std::swap(data[pos], data[posMaxChild]);
				pos = posMaxChild;
			}
			else {
				break;
			}
		}
	}
	// shift down each element
	int heapSize = size;
	for (int step = 1; step < size; ++step) {
		if (data[heapSize - 1] <= data[0]) {
			std::swap(data[heapSize - 1], data[0]);
		}
		--heapSize;
		int position = 0;
		int posMaxChild;
		while ((posMaxChild = 2 * position + 1) < heapSize) {// Пока есть левый потомок
			if (posMaxChild + 1 < heapSize) { // Есть ещё кто-то и справа
				if (data[posMaxChild] <= data[posMaxChild + 1]) {
					++posMaxChild;
				}
			}
			if (data[position] <= data[posMaxChild]) {
				std::swap(data[position], data[posMaxChild]);
				position = posMaxChild;
			}
			else {
				break;
			}
		}
	}
}

void DataBase::print()
{
	this->sortingData();
	for (int i = 0; i < size; ++i)
	{
		std::cout << data[i].getID() << ", " << data[i].getNomFli() << ", " << data[i].getAirFrom();
		std::cout<< ", " << data[i].getAirTo() << ", " << data[i].getDataFrom()<<", "<<data[i].getDataTo();
		std::cout << ", " << data[i].getCntTickets() << ", " << data[i].getPrice() << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out, const AviaTickets& x)
{
	out << x.getID() << ", " << x.getNomFli() << ", " << x.getAirFrom();
	out << ", " << x.getAirTo() << ", " << x.getDataFrom() << ", " << x.getDataTo();
	out << ", " << x.getCntTickets() << ", " << x.getPrice();
	return out;
}

unsigned int DataBase::load(unsigned char* str, unsigned int strSize)
{
	Arry fileName;
	for (int i = 5; i < strSize; ++i)
	{
		if (str[i] != '\0')
		{
			fileName.addElement(str[i]);
		}
		else
		{
			fileName.addElement('\0');
			break;
		}
	}
	std::ifstream file;
	file.open((char*)fileName.m_bytes, std::ios_base::binary);
	if (!file.is_open())
	{
		throw "Can not open database";
	}
	unsigned long long int fileSize=0;
	file.read((char*)fileSize, 8);
	char fileNomFli[8];
	char fileAirFrom[4];
	char fileAirTo[4];

	short day = 0;
	short month = 0;
	short year = 0;
	short hours = 0;
	short minutes = 0;

	short day2 = 0;
	short month2 = 0;
	short year2 = 0;
	short hours2 = 0;
	short minutes2 = 0;

	unsigned long long int CntTickets=0;
	long double price=0;
	unsigned int newID=0;
	unsigned int maxID = 0;
	for (int i = 0; i < size; ++i)
	{
		file.read(fileNomFli, 8);
		file.read(fileAirFrom, 4);
		file.read(fileAirTo, 4);

		file.read((char*)day, 2);
		file.read((char*)month, 2);
		file.read((char*)year, 2);
		file.read((char*)hours, 2);
		file.read((char*)minutes, 2);

		file.read((char*)day2, 2);
		file.read((char*)month2, 2);
		file.read((char*)year2, 2);
		file.read((char*)hours2, 2);
		file.read((char*)minutes2, 2);

		file.read((char*)CntTickets, 8);
		file.read((char*)price, 16);
		file.read((char*)newID, 4);

		if (newID > maxID)
		{
			maxID = newID;
		}

		addElement(AviaTickets(fileNomFli, fileAirFrom, fileAirTo,
			DataTime(day, month, year, hours, minutes),
			DataTime(day2, month2, year2, hours2, minutes2), CntTickets, price, newID));
	}
	file.close();
	return maxID;
}

void DataBase::save(unsigned char* str, unsigned int strSize)const
{
	Arry fileName;
	for (int i = 5; i < strSize; ++i)
	{
		if (str[i] != '\0')
		{
			fileName.addElement(str[i]);
		}
		else
		{
			fileName.addElement('\0');
			break;
		}
	}
	std::ofstream file;
	file.open((char*)fileName.m_bytes, std::ios_base::binary);
	if (!file.is_open())
	{
		throw "Can not write to file";
	}
	file.write((char*)size, 8);
	for (int i = 0; i < size; ++i)
	{
		file.write(data[i].getNomFli(),8);
		file.write(data[i].getAirFrom(), 4);
		file.write(data[i].getAirTo(), 4);

		file.write((char*)data[i].getDataFrom().getDay(), 2);
		file.write((char*)data[i].getDataFrom().getMonth(), 2);
		file.write((char*)data[i].getDataFrom().getYear(), 2);
		file.write((char*)data[i].getDataFrom().getHours(), 2);
		file.write((char*)data[i].getDataFrom().getMinutes(), 2);

		file.write((char*)data[i].getDataTo().getDay(), 2);
		file.write((char*)data[i].getDataTo().getMonth(), 2);
		file.write((char*)data[i].getDataTo().getYear(), 2);
		file.write((char*)data[i].getDataTo().getHours(), 2);
		file.write((char*)data[i].getDataTo().getMinutes(), 2);

		file.write((char*)data[i].getCntTickets(), 8);
		file.write((char*)(data[i].getPrice()), 16);
		file.write((char*)data[i].getID(), 4);
	}
	file.close();
}
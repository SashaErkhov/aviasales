#include "AviaTickets.h"
#include "DataTime.h"
#include "Array.h"
#include <iostream>
#include <iomanip>
#include <fstream>

AviaTickets::AviaTickets(char* nomberOfFlight, char* airportFrom, char* airportTo,
	const DataTime& DTFrom, const DataTime& DTTo, unsigned long long int cntTickets,
	long double priceTickets, unsigned int ID)
{
	for (int i = 0; i < 8; ++i)
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

bool fooKons(Arry& x, const unsigned char* str, unsigned int startIndex, unsigned int strSize)
{
	for (int i = startIndex; i < strSize; ++i)
	{
		if (str[i] != ',' and str[i] != 0)
		{
			x.addElement(str[i]);
		}
		else if ((str[i] == ',')or(str[i]==0))
		{
			return true;
		}
		else
		{
			return false;
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
	DTTo = DataTime();
	cntTickets = 0;
	priceTickets = 0;
	ID = 0;
}

AviaTickets::AviaTickets(const unsigned char* str, unsigned int strSize, unsigned int ID)
{
	//add номер_рейса, аэропорт_вылета, аэропорт_прибытия, дата_и_время_вылета, дата_и_время_прилёта, количество_билетов, цена
	//add CA-909, PKX, SVO, 19.02.2024 8:40, 19.02.2024 17:00, 5, 80499
	Arry newNomFli;
	if ((!fooKons(newNomFli, str, 4, strSize)) or newNomFli.size > 7)
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
		if ('a' <= nomberOfFlight[i] and nomberOfFlight[i] <= 'z')
		{
			nomberOfFlight[i] += 'A' - 'a';
		}
	}
	for (int i = newNomFli.size + 1; i < 8; ++i)
	{
		nomberOfFlight[i] = '\0';
	}
	unsigned int index = 4 + newNomFli.size + 1;
	if (str[index] == ' ') { ++index; }
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
		if ('a' <= airportFrom[i] and airportFrom[i] <= 'z')
		{
			airportFrom[i] += 'A' - 'a';
		}
	}
	for (int i = airFrom.size + 1; i < 4; ++i)
	{
		airportFrom[i] = '\0';
	}
	index += airFrom.size + 1;
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
		if ('a' <= airportTo[i] and airportTo[i] <= 'z')
		{
			airportTo[i] += 'A' - 'a';
		}
	}
	for (int i = airTo.size + 1; i < 4; ++i)
	{
		airportTo[i] = '\0';
	}
	Arry dtFrom;
	index += airTo.size + 1;
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

	/*for (int i = index; i < strSize; ++i)
	{
		if (str[i] != ',' and str[i] != 0)
		{
			dtTo.addElement(str[i]);
		}
		else if ((str[i] == ',') or (str[i] == 0))
		{
			return true;
		}
	}*/

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
	index += dtTo.size + 1;
	if (str[index] == ' ') { ++index; }
	Arry cnt;
	if (!fooKons(cnt, str, index, strSize))
	{
		throw "Unknown command";
	}
	this->cntTickets = std::atoi((char*)cnt.m_bytes);
	Arry price;
	index += cnt.size + 1;
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

AviaTickets::AviaTickets(const AviaTickets& X)
{
	for (int i = 0; i < 8; ++i)
	{
		this->nomberOfFlight[i] = X.nomberOfFlight[i];
	}
	for (int i = 0; i < 4; ++i)
	{
		this->airportFrom[i] = X.airportFrom[i];
		this->airportTo[i] = X.airportTo[i];
	}
	DTFrom = X.DTFrom;
	DTTo = X.DTTo;
	cntTickets = X.cntTickets;
	priceTickets = X.priceTickets;
	ID = X.ID;
}

AviaTickets& AviaTickets::operator=(const AviaTickets& X)
{
	for (int i = 0; i < 8; ++i)
	{
		this->nomberOfFlight[i] = X.nomberOfFlight[i];
	}
	for (int i = 0; i < 4; ++i)
	{
		this->airportFrom[i] = X.airportFrom[i];
		this->airportTo[i] = X.airportTo[i];
	}
	DTFrom = X.DTFrom;
	DTTo = X.DTTo;
	cntTickets = X.cntTickets;
	priceTickets = X.priceTickets;
	ID = X.ID;
	return *this;
}

bool AviaTickets::operator<(const AviaTickets& right)const
{
	if (this->getDataFrom().getYear()< right.getDataFrom().getYear()) { return true; }
	else if (this->getDataFrom().getYear() > right.getDataFrom().getYear()) { return false; }
	if (this->getDataFrom().getMonth() < right.getDataFrom().getMonth()) { return true; }
	else if (this->getDataFrom().getMonth() > right.getDataFrom().getMonth()) { return false; }
	if (this->getDataFrom().getDay() < right.getDataFrom().getDay()) { return true; }
	else if (this->getDataFrom().getDay() > right.getDataFrom().getDay()) { return false; }
	if (this->getDataFrom().getHours() < right.getDataFrom().getHours()) { return true; }
	else if (this->getDataFrom().getHours() > right.getDataFrom().getHours()) { return false; }
	if (this->getDataFrom().getMinutes() < right.getDataFrom().getMinutes()) { return true; }
	else if (this->getDataFrom().getMinutes() > right.getDataFrom().getMinutes()) { return false; }
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

bool AviaTickets::operator==(const AviaTickets& right)const
{
	if (this->getDataFrom().getYear() < right.getDataFrom().getYear()) { return true; }
	else if (this->getDataFrom().getYear() > right.getDataFrom().getYear()) { return false; }
	if (this->getDataFrom().getMonth() < right.getDataFrom().getMonth()) { return true; }
	else if (this->getDataFrom().getMonth() > right.getDataFrom().getMonth()) { return false; }
	if (this->getDataFrom().getDay() < right.getDataFrom().getDay()) { return true; }
	else if (this->getDataFrom().getDay() > right.getDataFrom().getDay()) { return false; }
	if (this->getDataFrom().getHours() < right.getDataFrom().getHours()) { return true; }
	else if (this->getDataFrom().getHours() > right.getDataFrom().getHours()) { return false; }
	if (this->getDataFrom().getMinutes() < right.getDataFrom().getMinutes()) { return true; }
	else if (this->getDataFrom().getMinutes() > right.getDataFrom().getMinutes()) { return false; }
	for (int i = 0; i < 8; ++i)
	{
		if (this->nomberOfFlight[i] < right.nomberOfFlight[i]) { return true; }
		else if (this->nomberOfFlight[i] > right.nomberOfFlight[i]) { return false; }
	}
	if (this->priceTickets < right.priceTickets) { return true; }
	return false;
}

std::ostream& operator<<(std::ostream& out, const AviaTickets& x)
{
	out << x.getID() << ", " << x.getNomFli() << ", " << x.getAirFrom();
	out << ", " << x.getAirTo() << ", " << x.getDataFrom() << ", " << x.getDataTo();
	out << ", " << x.getCntTickets() << ", " << x.getPrice();
	return out;
}

DataBase::DataBase(unsigned long long int size)
{
	this->size = size;
	data = new AviaTickets[size];
}

DataBase::DataBase(const DataBase& X)
{
	size = X.size;
	data = new AviaTickets[size];
	for (int i = 0; i < size; ++i)
	{
		data[i] = X.data[i];
	}
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
	unsigned int index = -1;
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
		tmp.data[i-1] = this->data[i];
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

void DataBase::sortingDNP()
{
	// make heap
	for (int i = size / 2; i >= 0; --i) {
		// shift down each element
		int pos = i;
		int posMaxChild;
		while ((posMaxChild = 2 * pos + 1) < size) {
			if (posMaxChild + 1 < size) {
				if (data[posMaxChild] == data[posMaxChild + 1]) {
					++posMaxChild;
				}
			}
			if (data[pos] == data[posMaxChild]) {
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
		if (data[heapSize - 1] == data[0]) {
			std::swap(data[heapSize - 1], data[0]);
		}
		--heapSize;
		int position = 0;
		int posMaxChild;
		while ((posMaxChild = 2 * position + 1) < heapSize) {// Пока есть левый потомок
			if (posMaxChild + 1 < heapSize) { // Есть ещё кто-то и справа
				if (data[posMaxChild] == data[posMaxChild + 1]) {
					++posMaxChild;
				}
			}
			if (data[position] == data[posMaxChild]) {
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

void DataBase::sortingNom()
{
	// make heap
	for (int i = 8 / 2; i >= 0; --i) {
		// shift down each element
		int pos = i;
		int posMaxChild;
		while ((posMaxChild = 2 * pos + 1) < 8) {
			if (posMaxChild + 1 < 8) {
				if (data->getNomFli()[posMaxChild] < data->getNomFli()[posMaxChild + 1]) {
					++posMaxChild;
				}
			}
			if (data->getNomFli()[pos] < data->getNomFli()[posMaxChild]) {
				std::swap(data[pos], data[posMaxChild]);
				pos = posMaxChild;
			}
			else {
				break;
			}
		}
	}
	// shift down each element
	int heapSize = 8;
	for (int step = 1; step < 8; ++step) {
		if (data->getNomFli()[heapSize - 1] < data->getNomFli()[0]) {
			std::swap(data[heapSize - 1], data[0]);
		}
		--heapSize;
		int position = 0;
		int posMaxChild;
		while ((posMaxChild = 2 * position + 1) < heapSize) {// Пока есть левый потомок
			if (posMaxChild + 1 < heapSize) { // Есть ещё кто-то и справа
				if (data->getNomFli()[posMaxChild] < data->getNomFli()[posMaxChild + 1]) {
					++posMaxChild;
				}
			}
			if (data->getNomFli()[position] < data->getNomFli()[posMaxChild]) {
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
	DataBase tmp(*this);
	tmp.sortingDNP();
	for (int i = 0; i < size; ++i)
	{
		std::cout << tmp.data[i].getID() << ", " << tmp.data[i].getNomFli() << ", " << tmp.data[i].getAirFrom();
		std::cout << ", " << tmp.data[i].getAirTo() << ", " << tmp.data[i].getDataFrom() << ", " << tmp.data[i].getDataTo();
		std::cout << ", " << tmp.data[i].getCntTickets() << ", " << tmp.data[i].getPrice() << std::endl;
	}
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
	unsigned long long int fileSize = 0;
	file >> fileSize;
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

	unsigned long long int CntTickets = 0;
	long double price = 0;
	unsigned int newID = 0;
	unsigned int maxID = 0;
	for (int i = 0; i < fileSize; ++i)
	{
		for (int i = 0; i < 8; ++i)
		{
			fileNomFli[i] = '\0';
		}
		for (int i = 0; i < 4; ++i)
		{
			fileAirFrom[i] = '\0';
			fileAirTo[i] = '\0';
		}
		file >> fileNomFli;
		file >> fileAirFrom;
		file >> fileAirTo;

		/*file.read(fileNomFli, 8);
		file.read(fileAirFrom, 4);
		file.read(fileAirTo, 4);*/

		file >> day;
		file >> month;
		file >> year;
		file >> hours;
		file >> minutes;

		file >> day2;
		file >> month2;
		file >> year2;
		file >> hours2;
		file >> minutes2;

		file >> CntTickets;
		file >> price;
		file >> newID;

		if (newID > maxID)
		{
			maxID = newID;
		}

		try
		{
			addElement(AviaTickets(fileNomFli, fileAirFrom, fileAirTo,
				DataTime(day, month, year, hours, minutes),
				DataTime(day2, month2, year2, hours2, minutes2), CntTickets, price, newID));
		}
		catch (const char* error)
		{
			std::cout << error << std::endl;
			return maxID;
		}
		catch (unsigned char day)
		{
			std::cout << "Day value is invalid: " << (int)day << std::endl;
			return maxID;
		}
	}
	file.close();
	return maxID;
}

void DataBase::save(unsigned char* str, unsigned int strSize)
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
	file << size << ' ';
	for (int i = 0; i < size; ++i)
	{
		file << data[i].getNomFli() << ' ';
		file << data[i].getAirFrom() << ' ';
		file << data[i].getAirTo() << ' ';

		/*file.write(data[i].getNomFli(), 8);
		file.write(data[i].getAirFrom(), 4);
		file.write(data[i].getAirTo(), 4);*/

		file << data[i].getDataFrom().getDay() << ' ';
		file << data[i].getDataFrom().getMonth() << ' ';
		file << data[i].getDataFrom().getYear() << ' ';
		file << data[i].getDataFrom().getHours() << ' ';
		file << data[i].getDataFrom().getMinutes() << ' ';

		file << data[i].getDataTo().getDay() << ' ';
		file << data[i].getDataTo().getMonth() << ' ';
		file << data[i].getDataTo().getYear() << ' ';
		file << data[i].getDataTo().getHours() << ' ';
		file << data[i].getDataTo().getMinutes() << ' ';

		file << data[i].getCntTickets() << ' ';
		file << data[i].getPrice() << ' ';
		file << data[i].getID() << ' ';

	}
	file.close();
	delete[]data;
	data = new AviaTickets[0];
	size = 0;
}

void DataBase::schedule(const unsigned char* str, unsigned int strSize)
{
	Arry airFrom;
	for (int i = 9; i < strSize; ++i)
	{
		if (str[i] != ' ' and str[i] != 0)
		{
			airFrom.addElement(str[i]);
		}
		else
		{
			break;
		}
	}
	for (int i = airFrom.size; i < 4; ++i)
	{
		airFrom.addElement('\0');
	}
	Arry DTFrom;
	for (int i = 9 + airFrom.size; i < strSize; ++i)
	{
		if (str[i] != ' ' and str[i] != 0)
		{
			DTFrom.addElement(str[i]);
		}
		else
		{
			break;
		}
	}
	DTFrom.addElement('\0');
	DataTime tmp;
	try
	{
		tmp = DataTime((char*)DTFrom.m_bytes, DTFrom.size);
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
		return;
	}
	catch (unsigned char day)
	{
		std::cout << "Day value is invalid: " << (int)day << std::endl;
		return;
	}
	DataBase tmpDB;
	for (int i = 0; i < size; ++i)
	{
		if (this->data[i].getDataFrom().getYear() == tmp.getYear() and
			this->data[i].getDataFrom().getMonth() == tmp.getMonth() and
			this->data[i].getDataFrom().getDay() == tmp.getDay())
		{
			bool ok = true;
			for (int i = 0; i < 4; ++i)
			{
				if (this->data[i].getAirFrom()[i] != (char)airFrom.m_bytes[i])
				{
					ok = false;
				}
			}
			if (ok)
			{
				tmpDB.addElement(this->data[i]);
			}
		}
	}
	tmpDB.sortingData();
	for (int i = 0; i < tmpDB.size; ++i)
	{
		std::cout << tmpDB.data[i].getNomFli() << ", " << tmpDB.data[i].getAirTo() << ", "
			<< tmpDB.data[i].getDataFrom().getHours()<<':'<< tmpDB.data[i].getDataFrom().getMinutes() << std::endl;
	}
}

void DataBase::fromTo(const unsigned char* str, unsigned int strSize)
{
	Arry airFrom;
	unsigned int index = 5;
	for (int i = index; i < strSize; ++i)
	{
		if (str[i] != ',' and str[i] != 0)
		{
			airFrom.addElement(str[i]);
		}
		else
		{
			break;
		}
	}
	Arry airTo;
	index += airFrom.size + 4;
	for (int i = index; i < strSize; ++i)
	{
		if (str[i] != ',' and str[i] != 0)
		{
			airTo.addElement(str[i]);
		}
		else
		{
			break;
		}
	}
	Arry DTFrom;
	index += airTo.size + 4;
	for (int i = index; i < strSize; ++i)
	{
		if (str[i] != ',' and str[i] != 0)
		{
			DTFrom.addElement(str[i]);
		}
		else
		{
			break;
		}
	}
	DataTime tmp;
	try
	{
		tmp = DataTime((char*)DTFrom.m_bytes, DTFrom.size);
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
		return;
	}
	catch (unsigned char day)
	{
		std::cout << "Day value is invalid: " << (int)day << std::endl;
		return;
	}
	DataBase tmpDB;
	for (int i = 0; i < size; ++i)
	{
		if (this->data[i].getDataFrom().getYear() == tmp.getYear() and
			this->data[i].getDataFrom().getMonth() == tmp.getMonth() and
			this->data[i].getDataFrom().getDay() == tmp.getDay())
		{
			bool ok = true;
			for (int i = 0; i < 4; ++i)
			{
				if (this->data[i].getAirFrom()[i] != (char)airFrom.m_bytes[i])
				{
					ok = false;
				}
				if (this->data[i].getAirTo()[i] != (char)airTo.m_bytes[i])
				{
					ok = false;
				}
			}
			if (ok)
			{
				tmpDB.addElement(this->data[i]);
			}
		}
	}
	tmpDB.sortingPrice();
	tmpDB.clearDB();
	if (tmpDB.size == 0)
	{
		std::cout << "no tickets" << std::endl;
		return;
	}
	for (int i = 0; i < tmpDB.size; ++i)
	{
		std::cout << tmpDB.data[i].getNomFli() << ", " << tmpDB.data[i].getAirFrom() << ", " <<
			tmpDB.data[i].getAirTo() << ", " << tmpDB.data[i].getDataFrom() << ", " <<
			tmpDB.data[i].getDataTo() << ", " << tmpDB.data[i].getCntTickets() << ", " <<
			tmpDB.data[i].getPrice() << std::endl;
	}
}

void DataBase::find(const unsigned char* str, unsigned int strSize)
{
	Arry airFrom;
	for (int i = 5; i < strSize; ++i)
	{
		if (str[i] != ' ' and str[i] != 0)
		{
			airFrom.addElement(str[i]);
		}
		else
		{
			break;
		}
	}
	Arry airTo;
	for (int i = 5 + airFrom.size + 4; i < strSize; ++i)
	{
		if (str[i] != ' ' and str[i] != 0)
		{
			airTo.addElement(str[i]);
		}
		else
		{
			break;
		}
	}
	for (int i = airFrom.size; i < 4; ++i)
	{
		airFrom.addElement('\0');
	}
	for (int i = airTo.size; i < 4; ++i)
	{
		airTo.addElement('\0');
	}
	DataBase tmp;
	for (int i = 0; i < size; ++i)
	{
		if ((char)airFrom.m_bytes[0] == this->data[i].getAirFrom()[0] and
			(char)airFrom.m_bytes[1] == this->data[i].getAirFrom()[1] and
			(char)airFrom.m_bytes[2] == this->data[i].getAirFrom()[2] and
			(char)airFrom.m_bytes[3] == this->data[i].getAirFrom()[3] and
			(char)airTo.m_bytes[0] == this->data[i].getAirTo()[0] and
			(char)airTo.m_bytes[1] == this->data[i].getAirTo()[1] and
			(char)airTo.m_bytes[2] == this->data[i].getAirTo()[2] and
			(char)airTo.m_bytes[3] == this->data[i].getAirTo()[3] and
			this->data[i].getPrice() > 0)
		{
			tmp.addElement(this->data[i]);
		}
	}
	tmp.sortingPrice();
	this->sortingPrice();
	for (int i = 0; i < size; ++i)
	{
		if ((char)airFrom.m_bytes[0] == this->data[i].getAirFrom()[0] and
			(char)airFrom.m_bytes[1] == this->data[i].getAirFrom()[1] and
			(char)airFrom.m_bytes[2] == this->data[i].getAirFrom()[2] and
			(char)airFrom.m_bytes[3] == this->data[i].getAirFrom()[3] and
			this->data[i].getPrice() != 0)
		{
			for (int j = 0; j < size; ++j)
			{
				if ((char)airTo.m_bytes[0] == this->data[j].getAirTo()[0] and
					(char)airTo.m_bytes[1] == this->data[j].getAirTo()[1] and
					(char)airTo.m_bytes[2] == this->data[j].getAirTo()[2] and
					(char)airTo.m_bytes[3] == this->data[j].getAirTo()[3] and
					this->data[j].getPrice() != 0)
				{
					if (this->data[i].getAirTo()[0] == this->data[j].getAirFrom()[0] and
						this->data[i].getAirTo()[1] == this->data[j].getAirFrom()[1] and
						this->data[i].getAirTo()[2] == this->data[j].getAirFrom()[2] and
						this->data[i].getAirTo()[3] == this->data[j].getAirFrom()[3])
					{
						if (tmp.size != 0 and (tmp.data[0].getPrice() > (data[i].getPrice() + data[j].getPrice())))
						{
							std::cout << data[i].getNomFli() << ", " << data[i].getAirFrom() << ", " <<
								data[i].getAirTo() << ", " << data[i].getDataFrom() << ", " <<
								data[i].getDataTo() << ", " << data[i].getCntTickets() << ", " <<
								data[i].getPrice() << std::endl;
							std::cout << data[j].getNomFli() << ", " << data[j].getAirFrom() << ", " <<
								data[j].getAirTo() << ", " << data[j].getDataFrom() << ", " <<
								data[j].getDataTo() << ", " << data[j].getCntTickets() << ", " <<
								data[j].getPrice() << std::endl;
							return;
						}
						else if (tmp.size != 0)
						{
							std::cout << tmp.data[i].getNomFli() << ", " << tmp.data[i].getAirFrom() << ", " <<
								tmp.data[i].getAirTo() << ", " << tmp.data[i].getDataFrom() << ", " <<
								tmp.data[i].getDataTo() << ", " << tmp.data[i].getCntTickets() << ", " <<
								tmp.data[i].getPrice() << std::endl;
							return;
						}
					}
				}
			}
		}
	}
	std::cout << "no tickets" << std::endl;
}

void DataBase::buy(const unsigned char* str, unsigned int strSize)
{
	Arry NomFli;
	for (int i = 4; i < strSize; ++i)
	{
		if (str[i] != ' ' and str[i] != 0)
		{
			NomFli.addElement(str[i]);
		}
		else
		{
			break;
		}
	}
	for (int i = NomFli.size; i < 8; ++i)
	{
		NomFli.addElement('\0');
	}
	Arry DTFrom;
	int Index = 3 + NomFli.size;
	if (str[Index] == ' ')
	{
		++Index;
	}
	for (int i = Index; i < strSize; ++i)
	{
		if (str[i] != ' ' and str[i] != 0)
		{
			DTFrom.addElement(str[i]);
		}
		else
		{
			break;
		}
	}
	DTFrom.addElement('\0');
	DataTime tmp;
	try
	{
		tmp = DataTime((char*)DTFrom.m_bytes, DTFrom.size);
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
		return;
	}
	catch (unsigned char day)
	{
		std::cout << "Day value is invalid: " << (int)day << std::endl;
		return;
	}
	DataBase tmpDB = *this;
	tmpDB.sortingPrice();
	bool ok2 = false;
	for (int i = 0; i < size; ++i)
	{
		if (tmpDB.data[i].getDataFrom().getYear() == tmp.getYear() and
			tmpDB.data[i].getDataFrom().getMonth() == tmp.getMonth() and
			tmpDB.data[i].getDataFrom().getDay() == tmp.getDay())
		{
			/*if (tmpDB.data[i].getCntTickets() == 0)
			{
				std::cout << "no tickets" << std::endl;
				return;
			}*/
			bool ok = true;
			for (int j = 0; j < 8; ++j)
			{
				if (tmpDB.data[i].getNomFli()[j] != (char)NomFli.m_bytes[j])
				{
					ok = false;
					break;
				}
			}
			if (ok and tmpDB.data[i].getCntTickets() != 0)
			{
				this->data[getIndex(tmpDB.data[i].getID())].setCntTickets(tmpDB.data[i].getCntTickets() - 1);
				std::cout << tmpDB.data[i].getPrice() << std::endl;
				ok2 = true;
				break;
			}
		}
	}
	if (!ok2)
	{
		std::cout << "no tickets" << std::endl;
	}
}

void DataBase::exportDB(const unsigned char* str, unsigned int strSize)const
{
	Arry fileName;
	for (int i = 7; i < strSize; ++i)
	{
		if (str[i] != 0 )
		{
			fileName.addElement(str[i]);
		}
		else
		{
			break;
		}
	}
	fileName.addElement('\0');
	std::fstream file;
	file.open((char*)fileName.m_bytes, std::ios_base::binary | std::ios_base::out);
	if (!file.is_open())
	{
		throw "Can not write to file";
	}
	DataBase tmp(*this);
	tmp.sortingDNP();
	for (int i = 0; i < size; ++i)
	{
		file << tmp.data[i].getNomFli() << ", " << tmp.data[i].getAirFrom() << ", " <<
			tmp.data[i].getAirTo() << ", " << tmp.data[i].getDataFrom() << ", " <<
			tmp.data[i].getDataTo() << ", " << tmp.data[i].getCntTickets() << ", " <<
			std::fixed << std::setprecision(2) <<
			tmp.data[i].getPrice() << std::endl;
		/*if (i != (size - 1))
		{
			file << std::endl;
		}*/
	}
}

DataBase& DataBase::operator=(const DataBase& X)
{
	if (this != &X)
	{
		delete[]data;
		DataBase tmp(X);
		swap(tmp);
	}
	return *this;
}

void DataBase::swap(DataBase& other)
{
	std::swap(data, other.data);
	std::swap(size, other.size);
}

unsigned long long int DataBase::getIndex(const unsigned int ID) const
{
	for (int i = 0; i < size; ++i)
	{
		if (this->data[i].getID() == ID) { return i; }
	}
}
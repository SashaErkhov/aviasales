#include "Array.h"
#include <iostream>

Arry::Arry(unsigned long long int size)
{
	/*if (size != 0)
	{
		m_bytes = new unsigned char[size];
	}
	else
	{
		m_bytes = nullptr;
	}*/
	m_bytes = new char[size];
	this->size = size;
}

Arry::~Arry() 
{
	delete m_bytes;
	size = 0;
}

char Arry::getElement(unsigned long long int pos)
{
	return m_bytes[pos];
}

void Arry::addElement(const char elem)
{
	Arry tmp(size + 1);
	for (int i = 0; i < size; ++i)
	{
		tmp.setElement(i, (*this).getElement(i));
	}
	tmp.m_bytes[size] = elem;
	std::swap(m_bytes, tmp.m_bytes);
	++size;
}

void Arry::setElement(unsigned long long int pos, const char value)
{
	m_bytes[pos] = value;
}

void Arry::addPhraze(const char* phraze, unsigned int size)
{
	for (int i = 0; i < size; ++i)
	{
		this->addElement((unsigned char)phraze[i]);
	}
}
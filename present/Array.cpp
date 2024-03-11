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
	m_bytes = new unsigned char[size];
	this->size = size;
}

Arry::Arry(const Arry& X)
{
	this->size = X.size;
	this->m_bytes = new unsigned char[this->size];
	for (int i = 0; i < this->size; ++i)
	{
		this->m_bytes[i] = X.m_bytes[i];
	}
}

Arry::~Arry() 
{
	delete m_bytes;
	size = 0;
}

unsigned char Arry::getElement(unsigned long long int pos)
{
	return m_bytes[pos];
}

void Arry::addElement(unsigned char elem)
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

void Arry::setElement(unsigned long long int pos, unsigned char value)
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

#include <iostream>
Arry& Arry::operator=(const Arry& X)
{
	if (this != &X)
	{
		delete[]m_bytes;
		Arry tmp(X);
		std::swap(this->m_bytes, tmp.m_bytes);
		std::swap(this->size, tmp.size);
	}
	return *this;
}
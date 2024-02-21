#pragma once
#ifndef ARRAY_OUR_WORK
#define ARRAY_OUR_WORK

class Arry{
	unsigned long long int size;
public:
	unsigned char* m_bytes;
	Arry(unsigned long long int size=0);
	void addElement(unsigned char elem);
	//void removeEleent(size_t pos);
	unsigned char getElement(unsigned long long int pos);
	void setElement(unsigned long long int pos, unsigned char value);
	//void resize(size_t new_size);
	~Arry();
	unsigned long long int getSize() const
	{
		return size;
	}
};

#endif // !ARRAY_OUR_WORK
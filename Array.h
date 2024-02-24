#pragma once
#ifndef ARRAY_OUR_WORK
#define ARRAY_OUR_WORK

class Arry{
public:
	unsigned long long int size;
	char* m_bytes;
	Arry(unsigned long long int size=0);
	void addElement(const char elem);
	void addPhraze(const char* phraze, unsigned int size);
	//void removeEleent(size_t pos);
	char getElement(unsigned long long int pos);
	void setElement(unsigned long long int pos, const char value);
	//void resize(size_t new_size);
	~Arry();
	unsigned long long int getSize() const
	{
		return size;
	}
};

#endif // !ARRAY_OUR_WORK
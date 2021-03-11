#pragma once

//zad1

template <class T>
class myVector
{
	T* table;
	int currentSize;
	int realSize;

public:
	myVector();
	myVector(int size);
	~myVector();
	T first();
	T last();
	int size();
	void add(T elem);
	void remove(int index);
	T get(int index);

};

template <class T>
myVector<T>::myVector() 
{
	int size = 5;
	table = new T[size];
	currentSize = 0;
	realSize = size;
}

template <class T>
myVector<T>::myVector(int size) 
{
	table = new T[size];
	currentSize = 0;
	realSize = size;
}

template <class T>
myVector<T>::~myVector() 
{
	delete[] table;
}

template <class T>
T myVector<T>::first()
{
	return table[0];
}

template <class T>
T myVector<T>::last() 
{
	return table[currentSize - 1];
}

template <class T>
int myVector<T>::size() 
{
	return currentSize;
}

template <class T>
void myVector<T>::add(T elem) 
{
	if (currentSize == realSize)
	{
		T* temp = new T[realSize + 5];
		for (int i = 0; i < currentSize; i++)
			temp[i] = table[i];
		delete[] table;
		table = temp;
		realSize += 5;
	}
	table[currentSize] = elem;
	currentSize++;
}

template <class T>
void myVector<T>::remove(int index)
{
	for (int i = index; i < currentSize - 1; i++)
		table[i] = table[i + 1];
	currentSize--;
	if (currentSize + 5 < realSize)
	{
		T* temp = new T[realSize - 5];
		for (int i = 0; i < currentSize; i++)
			temp[i] = table[i];
		delete[] table;
		table = temp;
		realSize -= 5;
	}
}

template <class T>
T  myVector<T>::get(int index)
{
	return table[index];
}

//zad2

template <class T, class T2>
void function(T& elem, T2 add)
{
	elem += add;
}

template <class T>
void function(T& elem)
{
	elem++;
}
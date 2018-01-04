#ifndef COLLECTION_H
#define COLLECTION_H

template<class T>
class Collection
{
	public:
		Collection();
		
		Collection(int size);
		void operator=(const Collection& c);
		
		void add(T t);
		void set(int index, T t);
		
		T& get(int index);
		
		int getSize();
		
		~Collection();
		
	private:
		unsigned int size;
		
		unsigned int numItems;
		
		T* collection;
		
		void alloc(int newSize);

};

template<class T>
Collection<T>::Collection()
{
	this->numItems = 0;
	this->size = 10;
	collection = new T[size];
}

template<class T>
Collection<T>::Collection(int size)
{
	this->numItems = 0;
	this->size = size;
	collection = new T[size];
}

template<class T>
Collection<T>::operator=(const Collection& c)
{
	alloc(c.size);
	
	for(int i = 0; i < c.numItems; ++i)
	{
		this->collection[i] = c.collection[i];
	}
}

template<class T>
void Collection<T>::add(T t)
{
	if((numItems + 1) >= size)
	{
		alloc(size + 5);
	}
	this->collection[numItems] = t;
	this->numItems++;
}

template<class T>
void Collection<T>::set(int index, T t)
{
	if(index < numItems && index >= 0)
	{
		this->collection[index] = t;
	}
}

template<class T>
T& Collection<T>::get(int index)
{
	return this->collection[index];
}

template<class T>
int Collection<T>::getSize()
{
	return numItems;
}

template<class T>
void Collection<T>::alloc(int newSize)
{
	T* temp = new T[newSize];
	
	for(int i = 0; i < newSize; ++i)
	{
		temp[i] = this->collection[i];
	}
	T* trash = this->collection;
	
	this->collection = temp;
	this->size = newSize;
	
	delete [] trash;
}

template<class T>
Collection<T>::~Collection()
{
	delete [] this->collection;
}

#endif
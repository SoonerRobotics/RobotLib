#ifndef COLLECTION_H
#define COLLECTION_H

template<class T>
class Collection
{
	public:
		Collection();
		
		Collection(int size);
		
		void add(T t);
		
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
void alloc(int newSize)
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
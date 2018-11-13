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
		
		T& get(int index); //difference between pointer and passing by reference?
		
		int getSize();
		
		~Collection();
		
	private:
		unsigned int size;
		
		unsigned int numItems;
		
		T* collection; //line 16
		
		void alloc(int newSize);

};

/*
	Creates an empty Collection with size 10.
*/
template<class T>
Collection<T>::Collection()
{
	this->numItems = 0;
	this->size = 10;
	collection = new T[size];
}

/*
	Creates an empty Collection with specified size.

	@param size - size of the Collection
*/
template<class T>
Collection<T>::Collection(int size)
{
	this->numItems = 0;
	this->size = size;
	collection = new T[size];
}

/*
	Equal sign copies another Collection

	@param c - Collection to be copied
*/
template<class T>
void Collection<T>::operator=(const Collection<T>& c)
{
	alloc(c.size);
	
	for(int i = 0; i < c.numItems; ++i)
	{
		this->collection[i] = c.collection[i];
	}
}

/*
	Adds t to the Collection.

	@param t
*/
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

/*
	Sets the value at index to t

	@param t - new value of that index

	@param index - index to be changed in collection
*/
template<class T>
void Collection<T>::set(int index, T t)
{
	if(index < numItems && index >= 0)
	{
		this->collection[index] = t;
	}
}

/*
	Returns value at index

	@param index - int on interval [0,size)

	@return value at index
*/
template<class T>
T& Collection<T>::get(int index)
{
	return this->collection[index];
}

/*
	Returns size of collection

	@return size of collection
*/
template<class T>
int Collection<T>::getSize()
{
	return numItems;
}

/*	
	Changes the size of the Collection object (Does this assume that the new size is smaller?)
	
	@param newSize - 

*/
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

/*
	Destructor (what are these for?)
*/
template<class T>
Collection<T>::~Collection()
{
	delete [] this->collection;
}

#endif
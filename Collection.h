#ifndef COLLECTION_H
#define COLLECTION_H

template<class T>
class Collection
{
	public:
		Collection()
		{
			this->numItems = 0;
			this->size = 10;
			collection = new T[size];
		}
		
		Collection(int size)
		{
			this->numItems = 0;
			this->size = size;
			collection = new T[size];
		}
		
		void add(T t)
		{
			if((numItems + 1) >= size)
			{
				alloc(size + 5);
			}
			this->collection[numItems] = t;
			this->numItems++;
		}
		
		T* get(int index)
		{
			if(index < numItems && index >= 0)
			{
				return &this->collection[index];
			}
			
			return NULL;
		}
		
	private:
		unsigned int size;
		
		unsigned int numItems;
		
		T* collection;
		
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

};

#endif
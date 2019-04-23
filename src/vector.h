#include<iostream>
#ifndef VECTOR_H_
#define VECTOR_H_

template<typename Type>
class vector
{
private:
    int m_count; //amount of elements in mp_data array

    int m_size; //count + freespace

    Type* mp_data; //points to array of elements

public:
//CONSTRUCTORS:
    //Default Constructor
    vector();
    //Size specific (s) constructor
    explicit vector(int s);
    //Copy Constructor
    vector(const vector&);

//OVERLOADED OPERATORS:
    //overloaded assignment operator
    vector& operator = (const vector& other);

    //overloaded array access operator
    const Type& operator [] (unsigned int n);

//MEMBER FUNCTIONS:
    /*Function: size()
     * POSTCONDITIONS: returns the current maximum size of the dynamic array needed before resizing
     */
    int size() const; //returns the maximum current size of the vector

    /*Function: capacity()
     * POSTCONDITIONS: returns the amount of space remaining before the dynamic array must be resized
     */
    int capacity() const; //returns the free_space - count of the vector

    /*Function: resize()
     * PRECONDITIONS: newsize must be a positive integer
     * POSTCONDITIONS: resizes the dynamic array
     */
    void resize(int newsize); //resizes the vector, removing data if needbe.

    /*Function: push_back()
     * PRECONDITIONS: val must be of the valid type
     * POSTCONDITIONS: adds val to the end of the dynamic array, resizing the array if needbe
     */
    void push_back(Type val); //adds new data to the end of the vector, resizing if neebe

    /*Function: reserve()
     * PRECONDITIONS: newalloc must be a positive integer
     * POSTCONDITIONS: replaces the dynamic array adding newalloc to its maximum size
     */
    void reserve(int newalloc); //adds to the maximum size of the vector

    //establishes iterator as a pointer to Type
    using iterator = Type*;

    using const_iterator = const Type*;

    /*Function: begin()
     * POSTCONDITIONS: returns the address at the first element of the array.
     */
    iterator begin(); //points to first element in array

    /*Function: end()
     * POSTCONDITIONS: returns the address of one passed the last element of the array
     */
    iterator end(); //returns one passed the last element in the array.

    const_iterator end() const; //returns one passed last element in array.

    /*Function: insert()
     * PRECONDITIONS: iterator must point to an element in the array.
     * POSTCONDITIONS: inserts newData into the array before to where it is pointing
     */
    iterator insert(iterator it, const Type& newData);

    /*Function: erase()
     * PRECONDITIONS: iterator must point to an element in the array.
     * POSTCONDITIONS: erases the data at it, and shifts the elements in the array to the left
     */
    iterator erase(iterator it);

    /*Function: print()
     * POSTCONDITIONS: prints the data using the cout operation
     */
    void print(); //uses the << operator to print the data in the function.

    //for debugging:
    //void printinfo(); //prints m_size, m_count, and lists the data for debugging

private:
    void push_data(int index, Type newData); //pushes data at 'index'

    int getIteratorIndex(iterator it) //returns the index of the data pointed to by the iterator
    {
        bool found = false; //flags to break the loop
        vector<Type>::iterator it2;
        int index = 0;
        for(it2 = begin(); it2 != end() && !found; ++it2)
        {
            if(*it2 == *it)
                found = true;
            else
                ++index;
        }
        return index;
    }
};

template<typename Type>
vector<Type> :: vector() //default constructor
{
    m_count = 0;
    m_size = 0;
    mp_data = nullptr;
}

template<typename Type>
vector<Type> :: vector(int size) //specific size constructor
{
    m_count = 0;
    m_size = 0;
    reserve(size);
}

template<typename Type>
vector<Type> :: vector(const vector& other) //copy constructor
{
    m_count = other.m_count;
    m_size = other.m_size;
    reserve(m_size);

    for(int i = 0; i < m_size; ++i)
        mp_data[i] = other.mp_data[i];
}

template<typename Type>
vector<Type>& vector<Type> :: operator = (const vector& other) //overloaded assignment operator
{
    Type *pT = new Type[other.m_size];
    std::copy(other.mp_data, other.mp_data + other.m_size, pT);
    delete [] mp_data;
    mp_data = pT;
    m_size = other.m_size;
    m_count = other.m_count;
}

template<typename Type>
const Type& vector<Type> :: operator [] (unsigned int n) //overloaded index operator
{
    if(n >= m_count)
    {
        std::cout << "data attempted to access with [] is uninitialized... returning default object";
        Type returnItem;
        return returnItem;
    }
    return mp_data[n];
}

template<typename Type>
void vector<Type> :: resize(int newsize) //set vector to new maximum size
{
    Type* temp = mp_data; //store pointer to delete old data
    m_size = newsize; //reset the size of the array

    if(newsize < m_count) //resets count if data is deleted from array
        m_count = newsize;

    Type* newArray = new Type[newsize]; //prepare new array
    for(int i = 0; i < m_count; ++i) //copy data
        newArray[i] = temp[i];

    mp_data = newArray; //set mp_data pointer to new sized array
    delete [] temp; //delete old data
}

template<typename Type>
void vector<Type> :: reserve(int newalloc) //adds newalloc amount of elements to the array
{
    Type* temp = mp_data; //store pointer to delete old data
    m_size = m_size + newalloc;

    Type* newArray = new Type[m_size]; //create new array for mp_data to point to
    for(int i = 0; i < m_count; ++i) //copy the data
        newArray[i] = temp[i];

    for(int i = m_count; i < m_size; ++i)
        newArray[i] = Type();


    mp_data = newArray; //mp_data points to the new array
    delete [] temp; //delete the old array.
}

template<typename Type>
int vector<Type> :: capacity() const //returns the remaining capacity of the vector
{
    return (m_size - m_count);
}

template<typename Type>
int vector<Type> :: size() const //returns maximum size of the array.
{
    return m_count;
}

template<typename Type>
void vector<Type> :: print() //prints the data in the array by means of cout
{
    for(int i = 0; i < m_count; i++)
        std::cout << mp_data[i] << " ";
}

template<typename Type>
void vector<Type> :: push_back(Type newData) //adds new element to the array, recreating the array if needbe for sizing purposes
{
    if(capacity() == 0)
        reserve(1);

    mp_data[m_count] = newData;
    ++m_count;
}

template<typename Type>
void vector<Type> :: push_data(int index, Type newData) //pushes the data 1 element to the right
{
    if(capacity() == 0)
        reserve(1);
    for(int i = (m_count-1); i > index-1; --i)
        mp_data[i+1] = mp_data[i];
    mp_data[index] = newData;
    ++m_count;
}

template<typename Type>
Type* vector<Type> :: begin()
{
    return &mp_data[0];
}

template<typename Type>
Type* vector<Type> :: end()
{
    return &mp_data[m_count];
}

template<typename Type>
const Type* vector<Type> :: end() const //returns one passed last element in array.
{
    return &mp_data[m_count];
}

template<typename Type>
Type* vector<Type> :: insert(iterator it, const Type& newData)
{
    vector<Type>::iterator returnIt = it;
    push_data(getIteratorIndex(it),newData);

        ++returnIt;
    return returnIt; //returns the iterator pointing to original data
}

template<typename Type>
Type* vector<Type> :: erase(iterator it)
{
    vector<Type>::iterator returnIt = it;
    for(; it < end();++it)
        *it = *(it+1);

    --m_count;
    return returnIt;
}

//for debugging
//template<typename Type>
//void vector<Type> :: printinfo()
//{
//	std::cout << "m_size : " << m_size << std::endl
//			<< "m_count : " << m_count << std::endl;
//	print();
//}

#endif /* VECTOR_H_ */

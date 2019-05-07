#include<iostream>
#ifndef VECTOR_H_
#define VECTOR_H_

/**
 * @brief Dynamic array to store data; stores the shapes that are drawn on the canvas.
 */
template<typename Type>
class GoldenConeVector
{
private:
    int m_count; //amount of elements in mp_data array
    int m_size; //count + freespace
    Type* mp_data; //points to array of elements

public:
    /**
     * @brief Constructor
     */
    GoldenConeVector();

    /**
     * @brief Constructor
     *
     * @param s: the predefined size of internal array
     */
    explicit GoldenConeVector(int s);

    /**
     * @brief Copy Constructor
     *
     * @param GoldenConeVector to copy from
     */
    GoldenConeVector(const GoldenConeVector&);

    /**
     *@brief Destructor
     */
    ~GoldenConeVector();

    /**
     * @brief Copy Assignment Operation
     *
     * @param other: GoldenConeVector to copy from
     * @return GoldenConeVector& other
     */

    GoldenConeVector& operator = (const GoldenConeVector& other);

    /**
     * @brief Returns the data at index n
     *
     * @param n: index of data in the array
     * @return Type&: data at index n
     */
    const Type& operator [] (unsigned int n);

    /**
     * @brief Total size of the dynamic array
     *
     * @return unsigned int n: total size of the array
     */
    int size() const; //returns the maximum current size of the vector

    /**
     * @brief Remaining space in the dynamic array before more memory must be allocated
     *
     * @return int: remaining free space in the array
     */
    int capacity() const; //returns the free_space - count of the vector

    /**
     * @brief Resizes the GoldenConeVector.
     *
     * @param newsize: new size of the vector
     */

    void resize(int newsize); //resizes the vector, removing data if needbe.

    /**
     * @brief Adds data to the end of the vector, resizing the vector if necessary
     *
     * @param val: data to be added to the vector.
     */

    void push_back(Type val); //adds new data to the end of the vector, resizing if neebe

    /**
     * @brief Allocates additional memory to the array
     *
     * @param newalloc: increases size of array by this amount
     */

    void reserve(int newalloc); //adds to the maximum size of the vector

    using iterator = Type*;

    using const_iterator = const Type*;

    /**
     * @brief Set pointer to first element in the vector
     *
     * @return iterator: iterator pointing to first element
     */
    iterator begin(); //points to first element in array

    /**
     * @brief set pointer to one passed the last element in the vector
     *
     * @return iterator: iterator pointing to one passed the last element
     */
    iterator end(); //returns one passed the last element in the array.

    /**
     * @brief set pointer to one passed the last element in the vector
     *
     * @return iterator: iterator pointing to one passed the last element
     */
    const_iterator end() const; //returns one passed last element in array.

    /**
     * @brief inserts new data into vector at certain point
     *
     * @param it: points to element after newData
     * @param newData: data added before it
     * @return pointer to it
     */
    iterator insert(iterator it, const Type& newData);

    /**
     * @brief deletes pointed to data
     *
     * @param it: points to data to be removed
     * @return data pointed to by it
     */
    iterator erase(iterator it);

    void print(); //uses the << operator to print the data in the function.

private:
    void push_data(int index, Type newData); //pushes data at 'index'

    int getIteratorIndex(iterator it) //returns the index of the data pointed to by the iterator
    {
        bool found = false; //flags to break the loop
        GoldenConeVector<Type>::iterator it2;
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
GoldenConeVector<Type> :: GoldenConeVector() //default constructor
{
    m_count = 0;
    m_size = 0;
    mp_data = nullptr;
}

template<typename Type>
GoldenConeVector<Type> :: GoldenConeVector(int size) //specific size constructor
{
    m_count = 0;
    m_size = 0;
    reserve(size);
}

template <typename Type>
GoldenConeVector<Type>::~GoldenConeVector()  //destructor
{
    delete [] mp_data;
}

template<typename Type>
GoldenConeVector<Type> :: GoldenConeVector(const GoldenConeVector& other) //copy constructor
{
    m_count = other.m_count;
    m_size = other.m_size;
    reserve(m_size);

    for(int i = 0; i < m_size; ++i)
        mp_data[i] = other.mp_data[i];
}

template<typename Type>
GoldenConeVector<Type>& GoldenConeVector<Type> :: operator = (const GoldenConeVector& other) //overloaded assignment operator
{
    Type *pT = new Type[other.m_size];
    std::copy(other.mp_data, other.mp_data + other.m_size, pT);
    delete [] mp_data;
    mp_data = pT;
    m_size = other.m_size;
    m_count = other.m_count;
}

template<typename Type>
const Type& GoldenConeVector<Type> :: operator [] (unsigned int n) //overloaded index operator
{
    if (n >= m_count)
    {
        std::cout << "data attempted to access with [] is uninitialized... returning default object";
        Type returnItem;
        return returnItem;
    }
    return mp_data[n];
}

template<typename Type>
void GoldenConeVector<Type> :: resize(int newsize) //set vector to new maximum size
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
void GoldenConeVector<Type> :: reserve(int newalloc) //adds newalloc amount of elements to the array
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
int GoldenConeVector<Type> :: capacity() const //returns the remaining capacity of the vector
{
    return (m_size - m_count);
}

template<typename Type>
int GoldenConeVector<Type> :: size() const //returns maximum size of the array.
{
    return m_count;
}

template<typename Type>
void GoldenConeVector<Type> :: print() //prints the data in the array by means of cout
{
    for(int i = 0; i < m_count; i++)
        std::cout << mp_data[i] << " ";
}

template<typename Type>
void GoldenConeVector<Type> :: push_back(Type newData) //adds new element to the array, recreating the array if needbe for sizing purposes
{
    if(capacity() == 0)
        reserve(1);

    mp_data[m_count] = newData;
    ++m_count;
}

template<typename Type>
void GoldenConeVector<Type> :: push_data(int index, Type newData) //pushes the data 1 element to the right
{
    if(capacity() == 0)
        reserve(1);
    for(int i = (m_count-1); i > index-1; --i)
        mp_data[i+1] = mp_data[i];
    mp_data[index] = newData;
    ++m_count;
}

template<typename Type>
Type* GoldenConeVector<Type> :: begin()
{
    return &mp_data[0];
}

template<typename Type>
Type* GoldenConeVector<Type> :: end()
{
    return &mp_data[m_count];
}

template<typename Type>
const Type* GoldenConeVector<Type> :: end() const //returns one passed last element in array.
{
    return &mp_data[m_count];
}

template<typename Type>
Type* GoldenConeVector<Type> :: insert(iterator it, const Type& newData)
{
    GoldenConeVector<Type>::iterator returnIt = it;
    push_data(getIteratorIndex(it),newData);

        ++returnIt;
    return returnIt; //returns the iterator pointing to original data
}

template<typename Type>
Type* GoldenConeVector<Type> :: erase(iterator it)
{
    GoldenConeVector<Type>::iterator returnIt = it;
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

/*
 * This assignment was made by Edvin Schölin (edvsc779) and Wilmer Segerstedt (wilse150).
 * This is a template class for an implementation of a vector. See template methods for the
 * implementation.
 */

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:

    MyVector();

    ~MyVector();

    /*
     * Copy constructor which sets capacity and numberOfElements to
     * other's and fills storage with other's elements.
     */
    MyVector(const MyVector& other);

    /*
     * Equal operator used in order to set a vector to another vector.
     */
    MyVector& operator =(const MyVector& other);

    /*
     * Appends element to the vector. If capacity is equal to numberOfElements
     * the method doubles storage's capacity
     */
    void push_back(const T&);

    /*
     * Removes the last element in the vector.
     */
    void pop_back();

    /*
     * Returns reference to element at the given index.
     */
    T& operator[](unsigned i);

    /*
     * Returns const reference to element at the given index.
     */
    const T& operator[](unsigned i)const;

    void remove(unsigned i);

    /*
     * Returns whether the vector is empty or not.
     */
    bool empty()const;

    /*
     * Returns pointer to the beginning of the vector.
     */
    T* begin();

    /*
     * Returns pointer to the an element after the last
     * element the vector.
     */
    T* end();

    /*
     * Clears the vector of all containing elements.
     */
    void clear();

    /*
     * Returns numberOfElements.
     */
    unsigned size()const;

private:
    T* storage;
    unsigned capacity;
    unsigned numberOfElements;

    void setElemetents(const MyVector& other) {
        for (int i = 0; i < other.numberOfElements; i++) {
            storage[i] = other.storage[i];
        }
    }
};

template<typename T>
MyVector<T>::MyVector(){
    this->storage = new T [1];
    this->capacity = 1;
    this->numberOfElements = 0;
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] storage;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    storage = new T [other.capacity];
    setElemetents(other);
    numberOfElements = other.numberOfElements;
    capacity = other.capacity;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other){
    if (this != &other) {
        delete[] storage;
        storage = new T [other.capacity];
        capacity = other.capacity;
        numberOfElements = other.numberOfElements;
        setElemetents(other);
    }

    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    if (numberOfElements == capacity) {
        T* temp = new T[2*capacity];
        for (int i = 0; i < numberOfElements; i++) {
            temp[i] = storage[i];
        }

        delete[] storage;
        storage = temp;
        capacity *= 2;
    }

    storage[numberOfElements] = e;
    numberOfElements += 1;
}

//template<typename T>
//void MyVector<T>::push_back(const T& e){
//    if (numberOfElements == capacity) {
//        T* temp = new T[capacity + 1];
//        for (int i = 0; i < numberOfElements; i++) {
//            temp[i] = storage[i];
//        }

//        delete[] storage;
//        storage = temp;
//        capacity++;
//    }

//    storage[numberOfElements] = e;
//    numberOfElements += 1;
//}

template<typename T>
void MyVector<T>::pop_back(){
    numberOfElements -= 1;
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return storage[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return storage[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    return numberOfElements == 0;
}

template<typename T>
void MyVector<T>::clear(){
    delete[] storage;
    storage = new T [1];
    numberOfElements = 0;
    capacity = 1;
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}

template<typename T>
T* MyVector<T>::begin(){
    return &storage[0];
}

template<typename T>
T* MyVector<T>::end(){
    return &storage[numberOfElements];
}

#endif // MY_VECTOR_H

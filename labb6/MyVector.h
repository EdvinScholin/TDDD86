// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    MyVector();

    ~MyVector();

    MyVector(const MyVector& other);

    MyVector& operator =(const MyVector& other);


    void push_back(const T&);

    void pop_back();

    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    void remove(unsigned i);

    bool empty()const;

    T* begin();

    T* end();

    void clear();

    unsigned size()const;

private:
    T* storage;
    unsigned capacity;
    unsigned numberOfElements;
};

template<typename T>
MyVector<T>::MyVector(){
    this->storage = new T [1];
    this->capacity = 1;
    this->numberOfElements = 0;
}

template<typename T>
MyVector<T>::~MyVector(){
    delete storage;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    storage = new T [other.capacity];
    //copy(begin(other.storage), end(other.storage), begin(storage)); // WE think this right is, yes!
    for (int i = 0; i < other.numberOfElements; i++) {
        storage[i] = other.storage[i];
    }
    numberOfElements = other.numberOfElements;
    capacity = other.capacity;
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if (this != &other) {
        delete storage;
        storage = new T [other.capacity];
        capacity = other.capacity;
        numberOfElements = other.numberOfElements;
        //copy(begin(other.storage), end(other.storage), begin(storage));
        for (int i = 0; i < other.numberOfElements; i++) {
            storage[i] = other.storage[i];
        }
    }

    return *this; // kanske rätt
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    if (numberOfElements == capacity) {
        T* temp = new T[2*capacity];
        //copy(begin(storage), end(storage), begin(temp));
        for (int i = 0; i < numberOfElements; i++) {
            temp[i] = storage[i];
        }

        //delete storage;
        storage = temp; //Osäker med hur man gör med pekare
        delete[] temp;
        capacity *= 2;
    }

    storage[numberOfElements] = e;
    numberOfElements += 1;

}

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
    delete storage;
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
    return &storage;
}

template<typename T>
T* MyVector<T>::end(){
    return &(storage + capacity);
}

#endif // MY_VECTOR_H

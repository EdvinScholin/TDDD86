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
    // private members?

};

template<typename T>
MyVector<T>::MyVector(){
    this->storage = new T [1];
    this->capacity = 1;
    this->numberOfElements = 0;
    MYEXCEPTION("unimplemented method");
}

template<typename T>
MyVector<T>::~MyVector(){
    delete storage;
    MYEXCEPTION("unimplemented method");
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
//    for (int i = 0; i < other.storage.size(); i++) {
//        storage[i] = other.storage[i];
//    }
    storage = new T [other.capacity];
    copy(begin(other), end(other), begin(storage)); // WE think this right is, yes!
    MYEXCEPTION("unimplemented method");
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if (this != &other) {
        delete storage;
        storage = new T [other.capacity];
        capacity = other.capacity;
        numberOfElements = other.numberOfElements;
        copy(begin(other), end(other), begin(storage));
    }

    return *this; // kanske rätt
    MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    if (numberOfElements == capacity) {
        T* temp = new T[2*capacity];
        copy(begin(storage), end(storage), begin(temp));
        delete storage;
        storage = temp; //Osäker med hur man gör med pekare
        storage[numberOfElements + 1] = e;
        capacity *= 2;
    }
    numberOfElements += 1;
    storage[numberOfElements] = e;
    MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::pop_back(){
    numberOfElements -= 1;
    MYEXCEPTION("unimplemented method");
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){

    MYEXCEPTION("unimplemented method");
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
bool MyVector<T>::empty()const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::clear(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
unsigned MyVector<T>::size()const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
T* MyVector<T>::begin(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
T* MyVector<T>::end(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

#endif // MY_VECTOR_H

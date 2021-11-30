// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"


template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    void push(const T& t);

    T top()const;

    void pop();

    bool empty()const;

private:
    // Other private members?
    int parent(int pos) {
        if (pos <= 0) return -1;
        return (pos-1)/2;
      }

    bool isLeaf(int pos) {
        return (pos >= vector_array.size()/2) && (pos < vector_array.size());
    }

    int leftchild(int pos) {
        if (pos >= vector_array.size()/2) return - 1;
        return 2*pos + 1;
      }
};

template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
}

template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    int currentPos = vector_array.size();
    vector_array[currentPos] = t;
    while ((currentPos != 0) && strictly_larger_operator(vector_array[parent(currentPos)], vector_array[currentPos])) {
//        T temp = vector_array[parent(currentPos)]; // byt plats på parent och currentPos
//        vector_array[parent(currentPos)] = vector_array[currentPos];
//        vector_array[currentPos] = temp;
        swap(vector_array[parent(currentPos)], vector_array[currentPos]);
        currentPos = parent(currentPos); // Tror detta är rätt
    }
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    vector_array[0] = vector_array[vector_array.size() - 1];
    vector_array.pop_back();

    int currentPos = 0;
    if (currentPos < 0 || currentPos > vector_array.size()) {
        return;
    }
    while (!isLeaf(currentPos)) {
       int child = leftchild(currentPos);
       if ((child < vector_array.size() - 1) && strictly_larger_operator(vector_array[currentPos + 1], vector_array[currentPos])) { // which of the siblings is largest
           child++; // becomes right child
       }

       if (strictly_larger_operator(vector_array[currentPos], vector_array[child])) {
//           T temp = vector_array[child]; // byt plats på parent och currentPos
//           vector_array[child] = vector_array[currentPos];
//           vector_array[currentPos] = temp;
           swap(vector_array[child], vector_array[currentPos]);
           currentPos = child; // Tror detta är rätt
       }
    }
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.empty();
}

#endif // MY_PRIORITY_QUEUE_H

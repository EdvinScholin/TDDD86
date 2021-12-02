/*
 * This assignment was made by Edvin Schölin (edvsc779) and Wilmer Segerstedt (wilse150).
 * This is a template class for an implementation of a priority queue.
 * The code is based on an OpenDSA example. See template methods for the
 * implementation.
 */

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

    /*
     * Places an object t to appropriate position in MyVector.
     */
    void push(const T& t);

    /*
     * Returns element with highest priority.
     */
    T top()const;

    /*
     * Removes element with highest priority.
     */
    void pop();

    /*
     * Returns whether the queue is empty or not.
     */
    bool empty()const;

private:
    int parent(int pos) {
        return (pos-1)/2;
      }

    bool isLeaf(int pos) {
        return (pos >= (vector_array.size()/2)) && (pos < vector_array.size());
    }

    int leftchild(int pos) {
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
    vector_array.push_back(t);
    int currentPos = vector_array.size() - 1;
    while ((currentPos != 0) && strictly_larger_operator(vector_array[parent(currentPos)], vector_array[currentPos])) {
        swap(vector_array[parent(currentPos)], vector_array[currentPos]);
        currentPos = parent(currentPos);
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
    while (!isLeaf(currentPos)) {
       int child = leftchild(currentPos);

       if (child >= vector_array.size()) {
           return;
       }

       if ((child + 1 < vector_array.size())) { // which of the siblings is largest
           if (strictly_larger_operator(vector_array[child], vector_array[child + 1])) {
               child++; // becomes right child
           }
       }

       if (strictly_larger_operator(vector_array[child], vector_array[currentPos])) {
           return;
       }

       swap(vector_array[child], vector_array[currentPos]);
       currentPos = child;
    }
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.empty();
}

#endif // MY_PRIORITY_QUEUE_H

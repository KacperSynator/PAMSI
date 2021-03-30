#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include "list.hpp"

template <typename T>
class Queue
{
    List<T> list;

  public:
    void enqueue(const T& newElement);
    T dequeue();
};

template <typename T>
void Queue<T>::enqueue(const T& newElement)
{
    list.pushBack(newElement);
}

template <typename T>
T Queue<T>::dequeue()
{
    T data=list[0];
    list.removeFront();
    return data;
}

#endif /* QUEUE_HPP_ */

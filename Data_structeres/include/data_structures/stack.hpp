#ifndef STACK_HPP_
#define STACK_HPP_

#include "list.hpp"

template <typename T>
class Stack
{
    List<T> list;

  public:
    void push(const T& newElement);
    T pop();
};

template <typename T>
void Stack<T>::push(const T& newElement)
{
  list.pushFront(newElement);
}

template <typename T>
T Stack<T>::pop()
{
  T data=list[0];
  list.removeFront();
  return data;
}

#endif /* STACK_HPP_ */

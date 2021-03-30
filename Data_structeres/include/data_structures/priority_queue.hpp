#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY_QUEUE_HPP_

#include "list.hpp"

template <typename T>
class PriorityQueue
{
  public:
    void enqueue(const T& newElement, int priority);
    T dequeue();

    struct PrioData
    {
        int prio;
        T data;
    };

  private:
    List<PrioData> list;
};


template <typename T>
void PriorityQueue<T>::enqueue(const T& newElement, int priority)
{
  PrioData newNode;
  newNode.prio=priority;
  newNode.data=newElement;
  unsigned int i=0;
  for(auto it = list.begin(); it != list.end() ; ++it)
  {
    if(priority > (*it).prio)
        break;
      i++;
  }

  list.insert(newNode,i);
}


template <typename T>
T PriorityQueue<T>::dequeue()
{
    T data = list[0].data;
    list.removeFront();
    return data;
}

#endif /* PRIORITY_QUEUE_HPP_ */

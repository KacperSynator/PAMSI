#ifndef LIST_HPP_
#define LIST_HPP_

#include <memory>
#include <cstdlib>
#include <exception>

template <typename T>
class List
{
  public:
    class Node
    {
      private:
        T data;
        std::shared_ptr<Node> next;
        std::shared_ptr<Node> prev;


      public:
        Node() {next= nullptr; prev= nullptr;}
        Node(std::shared_ptr<Node> _next, std::shared_ptr<Node> _prev, const  T& _data ) :
            next(_next), prev(_prev), data(_data) {}

        T& getData() {return data;}
        std::shared_ptr<Node> getNext() {return next;}
        std::shared_ptr<Node> getPrev() {return prev;}

        void setNext(std::shared_ptr<Node> newNext) {next=newNext;}
        void setPrev(std::shared_ptr<Node> newPrev) {prev=newPrev;}
    };

    class Iterator
    {
        std::shared_ptr<Node> currentNode;

      public:
        using difference_type = long;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::random_access_iterator_tag;

        Iterator(std::shared_ptr<Node> ptrNode= nullptr) : currentNode(ptrNode) {}

        Iterator operator++();
        Iterator operator--();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator<(const Iterator& other) const;
        difference_type operator-(const Iterator& other) const;
        Iterator operator+(difference_type diff) const;
        Iterator operator-(difference_type diff) const;
        Iterator operator[](std::size_t i);
        T& operator*();
    };

    class ConstIterator
    {
        std::shared_ptr<Node> currentNode= nullptr;
    public:
      using difference_type = long;
      using value_type = T;
      using pointer = const T*;
      using reference = const T&;
      using iterator_category = std::random_access_iterator_tag;

      ConstIterator(std::shared_ptr<Node> ptrNode = nullptr) : currentNode(ptrNode) {}

      ConstIterator operator++();
      ConstIterator operator--();
      bool operator==(const ConstIterator& other) const;
      bool operator!=(const ConstIterator& other) const;
      bool operator>(const ConstIterator& other) const;
      bool operator<(const ConstIterator& other) const;
      difference_type operator-(const ConstIterator& other) const;
      ConstIterator operator+(difference_type diff) const;
      ConstIterator operator-(difference_type diff) const;
      ConstIterator operator[](std::size_t i);
      const T& operator*();
    };

  private:
    std::shared_ptr<Node> head;
    unsigned int node_count;

  public:
    List() {node_count=0;}
    ~List(){clear();}

    void pushBack(const T& newElement);
    void pushFront(const T& newElement);
    void insert(const T& newElement, int index);
    void remove(const T& element);
    void removeFront ();
    void clear();
    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;
    T& operator[](int index);

};



template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++()
{

    if(currentNode != nullptr)
    {
        currentNode = currentNode->getNext();
        return currentNode;
    }
    else
        return Iterator(nullptr);
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--()
{
    if(currentNode != nullptr)
    {
        currentNode = currentNode->getPrev();
        return currentNode;
    }
    else
        return Iterator(nullptr);
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const
{
  return this->currentNode == other.currentNode;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const
{
  return !(*this == other);
}

template <typename T>
bool List<T>::Iterator::operator>(const Iterator& other) const
{
  if(*this==other) return false;
  if(this->currentNode == nullptr) return true;
  Iterator tmp(this->currentNode);
  while(tmp != other)
  {
      if(tmp.currentNode == nullptr)
          return false;

      --tmp;
  }
  return true;
}

template <typename T>
bool List<T>::Iterator::operator<(const Iterator& other) const
{
    if(*this==other) return false;
    if(this->currentNode == nullptr) return false;
    Iterator tmp(this->currentNode);
    while(tmp != other)
    {
        if(tmp.currentNode == nullptr)
            return false;

        ++tmp;
    }
    return true;
}

template <typename T>
typename List<T>::Iterator::difference_type List<T>::Iterator::operator-(const Iterator& other) const
{
    difference_type i = 0;
    Iterator tmp(other.currentNode);
    if(*this > other)
    {
        while(tmp != *this)
        {
            ++tmp;
            i++;
        }
    }
    else if(*this < other)
    {
        while(tmp != *this)
        {
            --tmp;
            i--;
        }
    }
    return i;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator+(difference_type diff) const
{
    Iterator  tmp(this->currentNode);
    for(difference_type j=0; j<diff; j++)
    {
        ++tmp;
    }
    return tmp;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator-(difference_type diff) const
{
    Iterator  tmp(this->currentNode);
    for(difference_type j=0; j<diff; j++)
    {
        --tmp;
    }
    return tmp;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator[](std::size_t i)
{
    Iterator  tmp(this->currentNode);
    for(std::size_t j=0; j<i; j++)
    {
        ++tmp;
    }
    return tmp;
}

template <typename T>
T& List<T>::Iterator::operator*()
{
    return currentNode->getData();
}


template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++()
{
    if(currentNode != nullptr)
    {
        currentNode = currentNode->getNext();
        return currentNode;
    }
    else
        return ConstIterator(nullptr);
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--()
{
    if(currentNode != nullptr)
    {
        currentNode = currentNode->getPrev();
        return currentNode;
    }
    else
        return ConstIterator(nullptr);
}


template <typename T>
bool List<T>::ConstIterator::operator==(const ConstIterator& other) const
{
  return this->currentNode == other.currentNode;
}

template <typename T>
bool List<T>::ConstIterator::operator!=(const ConstIterator& other) const
{
  return !(*this == other);
}

template <typename T>
bool List<T>::ConstIterator::operator>(const ConstIterator& other) const
{
    if(*this==other) return false;
    if(this->currentNode == nullptr) return true;
    ConstIterator tmp(this->currentNode);
    while(tmp != other)
    {
        if(tmp.currentNode == nullptr)
            return false;

        --tmp;
    }
    return true;
}

template <typename T>
bool List<T>::ConstIterator::operator<(const ConstIterator& other) const
{
    if(*this==other) return false;
    if(this->currentNode == nullptr) return false;
    ConstIterator tmp(this->currentNode);
    while(tmp != other)
    {
        if(tmp.currentNode == nullptr)
            return false;

        ++tmp;
    }
    return true;
}

template <typename T>
typename List<T>::ConstIterator::difference_type List<T>::ConstIterator::operator-(const ConstIterator& other) const
{
    difference_type i = 0;
    ConstIterator tmp(other.currentNode);
    if(*this > other)
    {
        while(tmp != *this)
        {
            ++tmp;
            i++;
        }
    }
    else if(*this < other)
    {
        while(tmp != *this)
        {
            --tmp;
            i--;
        }
    }
    return i;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator+(difference_type diff) const
{
    ConstIterator  tmp(this->currentNode);
    for(difference_type j=0; j<diff; j++)
    {
        ++tmp;
    }
    return tmp;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator-(difference_type diff) const
{
    ConstIterator  tmp(this->currentNode);
    for(difference_type j=0; j<diff; j++)
    {
        --tmp;
    }
    return tmp;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator[](std::size_t i)
{
    ConstIterator  tmp(this->currentNode);
    for(std::size_t j=0; j<i; j++)
    {
        ++tmp;
    }
    return tmp;
}

template <typename T>
const T& List<T>::ConstIterator::operator*()
{
    return currentNode->getData();
}









template <typename T>
void List<T>::pushBack(const T& newElement)
{
    node_count++;

    if(this->head == nullptr)
        this->head = std::make_shared<Node>(std::shared_ptr<Node>(nullptr), std::shared_ptr<Node>(nullptr), newElement);
    else
    {
        std::shared_ptr<Node> tmp;
        tmp = this->head;
        while(tmp->getNext() != nullptr)
            tmp = tmp->getNext();

        tmp->setNext(std::make_shared<Node>(std::shared_ptr<Node>(nullptr), tmp, newElement));
    }
}
template <typename T>
void List<T>::pushFront(const T& newElement)
{
    node_count++;

    if(this->head == nullptr)
        this->head = std::make_shared<Node>(std::shared_ptr<Node>(nullptr),std::shared_ptr<Node>(nullptr),newElement);

    else
      this->head=std::make_shared<Node>(this->head,std::shared_ptr<Node>(nullptr),newElement);

}
template <typename T>
void List<T>::insert(const T& newElement, int index)
{
    if(index ==0 && node_count>=0 )
    {
        pushFront(newElement);
        return;
    }
    if(index ==  node_count)
    {
        pushBack(newElement);
        return;
    }
    if(index+1>node_count || index<0)
    {
        throw "WrongIndex";
    }

    node_count++;

    std::shared_ptr<Node> tmp=this->head;
    for(int i=0;i<index;i++)
        tmp=tmp->getNext();

        std::shared_ptr<Node> tmp2 = tmp->getPrev(); // node before(prev) tmp
        tmp->setPrev(std::make_shared<Node>(tmp, tmp2, newElement));
        tmp2->setNext(tmp->getPrev());

}

template <typename T>
void List<T>::remove(const T& element)
{

    std::shared_ptr<Node> tmp=this->head;
    while(tmp != nullptr)
       {
           if(tmp->getData() == element)
           {
               node_count--;
               if(tmp->getNext() != nullptr)
                   tmp->getNext()->setPrev(tmp->getPrev());

               if(tmp->getPrev() != nullptr)
                   tmp->getPrev()->setNext(tmp->getNext());
               else
                   this->head=tmp->getNext();
           }
           tmp=tmp->getNext();
       }
}

template <typename T>

void List<T>::removeFront()
{
    node_count--;
    if(head->getNext()!= nullptr)
    {
        head->getNext()->setPrev(nullptr);
        head = head->getNext();
    }
    else
        head= nullptr;
}
template <typename T>
void List<T>::clear()
{
    while( head!= nullptr)
        removeFront();
}

template <typename T>
typename List<T>::Iterator List<T>::begin()
{
    return Iterator(head);
}

template <typename T>
typename List<T>::Iterator List<T>::end()
{
    return Iterator(nullptr);
}

template <typename T>
typename List<T>::ConstIterator List<T>::cbegin() const
{
    return ConstIterator(head);
}

template <typename T>
typename List<T>::ConstIterator List<T>::cend() const
{
    return ConstIterator(nullptr);
}

template <typename T>
T& List<T>::operator[](int index)
{
    if(index+1>node_count || index<0)
    {
        throw "WrongIndex";
    }
    std::shared_ptr<Node> tmp;
    tmp=this->head;

    for(int i=0;i<index;i++)
        tmp=tmp->getNext();

    return tmp->getData();
}


#endif /* LIST_HPP_ */

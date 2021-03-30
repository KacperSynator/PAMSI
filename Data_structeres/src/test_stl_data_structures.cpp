
#include "catch2/catch.hpp"

#include <list>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>

TEST_CASE("List_stl/push_front/pop_front")
{
    std::list<int> list;

    list.push_front(5);
    list.push_front(7);
    list.push_front(9);

    REQUIRE(list.front() == 9);
    list.pop_front();
    REQUIRE(list.front() == 7);
    list.pop_front();
    REQUIRE(list.front() == 5);
    list.pop_front();

}

TEST_CASE("List_stl/push_back/pop_back")
{
    std::list<int> list;

    list.push_back(5);
    list.push_back(7);
    list.push_back(9);

    REQUIRE(list.back() == 9);
    list.pop_back();
    REQUIRE(list.back() == 7);
    list.pop_back();
    REQUIRE(list.back() == 5);
    list.pop_back();

}

TEST_CASE("List_stl/iterator")
{
    std::list<int> list;

    int tab[3]={5,7,9};

    for(auto i : tab)
        list.push_back(i);

    int index=0;
    for(auto it=list.begin(); it!=list.end(); ++it)
        REQUIRE(*it == tab[index++]);
}


TEST_CASE("List_stl/remove")
{
    std::list<int> list;

    list.push_back(5);
    list.push_back(5);
    list.push_back(7);
    list.push_back(9);

    list.remove(5);
    REQUIRE(list.front() == 7);
    REQUIRE(list.back() == 9);

    list.remove(9);
    REQUIRE(list.front() == 7);
}

TEST_CASE("List_stl/insert")
{
    std::list<int> list;

    list.push_back(5);
    list.push_back(7);
    list.insert(++list.begin(),9);
    list.insert(++list.begin(),11);

    REQUIRE(list.front()==5);
    REQUIRE(list.back()==7);
    REQUIRE(*(++list.begin())==11);
    REQUIRE(*(++++list.begin())==9);
}

TEST_CASE("Stack_stl")
{
    std::stack<int> stack;

    stack.push(5);
    stack.push(7);
    stack.push(9);

    REQUIRE(stack.top()==9);
    stack.pop();
    REQUIRE(stack.top()==7);
    stack.pop();
    REQUIRE(stack.top()==5);
    stack.pop();
}

TEST_CASE("Queue_stl")
{
    std::queue<int> queue;

    queue.push(5);
    queue.push(7);
    queue.push(9);

    REQUIRE(queue.front()==5);
    queue.pop();
    REQUIRE(queue.front()==7);
    queue.pop();
    REQUIRE(queue.front()==9);
    queue.pop();
}

TEST_CASE("priority_queue_stl")
{
    std::priority_queue<int> pq;

    pq.push(7);
    pq.push(5);
    pq.push(9);

    REQUIRE(pq.top()==9);
    pq.pop();
    REQUIRE(pq.top()==7);
    pq.pop();
    REQUIRE(pq.top()==5);
    pq.pop();
}

TEST_CASE("map_stl")
{
 std::map<std::string,int> map;
 map.insert({"one",1});
 map.insert({"two",2});
 map.insert({"three",3});

 REQUIRE(map["one"]==1);
 REQUIRE(map["two"]==2);
 REQUIRE(map["three"]==3);
}
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "data_structures/list.hpp"
#include "data_structures/map.hpp"
#include "data_structures/priority_queue.hpp"
#include "data_structures/queue.hpp"
#include "data_structures/stack.hpp"

using namespace std::string_literals;


TEST_CASE("Map", "insert/operator[]")
{
    Map<std::string, int > hashArray;

    std::map< std::string , int> refHashArray = {{"one"s, 1}, {"two"s,2 }, {"three"s,3 }};

    for(auto& keyValue : refHashArray)
    {
        hashArray.insert(keyValue.first, keyValue.second);
    }

    for(auto& keyValue : refHashArray)
    {
        REQUIRE(keyValue.second == hashArray[keyValue.first]);
    }
}

TEST_CASE("List/pushFront")
{
    List<int> list;

    list.pushFront(1);
    list.pushFront(2);

    REQUIRE(list[0] == 2);
    REQUIRE(list[1] == 1);
}

TEST_CASE("List/pushBack")
{
    List<int> list;

    list.pushBack(1);
    list.pushBack(2);
    REQUIRE(list[0] == 1);
    REQUIRE(list[1] == 2);
}

TEST_CASE("List/insert")
{
    List<int> list;

    list.pushBack(1);
    list.pushBack(2);
    list.insert(3, 1);
    list.insert(4, 0);

    REQUIRE(list[0] == 4);
    REQUIRE(list[1] == 1);
    REQUIRE(list[2] == 3);
    REQUIRE(list[3] == 2);
}

TEST_CASE("List/remove")
{
    List<int> list;

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);

    list.remove(2);

    REQUIRE(list[0] == 1);
    REQUIRE(list[1] == 3);

    list.remove(1);

    REQUIRE(list[0] == 3);
}

TEST_CASE("List/iterator")
{
    List<int> list;

    list.pushBack(1);
    list.pushBack(3);
    list.pushBack(2);

    std::sort(list.begin(), list.end());

    REQUIRE(list[0] == 1);
    REQUIRE(list[1] == 2);
    REQUIRE(list[2] == 3);
}

TEST_CASE("List/ConstIterator")
{
    List<int> list;

    std::array<int, 3> refArray = {1, 2, 3};

    for(auto& element : refArray)
    {
        list.pushBack(element);
    }

    int index = 0;
    for(auto it = list.cbegin(); it != list.cend(); ++it)
    {
        REQUIRE(*it == refArray[index++]);
    }
}


TEST_CASE("Stack")
{
    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    REQUIRE(stack.pop() == 3);
    REQUIRE(stack.pop() == 2);
    REQUIRE(stack.pop() == 1);
}

TEST_CASE("Queue")
{
    Queue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    REQUIRE(queue.dequeue() == 1);
    REQUIRE(queue.dequeue() == 2);
    REQUIRE(queue.dequeue() == 3);
}

TEST_CASE("PriorityQueue")
{
    PriorityQueue<int> queue;

    queue.enqueue(1, 20);
    queue.enqueue(3, 5);
    queue.enqueue(2, 30);

    REQUIRE(queue.dequeue() == 2);
    REQUIRE(queue.dequeue() == 1);
    REQUIRE(queue.dequeue() == 3);
}


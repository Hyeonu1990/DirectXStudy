#include <iostream>
#include <list>
using namespace std;

template<typename T>
class Node
{
public:
    Node() : _prev(nullptr), _next(nullptr), _data(T())
    {

    }

    Node(const T& value) : _prev(nullptr), _next(nullptr), _data(value)
    {

    }

public:
    Node* _prev;
    Node* _next;
    T       _data;
};

template<typename T>
class Iterator
{
public:
    Iterator() : _node(nullptr)
    {

    }

    Iterator(Node<T>* node) : _node(node)
    {

    }

    Iterator& operator++()
    {
        _node = _node->_next;
        return *this;
    }

    Iterator operator++(int) // a++
    {
        Iterator<T> temp = *this; // �����ϱ� �� ������ ��������ڷ� ����
        _node = _node->_next;
        return temp;
    }

    Iterator& operator--()
    {
        _node = _node->_prev;
        return *this;
    }

    Iterator operator--(int) // a++
    {
        Iterator<T> temp = *this; // �����ϱ� �� ������ ��������ڷ� ����
        _node = _node->_prev;
        return temp;
    }

    T& operator*()
    {
        return _node->_data;
    }

    bool operator==(const Iterator& other)
    {
        return _node == other._node;
    }

    bool operator!=(const Iterator& other)
    {
        return _node != other._node;
    }

public:
    Node<T>* _node;
};

template<typename T>
class List
{
public:
    List() : _size(0)
    {
        _head = new Node<T>();
        _tail = new Node<T>();
        _head->_next = _tail;
        _tail->_prev = _head;
    }

    ~List()
    {
        while (_size > 0)
            pop_back();
        delete _head;
        delete _tail;
    }

    void push_back(const T& value)
    {
        AddNode(_tail, value);
    }

    void pop_back()
    {
        RemoveNode(_tail->_prev);
    }

private:
    // [prevNode] <-> [before]
    // [prevNode] <-> [newNode] <-> [before]
    Node<T>* AddNode(Node<T>* before, const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        Node<T>* prevNode = before->_prev;
        newNode->_next = before;
        newNode->_prev = prevNode;
        before->_prev = newNode;
        prevNode->_next = newNode;
        _size++;
        return newNode;
    }

    Node<T>* RemoveNode(Node<T>* node)
    {
        Node<T>* prevNode = node->_prev;
        Node<T>* nextNode = node->_next;

        prevNode->_next = nextNode;
        nextNode->_prev = prevNode;

        delete node;

        _size--;

        return nextNode;
    }

public:
    using iterator = Iterator<T>;

    iterator begin() { return iterator(_head->_next); }
    iterator end() { return iterator(_tail); }

    iterator insert(iterator it, const T& value)
    {
        return iterator(AddNode(it._node, value));
    }

    iterator erase(iterator it)
    {
        return iterator(RemoveNode(it._node));
    }


private:
    Node<T>* _head;
    Node<T>* _tail;
    int         _size;
};

template<typename T>
using LIST = List<T>; // list<T>

int ListTest()
{
    LIST<int> li;
    LIST<int>::iterator eraseIt;
    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
        {
            eraseIt = li.insert(li.end(), i);
        }
        else
            li.push_back(i);
    }

    li.pop_back();

    li.erase(eraseIt);

    for (LIST<int>::iterator it = li.begin(); it != li.end(); it++)
    {
        cout << (*it) << endl;
    }

    return 0;
}
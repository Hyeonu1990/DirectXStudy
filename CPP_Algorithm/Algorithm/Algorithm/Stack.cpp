#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;

template<typename T, typename Container = vector<T>>
class Stack
{
public:
    void push(const T& value)
    {
        _container.push_back(value);
    }
    void pop()
    {
        _container.pop_back();
    }
    T& top()
    {
        return _container.back();
    }
    bool empty() { return _container.empty(); }
    int size() { return _container.size(); }

private:
    //vector<T> _container;
    Container _container;
};


template<typename T>
using STACK = Stack<T, list<T>>; // stack<T>

int MyStack()
{
    // Stack (LIFO Last-In-First-Out 후입선출)

    STACK<int> s;

    s.push(1);
    s.push(2);
    s.push(3);

    while (s.empty() == false)
    {
        int data = s.top();
        cout << data << " size : " << s.size() << endl;
        s.pop();
    }
    cout << "size : " << s.size() << endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

template<typename T>
class ListQueue
{
public:
    void push(const T& value)
    {
        _container.push_back(value);
    }
    void pop()
    {
        //front값 지우기
        //_container.erase(_container.begin()); // vector 같은 배열형은 느리다
        _container.pop_front(); // list를 사용한 정석
    }
    T& front()
    {
        return _container.front();
    }
    bool empty() { return _container.empty(); }
    int size() { return _container.size(); }

private:
    list<T> _container;
};

// 순환방식 사용
// [front/back][][][][][][]
// [front][][][][][][back]
// [][][]front[][][][back]
// [][back][][][][front][]
template<typename T>
class ArrayQueue
{
public:
    ArrayQueue()
    {
        //_container.resize(100);
    }

    void push(const T& value)
    {
        //배열 capacity 다 찼는지 체크
        if (_size == _container.size())
        {
            int newSize = max(1, _size * 2);
            vector<T> newData;
            newData.resize(newSize);
            for (int i = 0; i < _size; i++)
            {
                int index = (_front + i) % _container.size();
                newData[i] = _container[index];
            }

            _container.swap(newData);
            _front = 0;
            _back = _size;
        }

        _container[_back] = value;
        _back = (_back + 1) % _container.size();
        _size++;
    }
    void pop()
    {
        _front = (_front + 1) % _container.size();
        _size--;
    }
    T& front()
    {
        return _container[_front];
    }
    bool empty() { return _size == 0; }
    int size() { return _size; }

private:
    vector<T> _container;
    int _front = 0;
    int _back = 0;
    int _size = 0;
};


template<typename T>
using QUEUE = ArrayQueue<T>;// queue<T>

int QueueTest()
{
    // Queue (FIFO First-In-First-Out 선입선출)

    QUEUE<int> q;

    for (int i = 0; i < 100; i++)
        q.push(i);

    while (q.empty() == false)
    {
        int data = q.front();
        cout << "data : " << data << ", size : " << q.size() << endl;
        q.pop();
    }
    cout << "size : " << q.size() << endl;
    return 0;
}
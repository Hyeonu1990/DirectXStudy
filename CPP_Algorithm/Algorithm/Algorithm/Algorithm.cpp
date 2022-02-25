#pragma region NOTE
// [동적 배열]
// push_back O(1)
// 중간 삽입/삭제 O(N)
// 임의 접근 O(1)
// 
// [연결 리스트]
// 삽입/삭제 O(1)
// 임의 접근 O(N)
// 
// [스택] O(1)
// 
// [큐] O(1) // list 방식으로 만들어졌을 경우
// 
#pragma endregion

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

// 이진 탐색 트리
// std::map

#pragma region 이진 탐색(binary search)

// 상황) 배열에 데이터가 정렬되어 있다
// [1][8][15][23][32][44][56][63][81][91]
// Q) 82라는 숫자가 배열에 있습니까?
// A) 순차적으로 찾으면 O(N), 정렬되있다는 기준하에 업다운 형식으로 찾으면 O(logN)

// - 정렬된 배열을 이용했기에 이진 탐색 가능
// -- 배열의 단점
// --- 중간 삽입/삭제가 느리다
// - 정렬된 연결 리스트로는 불가 (임의 접근 X)

vector<int> numbers;

// O(log N)
void BinarySearch(int N)
{
    int left = 0;
    int right = numbers.size() - 1;

    while (left <= right)
    {
        cout << "탐색 범위 : " << left << "-" << right << endl;

        int mid = (left + right) / 2;

        if (N < numbers[mid])
        {
            cout << N << " < " << numbers[mid] << endl;
            right = mid - 1;
        }
        else if (N > numbers[mid])
        {
            cout << N << " > " << numbers[mid] << endl;
            left = mid + 1;
        }
        else
        {
            cout << "찾음" << endl;
            break;
        }
    }
}
#pragma endregion
#pragma region 이진 탐색 트리 (Binary Search Tree)
#include "BinarySearchTree.h"
#pragma endregion
#pragma region 레드 블랙 트리
// Red-Black Tree
// 1) 모든 노트는 Red or Black
// 2) Root는 Black
// 3) Leaf(NIL)는 Black
// 4) Red 노드의 자식은 Black (연속해서 Red-Red X)
// 5) 각 노드로부터 ~ 리프까지 가는 경로들은 모두 같은 수의 Black
#pragma endregion

int main()
{
    //numbers = vector<int>{ 1,8,15,23,32,44,56,63,81,91 };
    //BinarySearch(82);

    // ------------------------------

    BinarySearchTree bst;
    char temp;
    bst.Insert(20);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(10);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(30);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(25);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(26);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(40);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(50);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(35);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(42);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(46);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(43);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);

    bst.Delete(20);
    bst.Print();

    return 0;
}
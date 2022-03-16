#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

// ���� Ž�� Ʈ��
// std::map

#pragma region ���� Ž��(binary search)

// ��Ȳ) �迭�� �����Ͱ� ���ĵǾ� �ִ�
// [1][8][15][23][32][44][56][63][81][91]
// Q) 82��� ���ڰ� �迭�� �ֽ��ϱ�?
// A) ���������� ã���� O(N), ���ĵ��ִٴ� �����Ͽ� ���ٿ� �������� ã���� O(logN)

// - ���ĵ� �迭�� �̿��߱⿡ ���� Ž�� ����
// -- �迭�� ����
// --- �߰� ����/������ ������
// - ���ĵ� ���� ����Ʈ�δ� �Ұ� (���� ���� X)

vector<int> numbers;

// O(log N)
void BinarySearch(int N)
{
    int left = 0;
    int right = numbers.size() - 1;

    while (left <= right)
    {
        cout << "Ž�� ���� : " << left << "-" << right << endl;

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
            cout << "ã��" << endl;
            break;
        }
    }
}
#pragma endregion
#pragma region ���� Ž�� Ʈ�� (Binary Search Tree)
#include "BinarySearchTree.h"
#pragma endregion
#pragma region ���� �� Ʈ��
// Red-Black Tree
// 1) ��� ��Ʈ�� Red or Black
// 2) Root�� Black
// 3) Leaf(NIL)�� Black
// 4) Red ����� �ڽ��� Black (�����ؼ� Red-Red X)
// 5) �� ���κ��� ~ �������� ���� ��ε��� ��� ���� ���� Black
#pragma endregion

int BST_RBT_Test()
{
    //numbers = vector<int>{ 1,8,15,23,32,44,56,63,81,91 };
    //BinarySearch(82);

    // ------------------------------

    BinarySearchTree bst;
    char temp;
    bst.Insert(30);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(10);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(20);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);
    bst.Insert(25);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);

    bst.Delete(20);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);

    bst.Delete(10);
    bst.Print();
    cin.get();//this_thread::sleep_for(1s);

    return 0;
}
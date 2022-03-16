#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

// [����]
// PriorityQueue O(logN)
// Red-Black Tree O(logN)
// Sorting ?

// [3][J][5][K][9]
// [3][J] [5][K][9]
// [3] [J][5] [K][9]
// [3][5] [J][K] [9]
// [3][5][J] [K][9]
// [3][5] [J][9][K]
// [3] [5][J] [9][K]
// [3][5] [J][9] [K] // �������� ���� �Ǿ��� ������ ����
// [3][5][9][J][K] // ��ó�� ���ĿϷ�� �޺κе� �ϳ��� �������� ���鼭 �����
// 1) ���� ���� (Bubble Sort)
void BubbleSort(vector<int>& v)
{
    const int n = (int)v.size();

    // (N-1) + (N -2) + ... + 2 + 1
    // ���������� �� = N * (N - 1) / 2
    // ��������� O(N^2)
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (v[j] > v[j + 1])
            {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// [3][J][5][K][9]
// [3]           [J][5][K][9]
// [3][5]        [J][K][9]
// [3][5][9]     [J][K]
// [3][5][9][J]  [K] // �������� �翬�� ���ĵ������Ƿ� ��
// 2) ���� ���� (Selection Sort)
void SelectionSort(vector<int>& v)
{
    const int n = (int)v.size();

    // (N-1) + (N -2) + ... + 2 + 1
    // ���������� �� = N * (N - 1) / 2
    // ��������� O(N^2)
    // �����ٴ� ���������� ���� ���⵵�� ������
    for (int i = 0; i < n - 1; i++)
    {
        int bestidx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (v[j] < v[bestidx])
            {
                bestidx = j;
            }
        }

        if (i != bestidx)
        {
            int temp = v[bestidx];
            v[bestidx] = v[i];
            v[i] = temp;
        }
    }
}

// [5][J][9][3][K]
// [5]              [J] [9][3][K]
// [5][J]               [9][3][K]
// 
// [5][J]           [9] [3][K]
// [5][J][J]            [3][K]
// [5][9][J]            [3][K]
// 
// [5][9][J]        [3] [K]
// [5][9][J][J]         [K]
// [5][9][9][J]         [K]
// [5][5][9][J]         [K]
// [3][5][9][J]         [K]
// 
// [3][5][9][J][K]
// 3) ���� ���� (Insertion Sort)
void InsertionSort(vector<int>& v)
{
    const int n = (int)v.size();

    // O(N^2)
    for (int i = 1; i < n; i++)
    {
        int insertData = v[i];
        int j;
        for (j = i - 1; i >= 0; j--)
        {
            if (v[j] > insertData)
                v[j + 1] = v[j];
            else
                break;
        }
        v[j + 1] = insertData;
    }

}

int BasicSortTest()
{
    vector<int> v{ 1,5,3,4,2 };
    //std::sort(v.begin(), v.end());
    //BubbleSort(v);
    //SelectionSort(v);
    InsertionSort(v);
    return 0;
}
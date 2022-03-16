#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

// �� ����
void HeapSort(vector<int>& v)
{
    priority_queue<int, vector<int>, greater<int>> pq;

    // priority_queue ����/���� * �����Ͱ��� => O(NlogN)
    for (int num : v)
        pq.push(num);

    v.clear();

    // O(NlogN)
    while (pq.empty() == false)
    {
        v.push_back(pq.top());
        pq.pop();
    }
}

// ���� ���� (�ٹ�鿡�� ���� ���̴� �����̴� �߿�)
// ���� ���� (Divide and Conquer)
// - ���� (Divide)    ������ �� �ܼ��ϰ� ����
// - ���� (Conquer)   ���ҵ� ������ �ذ�
// - ���� (Combine)   ����� �����Ͽ� ������

// [3][K][7][2][J][4][8][9]
// [3][K][7][2] [J][4][8][9]
// [2][3][7][K] [4][8][9][K]
// [2]  [3][7][K] [4][8][9][K]
// [2][3]  [7][K] [4][8][9][K]
// [2][3][4]  [7][K] [8][9][K]
// ...

// [3][K][7][2][J][4][8][9]            8�� * 1
// [3][K][7][2] [J][4][8][9]           4�� * 2
// [3][K] [7][2] [J][4] [8][9]         2�� * 4
// [3] [K] [7] [2] [J] [4] [8] [9]     1�� * 8
// [3][K] [2][7] [4][J] [8][9]         2�� * 4
// [2][3][7][K] [4][8][9][J]           4�� * 2
// [2][3][4][7][8][9][J][K]            8�� * 1

// O(N)
void MergeResult(vector<int>& v, int left, int mid, int right)
{
    // [2][3][7][K] [4][8][9][J]
    // [l]          [r]

    int leftIdx = left;
    int rightIdx = mid + 1;
    vector<int> temp;
    while (leftIdx <= mid && rightIdx <= right)
    {
        if (v[leftIdx] <= v[rightIdx])
        {
            temp.push_back(v[leftIdx]);
            leftIdx++;
            // [2][3][7][K] [4][8][9][J]
            //    [l]       [r]
        }
        else
        {
            temp.push_back(v[rightIdx]);
            rightIdx++;
            // [2][3][7][K] [4][8][9][J]
            // [l]             [r]
        }
    }

    // ������ ���� ��������, ������ ������ ������ ����
    if (leftIdx > mid)
    {
        while (rightIdx <= right)
        {
            temp.push_back(v[rightIdx]);
            rightIdx++;
        }
    }
    else // �������� ���� ��������, ���� ������ ������ ����
    {
        while (leftIdx <= mid)
        {
            temp.push_back(v[leftIdx]);
            leftIdx++;
        }
    }

    for (int i = 0; i < temp.size(); i++)
        v[left + i] = temp[i];
}

// MergeResult(O(N)) * �ݾ� ���� => O(NlogN)
void MergeSort(vector<int>& v, int left, int right)
{
    if (left >= right)
        return;

    int mid = (left + right) / 2;
    MergeSort(v, left, mid);
    MergeSort(v, mid + 1, right);

    MergeResult(v, left, mid, right);
}

int Heap_N_Merge()
{
    vector<int> v;

    srand(time(0));

    for (int i = 0; i < 50; i++)
    {
        int randValue = rand() % 100;
        v.push_back(randValue);
    }

    //HeapSort(v);
    MergeSort(v, 0, v.size() - 1);
    return 0;
}
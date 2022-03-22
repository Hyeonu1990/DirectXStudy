#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

// �� ����
int Partition(vector<int>& v, int left, int right)
{
    int pivot = v[left];
    int low = left + 1;
    int high = right;

    // O(N)
    while (low <= high)
    {
        while (low <= right && pivot >= v[low])
            low++;

        while (high >= left + 1 && pivot <= v[high])
            high--;

        if (low < high)
            swap(v[low], v[high]);
    }

    swap(v[left], v[high]); // low�� high�� �����Ǹ鼭 high�� pivot���� ���� ���� ����Ű������
    return high;
}

// O(N^2)   -> �־��� ���(�̹� ���ĵ� �迭�� �ݾ� ������ Ž���� �ȵ����� N*N)
// O(NlogN) -> ���������
// �������� �������Ŀ� ���� ������ ���� �� ���簡 ��� ������[���� O(NlogN)������]
void QuickSort(vector<int>& v, int left, int right)
{
    if (left > right)
        return;

    int pivot = Partition(v, left, right);
    QuickSort(v, left, pivot - 1);
    QuickSort(v, pivot + 1, right);
}

int QuickSortTest()
{
    vector<int> v;

    srand(time(0));

    for (int i = 0; i < 50; i++)
    {
        int randValue = rand() % 100;
        v.push_back(randValue);
    }

    QuickSort(v, 0, v.size() - 1);

    return 0;
}
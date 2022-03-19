#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

// 퀵 정렬
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

    swap(v[left], v[high]); // low와 high가 교차되면서 high가 pivot보다 낮은 값을 가리키고있음
    return high;
}

// O(N^2)   -> 최악의 경우(이미 정렬된 배열은 반씩 나눠서 탐색이 안됨으로 N*N)
// O(NlogN) -> 평균적으로
// 퀵정렬은 병합정렬에 비해 데이터 생성 및 복사가 없어서 빠르다[같은 O(NlogN)이지만]
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
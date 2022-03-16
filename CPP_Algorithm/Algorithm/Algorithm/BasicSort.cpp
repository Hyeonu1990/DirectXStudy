#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>

// [정렬]
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
// [3][5] [J][9] [K] // 마지막껀 정렬 되었기 때문에 냅둠
// [3][5][9][J][K] // 위처럼 정렬완료된 뒷부분들 하나씩 루프에서 빼면서 종료됨
// 1) 버블 정렬 (Bubble Sort)
void BubbleSort(vector<int>& v)
{
    const int n = (int)v.size();

    // (N-1) + (N -2) + ... + 2 + 1
    // 등차수열의 합 = N * (N - 1) / 2
    // 결론적으로 O(N^2)
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
// [3][5][9][J]  [K] // 마지막은 당연히 정렬되있으므로 끝
// 2) 선택 정렬 (Selection Sort)
void SelectionSort(vector<int>& v)
{
    const int n = (int)v.size();

    // (N-1) + (N -2) + ... + 2 + 1
    // 등차수열의 합 = N * (N - 1) / 2
    // 결론적으로 O(N^2)
    // 버블보다는 좋긴하지만 같은 복잡도를 가진다
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
// 3) 삽입 정렬 (Insertion Sort)
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
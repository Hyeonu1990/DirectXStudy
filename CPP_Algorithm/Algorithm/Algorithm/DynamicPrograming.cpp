#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>
#include <windows.h>
// 동적 계획법 (DP)

// 메모이제이션 (memoization)
// - 속도를 위해 메모리를 소모하는 방법
int cache[50][50]; // 50개를 안넘긴다고 판단하고 정의한 것임
int combination(int n, int r)
{
    // 기저 사례
    if (r == 0 || n == r)
        return 1;

    // 이미 답을 구한 적 있으면 바로 반환
    int& ret = cache[n][r];
    if (ret != -1)
        return ret;

    // 새로 답을 구해서 캐시에 저장
    return ret = combination(n - 1, r - 1) + combination(n - 1, r);
}

int DP_Test()
{
    ::memset(cache, -1, sizeof(cache));

    __int64 start = GetTickCount64();
    int lotto = combination(45, 6);
    __int64 end = GetTickCount64();
    cout << lotto << endl;
    cout << end - start << "ms" << endl; //78ms -> 0ms
    return 0;
}
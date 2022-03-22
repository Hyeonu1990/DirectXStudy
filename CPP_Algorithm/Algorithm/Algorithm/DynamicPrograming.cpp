#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>
#include <windows.h>
// ���� ��ȹ�� (DP)

// �޸������̼� (memoization)
// - �ӵ��� ���� �޸𸮸� �Ҹ��ϴ� ���
int cache[50][50]; // 50���� �ȳѱ�ٰ� �Ǵ��ϰ� ������ ����
int combination(int n, int r)
{
    // ���� ���
    if (r == 0 || n == r)
        return 1;

    // �̹� ���� ���� �� ������ �ٷ� ��ȯ
    int& ret = cache[n][r];
    if (ret != -1)
        return ret;

    // ���� ���� ���ؼ� ĳ�ÿ� ����
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
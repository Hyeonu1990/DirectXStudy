#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>
#include <windows.h>

// ENCHANT

// 무기 강화 주문서 => +1 / +2 / +3 중 하나

// +N 집행검 뜨는 경우의 수는?
// ex) +1 +2 +3 ... +9
// ex) +3 +6 +9
// ex) +1 +3 +4

int enchant_target_num;
int enchant_cache[100];

// [+num]에서 시작해서, [+N]까지 가는 경우의 수
int Enchant(int num)
{
    // 기저 사례
    if (num > enchant_target_num) return 0;
    if (num == enchant_target_num) return 1;

    // 캐시
    int& ret = enchant_cache[num];
    if (ret != -1)
        return ret;

    // 적용
    return ret = Enchant(num + 1) + Enchant(num + 2) + Enchant(num + 3);
}

int Enchant_Test()
{
    enchant_target_num = 1;
    for (; enchant_target_num < 10; enchant_target_num++)
    {
        memset(enchant_cache, -1, sizeof(enchant_cache));

        int ret = Enchant(0);
        cout << "enchant_target_num : " << enchant_target_num << ", ret : " << ret << endl;
    }
    return 0;
}
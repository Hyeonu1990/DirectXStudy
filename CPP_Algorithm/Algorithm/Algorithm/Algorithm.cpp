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
// PriorityQueue 삽입/삭제 O(logN)
// Red-Black Tree 삽입/삭제 O(logN)
// 
// 기본정렬(버블정렬, 선택정렬, 삽입정렬) O(N^2)
// 힙정렬, 병합정렬 O(NLogN)
// 퀵정렬 O(N^2) 최악조건, O(NlogN) 평균
// 퀵정렬은 병합정렬에 비해 데이터 생성 및 복사가 없어서 빠르다[같은 O(NlogN)이지만]
// 
// 해시 테이블

// Q) map vs hash_map (C++ 표준 unordered_map)

// map : Red-Black Tree
// - 추가/탐색/삭제 O(logN)

// C# Dictionary == C++ map (X)
// C# Dictionary == C++ hash_map (O)

// hash_map (unordered_map)
// - 추가/탐색/삭제 O(1)
// - O(1)속도를 내기 위해 메모리를 내주고 속도를 취한다
// 
// - 충돌문제 : 충돌이 발생한 자리를 대신해서 다른 빈자리를 찾아나서면 된다
// -- 선형 조사법 (linear probing) : hash(key) + 1 -> hash(key) + 2 이런식으로 그냥 한칸씩 이동
// -- 이차 조사법 (quadratic probing) : hash(key) + 1^2 -> hash(key) + 2^2 이런식으로 N^2 씩 이동
// -- 기타 여러 조사법 존재
// -- 체이닝 : 해당 키값에 추가로 넣는거. 즉, 2차배열 형식으로 데이터 저장. 키값으로 배열을 찾고 해당 아이디에 맞는 데이터 탐색 후 출력
//
#pragma endregion

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>
#include <windows.h>

// K-RIDER

// - 카트는 게임이 시작하면 달리기 시작하며, 주어진 시간(T)동안 달린다.
// - 카트는 처음에는 기본 속도 (초속 1)로 달린다.
// - 게임이 시작하고 특정 시간(a)가 되면 바닥에 신발 아이템이 생성된다.
// - 카트는 신발을 신거나 지나칠 수 있다. 지나간 신발은 영영 다시 주을 수 없다.
// - 신발를 착용하려면 (b)의 시간이 필요하다. 즉 (b)초 동안 제자리에서 멈추고 나서야 움직일 수 있다.
// - 신발을 착용하면 일정시간(c) 동안 신발 속도(d)로 달릴 수 있다.
// - 신발은 하나만 착용할 수 있고, 가장 최근에 착용한 신발의 속도만 적용된다. 
// - 신발을 벗거나 다른 신발로 바꿔 장착할 때 추가시간이 들지 않는다. (새로운 신발을 신는 시간만 소요 된다)
// - 신발 효과가 끝나면 다시 기본 속도 (초속 1)로 달린다.

// Q) 생성되는 모든 신발 정보가 주어졌을 때, (T)초 동안 갈 수 있는 최대 거리를 구하라.

// input.txt
// 20
// 4
// 3 4 10 3
// 4 1 4 2
// 10 2 5 5
// 15 1 3 7

struct Shoe
{
    Shoe(int a, int b, int c, int d)
    {
        time = a;
        start = a + b;
        end = a + b + c;
        speed = d;
    }

    int time; // a (신발 스폰 시간)
    int start; // a+b (신발 효과 시작 시간)
    int end; //  a+b+C (신발 효과 끝나는 시간)
    int speed; // d (신발 속도)
};

int K_RAIDER_T;
vector<Shoe> shoes;
vector<int> k_raider_cache;

// now번 신발을 신고 갈 수 있는 최대 거리를 반환
int Solve(int now)
{
    // 기저 사례
    if (now >= shoes.size())
        return 0;

    // 캐시
    int& ret = k_raider_cache[now];
    if (ret != -1)
        return ret;

    // 적용
    Shoe& shoe = shoes[now];

    // 신발 신고 이동한 거리 + 걸어서 이동한 거리
    int dist = (shoe.end - shoe.start) * shoe.speed + (K_RAIDER_T - shoe.end) * 1;
    ret = max(ret, dist);

    // 다른 신발도 하나씩 신어본다
    for (int next = now + 1; next < shoes.size(); next++)
    {
        Shoe& nextShoe = shoes[next];
        if (nextShoe.time < shoe.start)
            continue;

        // 다음 신발까지 이동 거리
        int moveDist = 0;

        // 현재 신발 효과가 끝나기 전에 다음 신발이 스폰 됨
        if (nextShoe.time <= shoe.end)
        {
            moveDist = (nextShoe.time - shoe.start) * shoe.speed; // 신발 신고 이동
        }
        else
        {
            moveDist = (shoe.end - shoe.start) * shoe.speed; // 신발 신고 이동
            moveDist += (nextShoe.time - shoe.end) * 1; // 나머지 부분 걸어서 이동
        }

        ret = max(ret, moveDist + Solve(next));
    }

    return ret;
}

int main()
{
    // 총 이동 시간
    K_RAIDER_T = 20;

    // 시간별로 생성되는 신발 등록
    shoes.push_back(Shoe(0, 0, K_RAIDER_T, 1));
    shoes.push_back(Shoe(3, 4, 10, 3));
    shoes.push_back(Shoe(4, 1, 4, 2));
    shoes.push_back(Shoe(10, 2, 5, 5));
    shoes.push_back(Shoe(15, 1, 3, 7));
    std::sort(shoes.begin(), shoes.end(), [=](Shoe& left, Shoe& right) { return left.time < right.time; });

    // 캐시
    k_raider_cache = vector<int>(shoes.size(), -1);

    int ret = Solve(0);

    cout << ret << endl;

    return 0;
}
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



int main()
{

    return 0;
}
#include <iostream>
using namespace std;

char a; // 1byte(-128 ~ 127)
short b; // 2bytes(-32768 ~ 32767)
int c; // 4bytes(-21.4억 ~ 21.4억)
__int64 d; // 8bytes(long long)(범위 많이 큼)

unsigned char ua; // 1byte(0 ~ 255)
unsigned short ub; // 2bytes(0 ~ 65536)
unsigned int uc; // 4bytes(0 ~ 42.9억)
unsigned __int64 ud; // 8bytes(long long)(0 ~ 범위 많이 큼)

bool isboolean; // 1바이트 (최소단위라서 1비트 안됨)

#pragma region 실수(부동소수점)
// 실수(부동소수점)
// float double
// 3.1415926535
// 부동소수점
// .을 유동적으로 움직여서 표현하는 방법
// 3.1415926535
// 1) 정규화 = 0.31415926535 * 10^1
// 2) 31415926535 (유효숫자) 1 (지수)
// float 부호(1) 지수(8) 유효숫자(23) = 32비트 = 4바이트
// double 부호(1) 지수(11) 유효숫자(52) = 64비트 = 8바이트

// ex) -3.375라는 값을 저장
// 1) 2진수 변환 = (3) + (0.375) = 0b11 + 0b0.011 = 0b11.011 // (0.375 = 0.5 * 0 + 0.25 + 1 + 0.125 * 1 = 0b0.011)
// 2) 정규화 0b1.1011 * 2^1
// 1(부호) 1(지수) 1011(유효숫자)
// 단 지수는 unsigned byte라고 가정하고 숫자 + 127 만들어줌
// 예상 결과 : 0b 1 1000'0000 1011000'0000'0000'0000'0000 = 0x c058000

// 프로그래밍할 때 부동소수점은 항상 '근사값'이라는 것을 기억
// 1/3 = 0.33333333333333333333333333~
// 특히 수가 커질 수록 오차 범위도 매우 커짐
// 실수 2개를 == 으로 비교하는 것은 지양
#pragma endregion

#pragma region 문자및문자열
// 문자
// char : 아스키코드
// wchar_t : 유니코드

// ASCII (American Standard Code for Inforamtion Interchange)
// 유니코드
// UTF8
// - 알파벳, 숫자 1바이트(ASCII 동일한 번호)
// - 유럽 지역의 문자는 2바이트
// - 한글, 한자 등 3바이트
// UTF16
// - 알파벳, 숫자, 한글, 한자 등 거의 대부분 문자 2바이트
// - 매~우 예외적인 고대 문자만 4바이트 (사실상 무시해도 됨)

wchar_t wch = 0xc548;// L'안';

// Escape Sequence
// 표기하기 애매한 애들을 표현
// \0 = 아스키코드0 = NULL
// \t = 아스키코드9 = Tab
// \n = 아스키코드10 = LineFeed (한줄 아래로)
// \r = 아스키코드13 = CarriageReturn (커서 <<)

// 문자열
// 끝는 NULL (\0)
char str[] = { 'h','e','l','l','o','\0' };
char str2[] = "Hello World";
wchar_t str3[] = L"Hello World 안녕";
#pragma endregion

// >> 비트 우측 이동 : 생성될 맨 왼쪽 비트는 부호 비트값에 따라 생성됨. 그래서 unsigned로 만들어야 정신건강에 좋음

#pragma region 데이터 영역
// 전역변수 데이터 영역
// .data : 초기값이 있는 경우
int num_a = 2;
// .bss : 초기값이 없는 경우
int num_b;
// .rodata : 읽기 전용 데이터
const int num_c = 5; // 컴파일러 하기 나름이고 const라고 .rodata에 무조건 들어가는건 아님
const int CONST_NUM = 0; // 전역변수에 이런 const int는 컴파일러에서 해당 부분을 0으로 바꿔서 정작 이 변수는 존재하지 않는 경우도 있음
#pragma endregion

#define DEFINE_NUM 1+2 // 보통 이런 상수는 const 같은거 사용
#define DEFINE_TEST cout << "Hello World!\n" << endl;

#pragma region 함수 선언
int base();
void Func2(int, int); // == void Func2(int x, int y);
int Pointer();
#pragma endregion

//[ [main매개변수][RET][main지역변수] [호출된 함수 매개변수][RET][호출된 함수 지역변수] ~ ] // RET : 리턴주소
int main()
{
    Pointer();
    return 0;
}

int base()
{
#pragma region 스택 영역
    // 함수 내 변수는 스택영역에 저장
    // {}(중괄호)과 생존 범위
    {
        int num_C = 5;
    }
    int num_c = 3;
#pragma endregion

#pragma region 전처리관련
    DEFINE_TEST;//이미 컴파일 후 cout << "Hello World!\n" << endl;로 대체되었기 때문에 BreakPoint 걸기가 애매하다
    cout << DEFINE_NUM * 2 << endl; //(1 + 2) * 2가 아니라 1 + 2 * 2 가 계산됨
#pragma endregion

#pragma region 유니코드 문자 출력
    wcout.imbue(locale("kor")); //wchar_t는 wcout 사용
    wcout << str3 << endl;
#pragma endregion

    int a = 1;
    int b = 0;
    b = a++;
    cout << b << endl; // 1
    cout << a << endl; // 2

    return 0;
}

int Random()
{
    srand(time(0));//시드설정
    //rand();//0~32767
    cout << rand() << endl;
    cout << rand() << endl;
    cout << rand() << endl;
    cout << rand() << endl;
    cout << rand() << endl;
    cout << rand() << endl;

    return 0;
}

void Func1()
{
    cout << "Func1" << endl;
    Func2(1, 2); // 상단에 Func2 선언이 없으면 컴파일 에러
}

void Func2(int a, int b)
{
    cout << "Func2" << endl;
}

int Pointer()
{
    int num = 1;
    // 참고) 포인트 사이즈는 4바이트(32비트) or 8바이트(64비트)
    int* ptr = &num;

    int value1 = *ptr;
    *ptr = 2;

    //타입의 불일치
    __int64* ptr2 = (__int64*)&num;

    *ptr2 = 0x0000AABBCCDDEEFF;

    return 0;
}

int Pointer2()
{
    int number = 1;

    int* pointer = &number;

    number += 1; // 당연히 1 증가

    // 포인트 +- 연산은 Type 크기만큼 이동
    pointer += 1; // Type(int) 크기 만큼 4 증가
    
}

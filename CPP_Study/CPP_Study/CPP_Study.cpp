#include <iostream>
using namespace std;

//초기값이 0이거나, 초기값이 없는 변수라면 .bss 영역
//0이 아닌 초기화 값이 있으면 .data영역

char a; // 1byte(-128 ~ 127)
short b; // 2bytes(-32768 ~ 32767)
int c; // 4bytes(-21.4억 ~ 21.4억)
__int64 d; // 8bytes(long long)(범위 많이 큼)

unsigned char ua; // 1byte(0 ~ 255)
unsigned short ub; // 2bytes(0 ~ 65536)
unsigned int uc; // 4bytes(0 ~ 42.9억)
unsigned __int64 ud; // 8bytes(long long)(0 ~ 범위 많이 큼)

bool isboolean; // 1바이트 (최소단위라서 1비트 안됨)


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

int main()
{
    //cout << "Hello World!\n" << endl;
    wcout.imbue(locale("kor")); //wchar_t는 wcout 사용
    wcout << str3 << endl;
}

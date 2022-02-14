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

#pragma region 함수 선언(사용하려는 함수가 작동 중인 함수 아래에 표기되있을 경우 선언용)
int base();
void Func2(int, int); // == void Func2(int x, int y);
int Pointer();
void ArrayAndPointer();
#pragma endregion

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

struct TestStruct
{
    int index = 0;
};

TestStruct SetTestStruct()
{
    TestStruct test;
    test.index = 30;
    return test;
}

int Pointer2()
{
    int number = 1;

    int* pointer = &number;

    number += 1; // 당연히 1 증가

    // 포인트 +- 연산은 Type 크기만큼 이동
    pointer += 1; // Type(int) 크기 만큼 4 증가
    
    TestStruct test_main;
    // [매개변수][RET][지역변수(생략된 TestStruct temp)]   [SetTestStruct 함수 매개변수((생략된 TestStruct &temp))][RET][SetTestStruct 함수 지역변수]
    // 어셈블리에서는 복사가 이뤄지며 이런 복사는 데이터 생성을 하게되어 구조체 및 클래스 크기가 클수록 비효율적
    // SetTestStruct(&test_main) 이런식으로 원본 가져가서 설정하는게 효율적
    test_main = SetTestStruct();

    return 0;
}

//참조 전달
int ReferenceType()
{
    int number = 1;
    int* pointer = &number;
    *pointer = 2;

    // 로우레벨(어셈블리) 관점에서 실제 자동 방식은 int*와 같음, 실제로는 int*지만 문법은 int처럼 사용, C#의 ref
    // 포인터랑 다르게 참조대상이 없으면 안됨, 즉 포인터랑 다르게 nullptr 지정 불가 및 관련 예외처리 불가
    // int* ptr; (O)
    // int& ptr; (X)
    int& reference = number;

    // C++ 관점에서는 number라는 바구니에 또 다른 이름을 부여한 것
    // number라는 바구니에 reference라는 다른 이름이 지어짐
    // reference를 수정하면 number 도 수정됨

    reference = 3;

    //서로 변환 방법, 그냥 int&를 일반타입처럼 사용하면 됨
    int* pointer2 = &reference;
    int& reference2 = *pointer;

    return 0;
}

void PrintInfo(const TestStruct* const info)
{
    // TestStruct* const info
    // info 내용물(주소) 바꿀 수 없음 info = &value;(X)
    // info 내부(info->~)는 수정가능 info->index = 300 (O)

    // const TestStruct* info 또는 TestStruct const * info // 전자가 더 많이 쓰임
    // info 내용물(주소) 바꿀 수 있음 info = &value;(O)
    // info 내부(info->~)는 수정 info->index = 300 (X)
}

void PrintInfo(const TestStruct& info) //참조(&) 형식은 const랑 자주 쓰임
{
    //info.index = 300; (X)
    TestStruct value;
    //info = value; (X)
}

#define OUT

void ChangeInfo(OUT TestStruct& info)
{
    info.index = 30; 
}

void ReferenceTest()
{
    TestStruct Info;
    ChangeInfo(OUT Info); //C#과 다르게 그냥 가독성용 표시
}

void ArrayAndPointer()
{
    //주소만 담음
    const char* test1 = "Hello World"; // char* test1 = "Hello World";는 에러, "Hello World" 타입이 const char* 이므로

    //따로 생성
    char test2[] = "Hello World";
    int length = sizeof(test2) / sizeof(char);
}


void SetMessage(const char** a)
{
    *a = "Bye";
}

void SetMessage(const char*& a)
{
    a = "Wow";
}

void DoublePointer()
{
    const char* msg = "Hello";
    cout << msg << endl;
    SetMessage(&msg);
    cout << msg << endl;
    SetMessage(msg);
    cout << msg << endl;
}

int Array2D()
{
    int arr2[2][2] = { {1, 2}, {3, 4} };

    //int** pp = (int**)arr2;    
    // pp(주소1) -> 주소1(00000001) -> 주소2()Error
    //count << (**pp) << endl;

    // [1][2]
    // [주소]
    int(*p2)[2] = arr2;
    cout << (*p2)[0] << endl;
    cout << (*p2)[1] << endl;
    cout << (*(p2 + 1))[0] << endl;
    cout << (*(p2 + 1))[1] << endl;
    return 0;
}

char* StrCat(char* dest, char* src)
{
    char* ret = dest;
    while (*dest != '\0')
    {
        dest++;
    }

    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
        //위 내용 모두를 한줄로 하면 *dest++ = *src++;
    }

    *dest = '\0';

    return ret;
}

void stringFunc()
{
    const int BUFF_SIZE = 100;
    char str1[BUFF_SIZE] = "Hello";
    char str2[BUFF_SIZE] = "World";
    cout << str1 << endl;
    cout << str2 << endl;
    StrCat(str1, str2);
    cout << str1 << endl;
}

#include <iomanip> 
const int MAX = 100;
int board[MAX][MAX] = {};
int N;

void PrintBoard()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            cout << setfill('0') << setw(2) << board[y][x] << " ";
        }
        cout << endl;
    }
}

enum Direction
{
    EAST,
    SOUTH,
    WEST,
    NORTH
};

bool CanGo(const int& x, const int& y)
{
    return !(x >= N || y >= N || x < 0 || y < 0 || board[y][x] != 0);
}

void SetBoard()
{
    int index = 1;
    int x = 0;
    int y = 0;
    int dir = EAST;
    int dy[] = { 0, 1, 0, -1 };
    int dx[] = { 1, 0, -1, 0 };
    while (1)
    {
        board[y][x] = index;

        dir = dir % (NORTH + 1);

        index++;
        if (index > N * N)
            break;

        int next_x = x + dx[dir];
        int next_y = y + dy[dir];
        //아래 switch문을 dy, dx 배열을 사용하여 간단하게 표현함
        /*switch (dir)
        {
        case EAST:
            next_x++;
            break;
        case SOUTH:
            next_y++;
            break;
        case WEST:
            next_x--;
            break;
        case NORTH:
            next_y--;
            break;
        }*/
        if (CanGo(next_x, next_y))
        {
            x = next_x;
            y = next_y;
        }
        else
        {
            dir++;
            index--;
            continue;
        }
    }
}

class Player
{
public:
    Player() { _hp = 100; }
    //명시적 변환만 허용
    explicit Player(int hp) { _hp = hp; }
    //멤버함수
    void Move(int x, int y);

    virtual void VMove(int x, int y) { }; // 가상함수 추가하고 메모리 까보면 아래 멤버변수 외에 vftablec 주소값 데이터가 추가된걸 알 수 있음
    /// 가상 함수 테이블(vftable) virtual function table
    /// 생성자 호출 시 추가(설정)됨
    /// .vftable [] 4바이트(32) 8바이트(64)
    /// [VMove] [VDie]
    
    virtual void VDie() = 0; // 순수 가상 함수, Modern C++에선 abstract void VDie(); 로 표현 가능
    /// 순수 가상 함수 : 구현은 없고 인터페이스만 전달하는 용도로 사용하고 싶을 경우
    /// 추상 클래스 : 순수 가상 함수가 1개 이상 포함되면 바로 추상 클래스로 간주
    /// - 직접적으로 객체를 만들 수 없게 됨

    void Attack();
public:
    //멤버변수
    int _hp;
    bool _opponent; // 4바이트(x86기준) 차지하게됨
    int _attack;
    int _posX;
    int _posY;
};

class Knight : public Player
{
public:
    Knight() : Player(100) // 이런식으로 특정 생성자 선언해주지 않으면 Player() 기본 호출
    /*
    * 선처리 영역
    * 자식 생성자 호출 전 부모 생성자 호출
    */
                            , _mana(100), _hpRef(_hp), _hpConst(100)
    {
        _stamina = 100;
    }

    Knight(int stamina) : Player(150), _mana(100), _hpRef(_hp), _hpConst(100) // 초기화 리스트
        /* 초기화 리스트
        *  - 일단 상속관계에서 원하는 부모 생성자 호출할때 필요하다
        *  - 생성자 내에서 초기화 vs 초기화 리스트
        *  -- 일반 변수는 큰 차이 없음
        *  -- 멤버변수 타입이 클래스라면 차이가 남
        *     (생성자 타입을 선택 할 수 있기 때문 -> 생성자 내에서 따로 초기화하면 또 클래스를 생성해서 할당하므로 결국 클래스 2번 생성)
        *  -- 정의함과 동시에 초기화가 필요한 경우(참조 타입, const 타입)
        */
                          
    {
        _stamina = stamina;
        //_hpConst = 100; // 에러, 여기선 지정 불가
    }

    ~Knight()
    {

    }
    /*
    * 후처리 영역
    * 자식 소멸자 호출 후 부모 소멸자 호출
    */

    void Move(int x, int y)
    {
        Player::Move(x, y); //c#에선 base.Move(x, y);
    }

    virtual void VDie()
    {

    }

    void operator=(const int& _value)
    {
        _stamina = _value;
    }
    void operator=(const Knight& _value)
    {
        _stamina = _value._stamina;
    }
    /*
    * 전위형 (++a) operator++()
    * 후위형 (a++) operator++(int)
    */
    Knight& operator++()
    {
        _stamina++;
        return *this;
    }
    Knight& operator++(int)
    {
        _stamina++;
        return *this;
    }
public:
    int _stamina;
    int _mana;

    int& _hpRef;
    const int _hpConst;
};

//void operator=(const Knight& _knight, const int& _value); // = 는 전역으로 선언 불가

//[ [main매개변수][RET][main지역변수] [호출된 함수 매개변수][RET][호출된 함수 지역변수] ~ ] // RET : 리턴주소
int main1()
{
    /*cin >> N;
    SetBoard();
    PrintBoard();*/

    Knight k1;
    Knight k2(k1);
    Knight k3 = k1; // 위 k2처럼 복사 생성사 호출
    Knight k4; // 이건 그냥 기본 생성자 호출
    k4 = k1; // 이건 그냥 복사

    Knight k5;
    //k5 = 1; // 연산자가 없으면 원래 에러이나 컴파일러의 암시적 변환으로 int값 받는 생성자가 있어서 k5 = Knight(1) 이라는 의미가 됨, 좋은 방식은 아님
    //다행이 int값 받는 생성자 앞에 explicit를 붙혀서 이런 방식으로 못쓰게 하는거 가능
    //k5 = Knight(5); // 이건 가능

    Knight k6 = 3; // k6 = Knight(3) 과 같은 의미, 연산자 함수 작동되는거 아님
    k6 = 3; // 연산자 함수 작동

    cout << sizeof(k1) << endl; // 클래스 멤버변수만 크기에 영향을 줌

#pragma region 함수 내 static
    // 생명주기 : 프로그램 시작/종료 (메모리에 항상 올라가 있음)
    // 가시범위 : 함수 내부

    // 정적 지역 격체
    static int s_id = 1;
#pragma endregion

    return 0;
}

class Man
{
public:
    int _hp = 10;
};
class Dog
{
public:
    Dog() {}

    //타입 변환 생성자
    Dog(const Man& man)
    {
        _age = man._hp;
    }

    // 타입 변환 연산자
    operator Man()
    {
        return (Man)(*this);
    }

public:
    int _age = 1;
    int _cutness = 2;
};

class BullDog : public Dog
{
public:
    bool _french;
};


// 동적할당과 연간된 함수/연산자 : malloc / free, new / delete, new[] / delete[]
// malloc/free vs new/delete
// - 사용 편의성 -> new/delete
// - 타입에 상관없이 특정한 크기의 메모리 영역을 할당받으려면 -> malloc/free
// 이 둘의 가장 큰 차이
// 생성타입이 클래스일 경우 new/delete는 생성자/소멸자를 호출해준다.

int main2()
{
    // 유저 영역 [메모장] [LOL] [곰플레이어]
    // ------------------------------------------
    // 커널 영역 (운영체제 핵심 코드)

    // 유저 영역) 운영체제에서 제공하는 API 호출
    // 커널 영역) 메모리 할당해서 건내줌
    // 유저 영역) 받아서 잘 이용함

    // C++에서는 기본적으로 CRT(C 런타임 라이브러리)의 [힙 관리자]를 통해 힙 영역 사용
    // 단, 정말 원한다면 우리가 직접 API를 통해 힙을 생성하고 관리할 수도 있음( MMORPG 서버 메모리 풀링)

    // malloc
    // - 할당할 메모리 크기를 건내준다
    // - 메모리 할당 후 ㅣ작 주소를 가리키는 포인터를 반환 (메모리 부족 시 NULL 리턴)

    // free
    // - malloc (혹은 기타 calloc, realloc 등의 사촌)을 통해 할당된 영역을 해제
    // - 힙 관리자가 할당/미할당 여부를 구분해서 관리

    // void* 란
    // - *가 있으니 포인터 => OK
    // - 타고 가면 void 아무것도 없다? => NO
    // - 타고 가면 void 뭐가 있는지 모르니 너가 적당히 변환해서 사용해라 => OK
    // - void* 앞 메모리 주소에 해당 주소 크기 등 정보를 가지고 있어서 free 시 따로 크기를 입력 안해도 됬던것

    void* pointer = malloc(sizeof(Knight));
    // Heap Overflow
    // - 유효한 힙 범위를 초과해서 사용하는 문제

    Knight* k1 = (Knight*)pointer;
    k1->_hp = 123;
    k1->_posX = 1;
    k1->_posY = 2;


    free(pointer); // 이걸 한번 더 하면 Double Free, 메모리 크기를 참조하던 부분에 쓰레기값이 들어가서 오류남
    pointer = nullptr; // 아래 User-After-Free 방지
    k1 = nullptr; // 아래 User-After-Free 방지

    // User-After-Free
    //k1->_hp = 123;
    //k1->_posX = 1;
    //k1->_posY = 2;

    // new / delete
    // - C++에서 추가됨
    // - malloc/free는 함수, new/delete는 연산자(operator)

    // new[] / delete[]
    // - new가 malloc에 비해 좋긴 한데 배열과 같이 N개 데이터를 같이 할당하기위해

    Knight* k2 = new Knight;
    delete k2; // new로 생성했으면 무조건 delete(free X)

    Knight* k3 = new Knight[5];
    Knight* k3_1 = (k3 + 1);
    delete[] k3; // new[]로 생성했으면 무조건 delete[]

    // --------------- 타입 벼환 유형 (비트열 재구성 여부) -------------------

    // [1] 값 타입 변환
    // 특징) 의미를 유지하기 위해서, 원본 객체와 다른 비트열 재구성
    {
        int a = 123456789; // 2의 보수
        float b = (float)a; // 부동소수점(지수 + 유효숫자)
        cout << b << endl;
        // a의 값을 b 포맷에 맞게 복사 및 변환
    }

    // [2] 참조 타입 변환
    // 특징) 비트열을 재구성하지 않고, '관점'만 바꾸는 것
    // 거의 쓸일은 없지만, 포인터 타입 변환도 '참조 타입 변환' 동일한 룰을 따름
    {
        int a = 123456789; // 2의 보수
        float b = (float&)a; // 부동소수점(지수 + 유효숫자)
        cout << b << endl;
        // 위랑 다르게 그냥 메모리값 통으로 복사, 값을 복사하여 변환하는게 아님
    }

    // --------------- 안전도 분류 -------------------

    // [1] 안전한 변환
    // 특징) 의미가 항상 100% 완전히 일치하는 경우
    // 같은 타입이면서 크기만 더 큰 바구니로 이동
    // 작은 바구니 > 큰 바구니로 이동 OK (업캐스팅)
    // ex) char->short, short->int, int->__int64
    {
        int a = 123456789;
        __int64 b = a;
        cout << b << endl;
    }

    // [2] 불안전한 변환
    // 특징) 의미가 항상 100% 일치한다고 보장하지 못하는 경우
    // 타입이 다르거나
    // 같은 타입이지만 큰 바구니 -> 작은 바구니 이동 (다운캐스팅)
    // 데이터 손실 발생
    {
        int a = 123456789;
        float b = a;
        short c = a;
        cout << b << endl;
        cout << c << endl;
    }

    // ---------------- 프로그래머 의도에 따라 분류 ----------------------

    // [1] 암시적 변환
    // 특징) 이미 알려진 타입 변환 규칙에 따라서 컴파일러가 '자동'으로 타입 변환
    {
        int a = 123456789;
        float b = a; // 암시적으로, 컴파일러 단계에 따라서 오류로 뜰수도 있음
        cout << b << endl;
    }

    // [2] 명시적 변환
    {
        int a = 123456789;
        int* b = (int*)a; // 명시해주면 통과는 됨
        cout << b << endl;
    }

    // -------------------- 아무런 연관 관계가 없는 클래스 사이의 변환 ---------------------

    // [1] 연관없는 클래스 사이의 '값 타입' 변환
    // 특징) 일반적으로 안됨 (예외 : 타입 변환 생성자, 타입 변환 연산자)
    {
        Man man;
        Dog dog = (Dog)man; // 따로 타입 변환 생성자 만들어서 가능하도록함

        Man man2 = dog; // 따로 타입 변환 연산자 만들어서 가능하도록 함
    }

    // [2] 연관없는 클래스 사이의 '참조 타입' 변환
    // 특징) 명시적으로는 OK
    {
        Man man;
        // 어셈블리에선 포인터 = 참조
        Dog& dog = (Dog&)man;
        dog._cutness = 12;
    }

    // ----------- 상속 관계에 있는 클래스 사이 변환 --------------

    // [1] 상속 관계 클래스의 값 타입 변환

    {
        //Dog dog;
        //BullDog bulldog = (BullDog)dog; // 에러

        BullDog bulldog;
        Dog dog = bulldog; // _french 변수만 잘린 데이터 들어감

    }

    // [2] 상속 관계 클래스의 참조 타입 변환
    // 특징) 자식->부모 OK / 부모->자식 암시적X 명시적O
    {
        //Dog dog;
        //BullDog& bulldog = (BullDog&)dog; //타입 명시해주면 가능

        BullDog bulldog;
        Dog& dog = bulldog; //따로 타입 지정 안해줘도 가능
    }

    // 결론)
    // [값 타입 변환] : 진짜 비트열도 바꾸고~ 논리적으로 말이 되게 바꾸는 변환
    // - 논리적으로 말이 된다? (ex. BullDog -> Dog) O
    // - 논리적으로 말이 안된다 (ex. Dog -> BUllDog, Dog -> Man)
    // [참조 타입 변환] : 비트열은 냅두고 메모리 내용 통 복사 변환
    // -- 안전하다 (ex. BullDog -> Dog&) 암시적으로 O
    // -- 위험하다 (ex. Dog -> BullDog&)
    // --- 메모리 침범 위협이 있는 경우 암시적으로 빌드해주지 않음
    // --- 명시적으로 하겠다고 하면 일단 빌드는 됨

    // 명시적으로 처리하는 것들 모두 그냥 빌드만 안날뿐 제대로 연관성 없으면 오류 뿝는게 다반사. 그냥 대충 넘어가고 자주쓰이는 내용만 확인하면 될듯

    return 0;
}

class Item
{
public:
    Item()
    {
        cout << "Item()" << endl;
    }

    Item(int itemType) : _itemType(itemType)
    {
        cout << "Item(int itemType)" << endl;
    }

    Item(const Item& item)
    {
        cout << "Item(const Item&)" << endl;
    }

    virtual ~Item() // 이렇게 해야 Item 클래스로 명시된 자식 클래스도 Item 소멸자가 아닌 자식 자신의 소멸자도 호출
    {
        cout << "~Item()" << endl;
    }

    virtual void Test()
    {
        cout << "Test Item" << endl;
    }

public:
    int _itemType = 0;
    int _itemDbId = 0;
    int _rarity = 0;
    int _ownerID = 0;

    char _dummy[4096] = {};
};

enum ItemType
{
    IT_WEAPON = 1,
    IT_ARMOR = 2,
};
class Weapon : public Item
{
public:
    Weapon() : Item(IT_WEAPON)
    {
        _itemType = IT_WEAPON;
        cout << "Weapon()" << endl;
        _damage = rand() % 100;
    }

    ~Weapon()
    {
        cout << "~Weapon()" << endl;
    }

    virtual void Test()
    {
        cout << "Test Weapon" << endl;
    }

public:
    int _damage = 0;
};

class Armor : public Item
{
public:
    Armor() : Item(IT_ARMOR)
    {
        cout << "Armor()" << endl;
        _defence = rand() % 100;
    }

    ~Armor()
    {
        cout << "~Armor()" << endl;
    }

public:
    int _defence;
};

void TestItem(Item item)
{

}

void TestItemPtr(Item* item)
{
    item->Test();
}

class Character
{
public:

public:
    int _hp = 0;
};

int main3()
{
    //복습
    {
        // Stack [ type(4) dbid(4) dummy(4096) ] 
        Item item;

        // Stack [ 주소(4~8) ] -> Heap [ type(4) dbid(4) dummy(4096) ]
        Item* item2 = new Item();

        // 내부에 복사가 일어나 복사 생성자 및 소멸자 호출, 메모리 낭비
        TestItem(item);
        TestItem(*item2);

        TestItemPtr(&item);
        TestItemPtr(item2);

        // 메모리 누수(Memory Leak) -> 점점 가용 메모리가 줄어들어서 Crash
        delete item2; // 이걸 안하면 영역 나가도 사라지지 않음, item은 사라짐
    }

    //배열
    {
        cout << "----------------------------------" << endl;
        // 진짜 아이템이 100개 있는 것 (스택 메모리에 올라와 있는)
        Item item3[100] = {}; // Item 생성자 100번 호출

        cout << "----------------------------------" << endl;
        // 아이템을 가리키는 바구니가 100개, 실제 아이템은 1개도 없을 수도 있음
        Item* item4[100] = {}; // Item 생성자 호출 X

        for (int i = 0; i < 100; i++)
        {
            item4[i] = new Item();
        }

        cout << "----------------------------------" << endl;

        for (int i = 0; i < 100; i++)
        {
            delete item4[i];
        }

        cout << "----------------------------------" << endl;
    }


    return 0;
}

int main4()
{
    // 연관성이 없는 클래스 사이의 포인터 변환 테스트
    {
        // Stack [ 주소 ] -> Heap [ _hp(4) ]
        Character* character = new Character();

        // 암시적으로는 X
        // 명시적으로는 O
        // Stack [ 주소 ]
        //Item* item = (Item*)character;
        //item->_itemType = 2;
        //item->_itemDbId = 1;
    }

    // 부모 -> 자식 변환 테스트
    {
        Item* item = new Item();
        // [ [ item ] ]
        // [ _damage  ]
        //Weapon* weapon = (Weapon*)item;
        //weapon->_damage = 10; //Crash

        delete item;
    }

    // 자식 -> 부모 변환 테스트
    {
        // [ [ item ] ]
        // [ _damage  ]
        Weapon* weapon = new Weapon();
        // [ [ item ] ]
        Item* item = weapon; // 암시적으로도 된다

        TestItemPtr(item); // Test함수가 가상함수가 아닐 경우 : Item의 Test함수 호출, 가상함수 일 경우 : Weapon의 Test함수 호출

        delete weapon;
    }

    // 명시적으로 타입 변환할때는 항상 조심해야한다.
    // 암시적으로 될 때는 안전하다?
    // -> 평생 명시적으로 타입 변환(캐스팅)은 안하면 되는거 아닌가?

    Item* inventory[20] = {};

    srand((unsigned int)time(nullptr));
    for (int i = 0; i < 20; i++)
    {
        int randValue = rand() % 2;
        if (randValue == 0)
        {
            inventory[i] = new Weapon();
        }
        else
        {
            inventory[i] = new Armor();
        }
    }

    for (int i = 0; i < 20; i++)
    {
        Item* item = inventory[i];
        if (item == nullptr)
            continue;

        if (item->_itemType == IT_WEAPON)
        {
            Weapon* weapon = (Weapon*)item;
            cout << "Weapon Damage : " << weapon->_damage << endl;
        }
        else if (item->_itemType == IT_ARMOR)
        {
            Armor* armor = (Armor*)item;
            cout << "Armor Defence : " << armor->_defence << endl;
        }
    }

    // ************************ 매우 매우 매우 중요 **************************

    for (int i = 0; i < 20; i++)
    {
        Item* item = inventory[i];
        if (item == nullptr)
            continue;

        //delete item; // 깔끔하게 못지우게됨

        if (item->_itemType == IT_WEAPON)
        {
            Weapon* weapon = (Weapon*)item;
            delete weapon;
        }
        else if (item->_itemType == IT_ARMOR)
        {
            Armor* armor = (Armor*)item;
            delete armor;
        }
    }

    // [결론]
    // - 포인터 vs 일반 타입 : 차이를 이해하자 ([ Item item; ] vs [ Item* item = new Item(); ])
    // - 포인터 사이의 타입 변환(캐스팅)을 할 때는 조심해야 한다.
    // - 부모-자식 관계에서 부모 클래스의 소멸자에는 까먹지 말고 virtual을 붙이자

    return 0;
}

class Pet
{
public:
    Pet()
    {
        cout << "Pet()" << endl;
    }
    virtual ~Pet()
    {
        cout << "~Pet()" << endl;
    }
    Pet(const Pet& pet)
    {
        cout << "Pet(const Pet&)" << endl;
    }

    Pet& operator=(const Pet& pet)
    {
        cout << "operator=(const Pet&)" << endl;
        return *this;
    }
};

class Player2
{
public:
    Player2()
    {
        cout << "Player2()" << endl;
    }

    // 복사 생성자
    Player2(const Player2& player)
    {
        cout << "Player2(const Player2&)" << endl;
    }

    Player2& operator=(const Player2& player)
    {
        cout << "operator=(const Player2&)" << endl;
        _level = player._level;
        return *this;
    }

public:
    int _level = 0;
};

class Knight2 : public Player2
{
public:
    Knight2()
    {
        //_pet = new Pet();
    }

    Knight2(const Knight2& knight) : Player2(knight), _pet2(knight._pet2) // 명시해주지 않으면 부모 및 멤버 클래스 모두 기본 생성자 호출
    {
        cout << "Knight2(const Knight2&)" << endl;
        _hp = knight._hp;
        //if (_pet != nullptr)
        //    delete _pet;
        //_pet = new Pet(*knight._pet);
    }

    //~Knight2()
    //{
    //    delete _pet;
    //}

    Knight2& operator=(const Knight2& knight)
    {
        cout << "operator=(const Knight2&)" << endl;

        // 명시해줘야 호출됨
        {
            Player2::operator=(knight);
            _pet2 = knight._pet2;
        }

        _hp = knight._hp;
        //if (_pet != nullptr)
        //    delete _pet;
        //_pet = new Pet(*knight._pet);

        return *this;
    }

public:
    int _hp = 100;
    //Pet* _pet;
    Pet _pet2;
};

int main5()
{
    // 얕은 복사 vs 깊은 복사

    Knight2 knight;
    knight._hp = 200;
    knight._level = 99;

    cout << "--------------- 복사 생성자 --------------" << endl;
    Knight2 knight2 = knight; // ==  Knight2 knight2(knight); // 복사 생성자

    cout << "--------------- 복사 대입 연산자 -----------------" << endl;
    Knight2 knight3; // 기본 생성자
    knight3 = knight; // 복사 대입 연산자

    // [복사 생성자] + [복사 대입 연산자]
    // 둘 다 안 만들어주면 컴파일러가 '암시적으로' 만들어줌

    // 중간 결론) 컴파일러가 알아서 잘 만들어준다. 하지만 직접 만들어야할 상황이 생긴다.(클래스 내에 포인터 변수를 가질 경우)

    // [얕은 복사 Shallow Copy]
    // 멤버 데이터를 비트열 단위로 '똑같이' 복사 (메모리 영역 값 그대로 복사)
    // 포인터는 주소값 바구니 -> 줏값을 똑같이 복사 -> 동일한 객체를 가리키는 상태가 됨
    // Stack : Knight1 [ hp, 0x1000 ] -> Heap 0x1000 Pet[ ]
    // Stack : Knight2 [ hp, 0x1000 ]
    // Stack : Knight3 [ hp, 0x1000 ]
    
    // [깊은 복사 Shallow Copy]
    // 멤버 데이터가 참조(주소) 값이라면, 데이터를 새로 만들어준다 (원본 객체가 참조하는 대상까지 새로 만들어서 복사)
    // Stack : Knight1 [ hp, 0x1000 ] -> Heap 0x1000 Pet[ ]
    // Stack : Knight2 [ hp, 0x2000 ] -> Heap 0x2000 Pet[ ]
    // Stack : Knight3 [ hp, 0x3000 ] -> Heap 0x3000 Pet[ ]

    // 실험)
    // - 암시적 복사 생성자 Steps
    // 1) 부모 클래스의 복사 생성자 호출
    // 2) 멤버 클래스(클래스 내 기본 타입 클래스 변수)의 복사 생성자 호출
    // 3) 멤버가 기본 타입일 경우 메모리 복사 (얕은 복사 Shallow Copy)
    // - 명시적 복사 생성자 Steps (1089번 줄 참조)
    // 1) 부모 클래스의 기본 생성자 호출
    // 2) 멤버 클래스의 기본 생성자 호출

    // - 암시적 복사 대입 연산자 Steps
    // 1) 부모 클래스의 복사 대입 연산자 호출
    // 2) 멤버 클래스(클래스 내 기본 타입 클래스 변수)의 복사 대입 연산자 호출
    // 3) 멤버가 기본 타입일 경우 메모리 복사 (얕은 복사 Shallow Copy)
    // - 명시적 복사 대입 연산자 Steps
    // 1) 알아서 해주는거 없음

    // 왜 이렇게 혼란스러울까?
    // 객체를 '복사' 한다는 것은 두 객체의 값들을 일치시키려는 것
    // 따라서 기본적으로 얕은 복사 (Shallow Copy) 방식으로 동작

    // 결론) 명시적 복사 -> [모든 책임]을 프로그래머한테 위임하겠다는 의미

    return 0;
}
#pragma region Casting
// 캐스팅 (타입 변환) (강의명 : 캐스팅 4총사)
// (int)30.0 -> C언어 캐스팅 방식, 지양합시다

// 1) static_cast - 80~90%
// 2) dynamic_cast - 10%
// 3) const_cast - 잘 안쓰임
// 4) reinterpret_cast - 잘 안쓰임

class Player3
{
public:
    virtual ~Player3()
    {

    }
};

class Knight3 : public Player3
{
public:

};

class Archer : public Player3
{
public:

};

void PrintName(char* str)
{
    cout << str << endl;
}

int main6()
{
    // [static_cast : 타입 원칙에 비춰볼 때 상식적인 캐스팅만 허용해준다]
    // 1) int <-> float
    // 2) Player* -> Knight* (다운캐스팅) << 단, 안전성 보장 못함

    int hp = 100;
    int maxHp = 200;
    float ratio = static_cast<float>(hp) / maxHp; // (float)hp / maxHp;

    Player3* p = new Archer();
    Knight3* k1 = static_cast<Knight3*>(p); // (Knight*)p;

    // [dynamic_cast : 상속 관계에서의 안전 형변환]
    // RTTI (RunTime Type Information) - 다형성을 활용하는 방식 (virtual)
    // - virtual 함수를 하나라도 만들면, 객체의 메모리에 가상 함수 테이블 (vftable) 주소가 기입된다
    // - 만약 잘못된 타입으로 캐스팅을 했으면, nullptr 반환 ******
    // 이를 이용해서 맞는 타입으로 캐스팅을 했는지 확인이 유용하다.

    Knight3* k2 = dynamic_cast<Knight3*>(p); // RTTI 적용이 안되있으면 빌드 에러, 그리고 p가 Knight3 타입이 아닐 경우 nullptr 반환 ******

    // [const_cast : const를 붙이거나 때거나]
    // 현업에서 잘 안쓰임

    PrintName(const_cast<char*>("Hello")); // "Hello"는 const char* 타입이므로 그냥 넣으면 에러

    // [reinterpret_cast]
    // 가장 위험하고 강력한 형태의 캐스팅
    // 're-interpret' : 다시 간주하다/생각하다
    // - 포인터랑 전혀 관계없는 다른 타입 변환 등

    __int64 address = reinterpret_cast<__int64>(k2); // (__int64)k2;
    Dog* dog = reinterpret_cast<Dog*>(k2); //static_cast는 에러
    
    void* _ptr = malloc(1000);
    Dog* dog2 = reinterpret_cast<Dog*>(_ptr); // (Dog*)p;

    return 0;
}
#pragma endregion

#include "Game.h"
int TextRPG()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Game game;
    game.Init();

    while (true)
    {
        game.Update();
    }

    return 0;
}

#pragma region 함수포인터
// [ 함수 포인터 ]

int Add(int a, int b)
{
    return a + b;
}

int Sub(int a, int b)
{
    return a - b;
}

typedef bool(ITEM_SELECTOR)(Item* item, int);

//Item* FindItem(Item items[], int itemCount, bool(*selector)(Item* item))
Item* FindItem(Item items[], int itemCount, ITEM_SELECTOR* selector, int _value)
{
    for (int i = 0; i < itemCount; i++)
    {
        Item* item = &items[i];
        if (selector(item, _value))
            return item;
    }
    return nullptr;
}

bool CheckSomeType(Item* item, int _value)
{
    if (item == nullptr)
        return false;

    return item->_itemType == _value;
}

bool IsOwnerItem(Item* item, int ownerId)
{
    if (item == nullptr)
        return false;

    return item->_itemDbId == ownerId;
}

class TestClass
{
public:
    static int StaticTest(int, int)
    {
        return 0;
    }

    int Test(int, int)
    {
        return 0;
    }
};

int main7()
{
    int a = 10;

    //변수
    typedef int DATA;

    // 1) 포인터       *
    // 2) 변수 이름    pointer
    // 3) 데이터 타입  int
    DATA* pointer = &a;

    //함수
    // typedef int *FUNC_TYPE(int a, int b); -> typedef int(FUNC_TYPE)(int a, int b);  -------- int* FUNC_TYPE이랑 int *FUNC_TYPE이랑 햇갈리까 나온 표현? 인듯
    typedef int(*FUNC_TYPE)(int a, int b); // using = FUNC_TYPE = int(int a, int b); <- Mordern C++ 타입

    // 1) 포인터       *
    // 2) 변수 이름    fn
    // 3) 데이터 타입  함수 (인자는 (int, int), 반환은 int)
    FUNC_TYPE fn; // == int (*fn)(int, int);

    // 함수의 이름은 함수의 시작 주소
    int result = Add(1, 2);
    cout << result << endl;

    // 함수 포인터
    fn = Add; // <-> Sub
    fn = &Add; // 위처럼 & 생략가능

    result = fn(2, 3); // 기본 문법
    cout << result << endl;

    result = (*fn)(2, 3); // 위랑 같은 의미, 함수 포인터는 *(접근 연산자) 붙어도 함수 주소!
    cout << result << endl;

    //예제
    Item items[10] = {};
    items[3]._itemType = 2;
    Item* selectedItem = FindItem(items, 10, CheckSomeType, 2);



    fn = TestClass::StaticTest; // 일반 함수포인트는 클래스는 static 함수만 받을 수 있다.
    //fn = TestClass::Test; // 에러

    typedef int(TestClass::*MEMBER_FUNC_TYPE)(int, int);

    MEMBER_FUNC_TYPE mfn;
    //mfn = TestClass::StaticTest; // 에러
    mfn = &TestClass::Test; // &없으면 빌드에러

    //mfn(1, 2); // 에러
    TestClass testClass;
    (testClass.*mfn)(1, 1);
    TestClass* tcPtr = new TestClass();
    (tcPtr->*mfn)(1, 1);

    return 0;
}
#pragma endregion
#pragma region 함수 객체 (Functor)
// 함수 객체 (Functor) : 함수처럼 동작하는 객체

void HelloWorld()
{
    cout << "Hello World" << endl;
}

void HelloNumber(int number)
{
    cout << "Hello Number " << number << endl;
}

class Functor
{
public:
    void operator()()
    {
        cout << "Functor Test" << endl;
        cout << _value << endl;
    }

    bool operator()(int num)
    {
        cout << "Functor Test" << endl;
        _value += num;
        cout << _value << endl;

        return true;
    }

private:
    int _value = 0;
};

class MoveTask
{
public:
    void operator()()
    {
        cout << "해당 좌표로 플레이어 이동" << endl;
    }

public:
    int _playerId;
    int _posX;
    int _posY;
};

int main8()
{
    //함수 포인터 선언
    void(*pfunc)(void);

    // 동작을 넘겨줄 때 유용하다
    pfunc = &HelloWorld;
    (*pfunc)();

    //함수 포인터 단점
    // 1) 시그니처가 안 맞으면 사용 할 수 없다. -> pfunc = &HelloNumber; // 에러
    // 2) 상태(데이터)를 가질 수 없다

    // [함수처럼 동작]하는 객체
    // () 연산자 오버로딩
    Functor functor;
    functor();
    bool ret = functor(3);

    // MMO에서 함수 객체를 사용하는 예시
    // 클라 <-> 서버
    // 서버 : 클라가 보내준 네트워크 패킷을 받아서 처리
    // ex) 클라 : 나 (5, 0) 좌표로 이동시켜줘!
    MoveTask task;
    task._playerId = 100;
    task._posX = 5;
    task._posY = 0;
    // 나중에 여유 될 때 실행
    task();
    // 이런걸 커맨트 패턴 이라고 불림

    return 0;
}
#pragma endregion
#pragma region Template
// [템플릿]

class TKnight
{
public:
    //...
public:
    int _hp = 100;
};

template<typename T> // == template<class T>
void Print(T a)
{
    cout << a << endl;
}

// 템플릿 특수화
template<>
void Print(TKnight a)
{
    cout << "Knight" << endl;
    cout << a._hp << endl;
}

template<typename T1, typename T2> // == template<class T>
void Print(T1 a, T2 b)
{
    cout << a << " " << b << endl;
}

template<typename T>
T Add(T a, T b)
{
    return a + b;
}

// 연산자 오버로딩 (전역함수 버전)
ostream& operator<<(ostream& os, const TKnight& k)
{
    os << k._hp;
    return os;
}

template <typename T, int SIZE = 10>
class RandomBox
{
public:
    T GetRandomData()
    {
        int idx = rand() % SIZE;
        return _data[idx];
    }
public:
    T _data[SIZE];
};

// 템플릿 특수화
template <int SIZE>
class RandomBox<double, SIZE>
{
public:
    double GetRandomData()
    {
        cout << "RandomBox double" << endl;
        int idx = rand() % SIZE;
        return _data[idx];
    }
public:
    double _data[SIZE];
};

int main9()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    // 템플릿 : 함수나 클래스를 찍어내는 틀
    // 1) 함수 템플릿

    Print<int>(50);
    Print(50.0f);
    Print(50.0);
    Print("Hello Template World");
    Print(5, "Text");

    TKnight k1;
    Print(k1); // 빌드에러를 피하려면 연산자 오버로딩 추가 혹은 템플릿 특수화 필요

    cout << "--------------------------------" << endl;
    // 2) 클래스 템플릿

    RandomBox<int> rb1;
    for (int i = 0; i < 10; i++)
    {
        rb1._data[i] = i;
    }
    int value1 = rb1.GetRandomData();
    cout << value1 << endl;

    RandomBox<float, 20> rb2;
    for (int i = 0; i < 20; i++)
    {
        rb2._data[i] = i + 0.5f;
    }
    float value2 = rb2.GetRandomData();
    cout << value2 << endl;

    //rb1 = rb2; // 에러 - 템플릿 타입이 다르기 때문에 다른 클래스로 인식됨

    RandomBox<double, 20> rb3;
    for (int i = 0; i < 20; i++)
    {
        rb3._data[i] = i + 0.5f;
    }
    float value3 = rb3.GetRandomData();
    cout << value3 << endl;

    return 0;;
}
#pragma endregion
#pragma region CallBack 함수 구현
// CallBack

class FindByOwnerId // Functor
{
public:
    bool operator()(const Item* item)
    {
        if (item == nullptr) return false;
        return item->_ownerID == _ownerId;
    }

public:
    int _ownerId;
};

class FindByRarity // Functor
{
public:
    bool operator()(const Item* item)
    {
        if (item == nullptr) return false;
        return item->_rarity == _rarity;
    }

public:
    int _rarity;
};

template<typename T>
Item* FindItem(Item items[], int itemCount, T selector)
{
    for (int i = 0; i < itemCount; i++)
    {
        Item* item = &items[i];

        if (selector(item))
            return item;
    }

    return nullptr;
}

int main10()
{
    Item * items = new Item[10];
    (items + 3)->_ownerID = 100;
    (items + 8)->_rarity = 2;

    FindByOwnerId functor1;
    functor1._ownerId = 100;

    FindByRarity functor2;
    functor2._rarity = 2;

    Item* item1 = FindItem(items, 10, functor1);
    Item* item2 = FindItem(items, 10, functor2);

    delete[] items;

    return 0;
}
#pragma endregion

// STL (Standard Template Library)
// 프로그래밍할 때 필요한 자료구조/알고리즘들을
// 템플릿으로 제공하는 라이브러리

// 컨테이너(Container) : 데이터를 저장하는 객체 (자료구조 Data Structure)
#pragma region vector
#include <vector>
int main11()
{
    // vector
    // - vector의 동작 원리 (size/capacity)
    // - 중간 삽입/삭제
    // - 처음/끝 삽입/삭제
    // - 임의 접근
    
    // 배열
    const int MAX_SIZE = 1000;
    /*int arr[MAX_SIZE] = {};

    for (int i = 0; i < MAX_SIZE; i++)
        arr[i] = i;
    for (int i = 0; i < MAX_SIZE; i++)
        cout << arr[i] << endl;*/

    // 동적 배열
    // 1) (여유분을 두고) 메모리를 할당한다
    // 2) 여유분까지 꽉 찼으면, 메모리를 증설한다 - (메모리 영역 다시 할당)

    // Q1) 여유분은 얼만큼이 적당할까? - 컴파일러에 따라 1.5배 혹은 2배 증설
    // Q2) 증설을 얼마만큼 해야 할까? - 컴파일러에 따라 1.5배 혹은 2배 증설
    // Q3) 기존의 데이터를 어떻게 처리할까? - capacity 재할당->복사->기존 데이터 제거

    vector<int> v;
    // vector<int> v(MAX_SIZE, 0); // (capacity, 기본값)
    // v.reserve(MAX_SIZE); // capacity 지정 == vecotr<int> v(MAX_SIZE);
    // v.resize(MAX_SIZE); // size 지정 -> size에 따라 capacity 수정됨

    // size (실제 사용 데이터 개수)
    // 1 2 3 4 5 6 7 ....
    // capaciy (여유분을 포함한 용량 개수)
    // 1 2 3 4 6 9 13 19 28 42 ...

    for (int i = 0; i < MAX_SIZE; i++)
    {
v.push_back(i);
//cout << v.size() << " " << v.capacity() << endl;
    }

    const int size = v.size(); // 중간에 크기 변할때 오류 방지
    for (int i = 0; i < size; i++)
    {
        //cout << v[i] << endl;
    }

    v.pop_back();
    cout << v.size() << " " << v.capacity() << endl;
    int ret = v.back(); // pop은 안하고 그냥 마지막꺼 호출
    cout << v.size() << " " << v.capacity() << endl;
    v.clear();
    cout << v.size() << " " << v.capacity() << endl;
    vector<int>().swap(v); // 이런식으로 메모리 날릴 수 있지만 자주 쓰이진 않는다. 그냥 팁
    cout << v.size() << " " << v.capacity() << endl;



    // 반복자(iterator) : 포인터와 유사한 개념. 컨테이너의 원소(데이터)를 가리키고, 다음/이전 원소로 이동 가능
    vector<int> v2(10);

    for (vector<int>::size_type i = 0; i < v2.size(); i++)
    {
        v2[i] = i;
    }

    vector<int>::iterator it;
    int* ptr;

    it = v2.begin();
    ptr = &v2[0];

    cout << *it << endl;
    cout << *ptr << endl;

    vector<int>::iterator itBegin = v2.begin();
    vector<int>::iterator itEnd = v2.end(); // 마치 string \n 처럼 vector의 끝을 의미, 실제 vector 내부 데이터 아님

    // iterator로 데이터에 접근하는 이유
    // - 다른 컨테이너는 v[i]와 같은 인덱스 접근이 안될 수 있음
    // - iterator는 vector뿐 아니라, 다른 컨테이너도 공통적으로 있는 개념
    for (vector<int>::iterator it = v2.begin(); it != v2.end(); ++it) // ++it 권장
    {
        cout << *it << endl;
    }

    int* ptrBegin = &v2[0]; // == v2.begin()._Ptr;
    int* ptrEnd = ptrBegin + 10; //v.end()_Ptr;
    for (int* ptr = ptrBegin; ptr != ptrEnd; ++ptr)
    {
        cout << *ptr << endl;
    }

    // const int*;
    vector<int>::const_iterator cit1 = v2.cbegin();
    //*cit1 = 100; //수정불가, 에러

    // reverse_iterator 자주 사용하는 개념은 아님
    for (vector<int>::reverse_iterator it = v2.rbegin(); it != v2.rend(); ++it)
    {
        cout << *it << endl;
    }

    //**************************************
    // vector 특성
    // vector = 동적 배열 = 동적으로 커지는 배열 = 배열
    // 원소가 하나의 메모리 블록에 연속하게 저장된다
    // - 중간 삽입/삭제 (비효욜적)
    // - 처음/끝 삽입/삭제 (처음-비효율적/끝-효율적)
    // - 임의 접근 (Random Access) (효율적)
    v2.reserve(100);
    ptrBegin = v2.begin()._Ptr; // 디버그용
    //vector<int>::iterator inserIt =  v2.insert(v2.begin() + 2, 99); // 추가한 위치 return
    //vector<int>::iterator eraseIt1 = v2.erase(v2.begin() + 2); // 지운 위치(v2.begin() + 2) return
    //vector<int>::iterator eraseIt2 = v2.erase(v2.begin() + 2, v2.begin() + 4); // 지운 범위 시작 위치(v2.begin() + 2) return

    // 쭉 스캔해서 3이라는 데이터가 있으면 일괄 삭제하고 싶다
    for (vector<int>::iterator it = v2.begin(); it != v2.end();)
    {
        int data = *it;
        if (data == 3)
        {
            it = v2.erase(it); // 할당 안하면 it 데이터 날라간 상태로 진행되서 에러
        }
        else
        {
            // erase하면 지운 자리에 바로 다음 데이터가 왔기때문에 erase 안했을때만 iterator 갱신
            ++it;
        }
    }

    return 0;
}

// 나만의 vector 구현하기

template<typename T>
class Iterator_Vector
{
public:
    Iterator_Vector() : _Ptr(nullptr)
    {

    }

    Iterator_Vector(T* ptr) : _Ptr(ptr)
    {

    }

    Iterator_Vector& operator++()
    {
        _Ptr++;
        return *this;
    }

    Iterator_Vector operator++(int) // &가 없는(참조 타입이 아닌) 이유는 복사된 값을 출력하려고
    {
        Iterator_Vector temp = *this; // 복사
        _Ptr++;
        return temp;
    }

    Iterator_Vector& operator--()
    {
        _Ptr--;
        this* this;
    }

    Iterator_Vector operator--(int) // &가 없는(참조 타입이 아닌) 이유는 복사된 값을 출력하려고
    {
        Iterator_Vector temp = *this; // 복사
        _Ptr--;
        return temp;
    }

    Iterator_Vector operator+(const int count)
    {
        Iterator_Vector temp = *this;
        temp._Ptr += count;
        return temp;
    }

    Iterator_Vector operator-(const int count)
    {
        return *this + (count);
    }

    bool operator==(const Iterator_Vector& right)
    {
        return _Ptr == right._Ptr;
    }
    
    bool operator!=(const Iterator_Vector& right)
    {
        return !(*this == right);
    }

    T& operator*()
    {
        return *_Ptr;
    }

public:
    T* _Ptr;
};

template<typename T>
class Vector
{
public:
    Vector() : _data(nullptr), _size(0), _capacity(0)
    {

    }

    ~Vector()
    {
        if (_data)
            delete[] _data;
    }

    void push_back(const T& val)
    {
        if (_size == _capacity)
        {
            // 증설 작업
            int newCapacity = static_cast<int>(_capacity * 1.5);
            if (newCapacity == _capacity)
                newCapacity++;

            reserve(newCapacity);
        }

        _data[_size] = val;
        _size++;
    }

    void reserve(int capacity)
    {
        _capacity = capacity;

        T* newData = new T[_capacity];

        // 데이터 복사
        for (int i = 0; i < _size; i++) // _size 0이면 작동 안하므로 _data nullptr 체크 생략
            newData[i] = _data[i];

        // 기존에 있던 데이터 날린다
        if (_data)
            delete[] _data;

        // 교체
        _data = newData;
    }

    T& operator[](const int pos) { return _data[pos]; }

    int size() { return _size; }
    int capacity() { return _capacity; }
    void clear() { _size = 0; }

public:
    typedef Iterator_Vector<T> iterator;

    iterator begin() { return iterator(&_data[0]); }
    iterator end() { return begin() + _size; }


private:
    T* _data;
    int _size;
    int _capacity;
};

int main12()
{
    Vector<int> v;

    v.reserve(100);

    for (int i = 0; i < 100; i++)
    {
        v.push_back(i);
        cout << v.size() << " " << v.capacity() << endl;
    }

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }

    cout << "----------------" << endl;

    for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}
#pragma endregion
#pragma region List(Linked List)
#include <list>
// List (연결 리스트)
// - list의 동작 원리
// - 중간 삽입/삭제 (효율적) // 물론 중간에 삽입/삭제할 iterator를 찾는다는 것은 비효율적(임의 접근), 중간 데이터 iterator를 알고있다는 전제에서 효율적
// - 처음/끝 삽입/삭제 (효율적)
// - 임의 접근 (비효율적)

// 단일 / 이중 / 원형
// STL list는 이중연결리스트
// [1] <-> [2] <-> [3] <-> [4] <-> [5] <-> [ _Myhead : end() ] <-> [1] // _Myhead 노드 데이터는 null. 즉, 실제 데이터는 없음, vector처럼 데이터 끝을 표현

// STL list 노드 대략적인 구조
//class Node
//{
//public:
//    Node*   _next;
//    Node*   _prev;
//    int     _data;
//};

int main13()
{
    list<int> li;
    
    for (int i = 1; i < 100; i++)
        li.push_back(i);

    li.push_front(0); // vector와 다르게 가능
    int size = li.size();
    //li.capacity() // capacity 개념 없음

    int first = li.front();
    int last = li.back();

    //li[3] // [] 접근 없음

    list<int>::iterator itBegin = li.begin();
    list<int>::iterator itEnd = li.end();

    //list<int>::iterator itTest1 = --itBegin; // _Myhead 참조하면 에러
    //list<int>::iterator itTest2 = ++itEnd; // _Myhead 참조하면 에러
    list<int>::iterator itTest3 = --itEnd; // 마지막 데이터 가리키는 iterator
    //list<int>::iterator itTest4 = itBegin + 10; // 빌드 불가, 배열처럼 연속적인 데이터가 아니기때문, 그래도 위처럼 한 노드씩 ++ -- 으로 이동 가능
    
    int* ptrBegin = &(li.front());
    int* ptrEnd = &(li.back());

    for (list<int>::iterator it = li.begin(); it != li.end(); ++it)
    {
        cout << *it << endl;
    }

    li.insert(itBegin, 100);
    li.pop_front(); //li.erase(li.begin());
    li.remove(10); // vector는 불가능

    return 0;
}

// list 구현
template<typename T>
class Node
{
public:
    Node() : _next(nullptr), _prev(nullptr), _data(T())
    {

    }
    Node(const T& value) : _next(nullptr), _prev(nullptr), _data(value)
    {

    }

public:
    Node*   _next;
    Node*   _prev;
    T       _data;
};

template<typename T>
class Iterator_List // 나중에 따로 구현하면 자료구조별 iterator 공통 부모 클래스 만들어야할듯
{
public:
    Iterator_List() : _node(nullptr)
    {

    }

    Iterator_List(Node<T>* node) : _node(node)
    {

    }

    Iterator_List& operator++()
    {
        _node = _node->_next;
        return *this;
    }

    Iterator_List operator++(int)
    {
        Iterator_List<T> temp = *this;
        _node = _node->_next;
        return temp;
    }
    
    Iterator_List& operator--()
    {
        _node = _node->_prev;
        return *this;
    }
    
    Iterator_List operator--(int)
    {
        Iterator_List<T> temp = *this;
        _node = _node->_prev;
        return temp;
    }

    T& operator*()
    {
        return _node->_data;
    }

    bool operator==(const Iterator_List& right)
    {
        return _node == right._node;
    }

    bool operator!=(const Iterator_List& right)
    {
        return !(*this == right);
    }

public:
    Node<T>* _node;
};

template<typename T>
class List
{
public:
    List() : _size(0)
    {
        _Myheader = new Node<T>();
        _Myheader->_next = _Myheader;
        _Myheader->_prev = _Myheader;
    }

    ~List()
    {
        while (_size > 0)
            pop_back();

        delete _Myheader;
    }

    void push_back(const T& value)
    {
        AddNode(_Myheader, value);
    }

    void pop_back()
    {
        RemoveNode(_Myheader->_prev);
    }

public:
    typedef Iterator_List<T> iterator;

    iterator begin() { return iterator(_Myheader->_next); }
    iterator end() { return iterator(_Myheader->_prev); }

    iterator insert(iterator it, const T& value)
    {
        return iterator(AddNode(it._node, value));
    }

    iterator erase(iterator it)
    {
        return iterator(RemoveNode(it._node));
    }

private:
    // [node] <-> [header] <->
    // [1] <-> [2]           <->            [before] <-> [4] <-> [header] <->
    // [1] <-> [2(prevNode)] <-> [node] <-> [before] <-> [4] <-> [header] <->
    Node<T>* AddNode(Node<T>* before, const T& value)
    {
        Node<T>* node = new Node<T>(value);

        Node<T>* prevNode = before->_prev;
        prevNode->_next = node;
        node->_prev = prevNode;
        node->_next = before;
        before->_prev = node;

        _size++;

        return node;
    }

    // [1] <-> [prevNode] <-> [node] <-> [nextNode] <-> [4] <-> [header] <->
    // [1] <-> [prevNode] <->            [nextNode] <-> [4] <-> [header] <->
    Node<T>* RemoveNode(Node<T>* node)
    {
        Node<T>* prevNode = node->_prev;
        Node<T>* nextNode = node->_next;

        prevNode->_next = nextNode;
        nextNode->_prev = prevNode;
        
        delete node;

        _size--;

        return nextNode;
    }

public:
    Node<T>* _Myheader;
    int _size;
};

template<typename T>
using LIST = List<T>;// std:list<T>
int main14()
{
    LIST<int> li;

    LIST<int>::iterator eraseIt;

    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
        {
            eraseIt = li.insert(li.end(), i);
        }
        else
        {
            li.push_back(i);
        }
    }

    li.pop_back();

    li.erase(eraseIt);

    for (LIST<int>::iterator it = li.begin(); it != li.end(); ++it)
    {
        cout << (*it) << endl;
    }

    return 0;
}
#pragma endregion
#pragma region deque
#include <deque>
// 시퀀스 컨테이너 (Sequence Container)
// 데이터가 삽입 순서대로 나열되는 형태
// vector list deque

// vector : 동적 배열
// [        ]

// list : 이중 연결 리스트
// [ ] <-> [ ] <-> [ ] <-> [ ] <-> [ ]

// deque : double-ended queue 데크
// [        ] : 기본은 vector처럼 배열
// [        ] : capacity가 커져야될경우 vector처럼 재할당이 아닌 list처럼 다른 곳에 데이터 영역 할당
// [        ]

int main15()
{
    deque<int> dq;

    dq.push_back(1);
    dq.push_front(2);
    cout << dq[0] << endl;
    // vector와 마찬가지로 배열 기반으로 동작
    // 다만 메모리 할당 정책이 다르다

    vector<int> v(3, 1); // [1 1 1]
    deque<int> dq2(3, 1); // [1 1 1]

    v.push_back(2); // [1 1 1] 메모리 날리고   -> [1 1 1 2]
    v.push_back(2); // [1 1 1 2] 메모리 날리고 -> [1 1 1 2 2]
    dq2.push_back(2); //            [1 1 1 2]
    dq2.push_back(2); //            [1 1 1 2] [2      ]
    dq2.push_front(3); // [      3] [1 1 1 2] [2      ]
    dq2.push_front(3); // [    3 3] [1 1 1 2] [2      ]
    // 중간에 데이터 삭제할 경우
    //                    [    3 3] [1 1   2] [2      ]
    //                    [    3 3] [1 1 2 2]
    // 중간에 데이터 삽입할 경우
    //                    [    3 3] [1 1 (4) 2 2]
    //                    [  3 3 1] [1 1 4 2] : 데이터 크기가 효율적인 방향으로 칸이동

    // - deque의 동작 원리
    // - 중간 삽입/삭제 (비효율적 / 비효율적) : vector처럼 통으로 메모리 재할당 하는건 아니지만 삽입/삭제 후 값들을 이동시켜야하므로 list보단 느림
    // - 처음/끝 삽입/삭제 (효율적 / 효율적)
    // - 임의 접근 (가능)
    dq2[3] = 10; // 내부에서 iterator로 해당 값의 블록 및 인덱스 구해서 찾아줌
    cout << dq2[3] << endl;

    return 0;
}
#pragma endregion
#pragma region map
#include <map>

// map : 균형 이진 트리 (AVL)
// - 노드 기반

//class Node
//{
//public:
//    Node* _left;
//    Node* _right;
//
//    //DATA
//    //int     _key;
//    //Player* _value;
//    pair<int, Player*> _data;
//};

int main16()
{
    // vector, list의 치명적인 단점
    // -> 원하는 조건에 해당하는 데이터를 빠르게 찾을 수 없다.
    srand(static_cast<unsigned int>(time(nullptr)));
    map<int, int> m;

    pair<map<int, int>::iterator, bool> ok;
    ok = m.insert(make_pair(1, 100)); // make_pair(1, 100) == pair<int, int>(1, 100)
    ok = m.insert(make_pair(1, 200)); // insert 행동은 실패되고 위에 넣었던 100이 유지됨, 즉 넢어쓰지 않음

    for (int i = 0; i < 1000; i++)
    {
        m.insert(pair<int, int>(i, i * 100));
    }

    for (int i = 0; i < 500; i++)
    {
        int randomValue = rand() % 500;
        
        //m.erase(randomValue);
    }

    unsigned int count = 0;
    count = m.erase(100); // 삭제 성공했다면 삭제한 수 만큼 리턴
    count = m.erase(100);

    map<int, int>::iterator findIt =  m.find(100); // 못찾았으면 m.end() 리턴

    // 없으면 추가, 있으면 수정
    if (findIt != m.end())
    {
        findIt->second = 99;
        cout << "찾음, 수정함" << endl;
    }
    else
    {
        m.insert(make_pair(100, 99));
        cout << "못찾음, 추가함" << endl;
    }

    // 없으면 추가, 있으면 수정 v2
    m[100] = 999;
    // [] 사용에 주의할 점
    // - 대입을 하지 않더라도 (Key/Value) 형태의 데이터가 추가된다.
    // - 즉, 찾는게 목적이면 find(~)를 활용
    m.clear();
    for (int i = 0; i < 100; i++)
    {
        cout << m[i] << endl; //i키값이 없으면 호출할 때 i키값에 빈값(데이터의 기본값)을 넣게됨
    }

    //// map 순회 : 이러면 vector보다 효율 낮음
    //for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
    //{
    //    //pair<const int, int>& p = (*it);
    //    int key = it->first;
    //    int value = it->second;
    //    cout << key << " " << value << endl;
    //}

    // 중간 수정은 효율적인 자료구조임
    // 넣고 (insert, [])
    // 빼고 (erase)
    // 찾고 (find, [])
    // 반복자 (map::iterator) (*it) pair<key, value>&

    return 0;
}

// map의 형제들 : set, multimap, multiset
// - multi 붙어있으면 중복허용
#include <set>

int main17()
{
    set<int> s; //key가 곧 value

    s.insert(10);
    s.insert(30);
    s.insert(20);
    s.insert(50);
    s.insert(40);
    s.insert(70);
    s.insert(90);
    s.insert(80);
    s.insert(100);

    s.erase(40);

    set<int>::iterator findIt_s = s.find(50);
    if (findIt_s == s.end())
    {
        cout << "못찾음" << endl;
    }
    else
    {
        cout << "찾음" << endl;
    }

    //s[10] = 10; // 당연히 [] 호출 안됨

    for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
    {
        cout << (*it) << endl;
    }

    cout << "-------------------------------" << endl;

    multimap<int, int> mm;
    
    mm.insert(make_pair(1, 100));
    mm.insert(make_pair(1, 200));
    mm.insert(make_pair(1, 300));
    mm.insert(make_pair(2, 400));
    mm.insert(make_pair(2, 500));

    //mm[1] = 500; // 중복이 있을수있으니 당연히 안됨

    //unsigned int count = mm.erase(1); // 위에 key가 1인 3개 다 삭제되고 3 리턴

    multimap<int, int>::iterator findIt_mm = mm.find(1); // key가 1인 것 중 첫번째
    if (findIt_mm == mm.end())
    {
        cout << "못찾음" << endl;
    }
    else
    {
        cout << "찾음" << endl;
        mm.erase(findIt_mm); // key값만 넣은것과 다르게 해당 데이터만 erase, ++findIt_mm 이렇게 넣으면 다음꺼 삭제
    }

    //여러개 찾을 경우
    pair<multimap<int, int>::iterator, multimap<int, int>::iterator> itPair;
    itPair = mm.equal_range(1); // key값이 1인 값들 시작 iterator(1, 200)와 끝나는 다음의 iterator(2, 400) 리턴 // (1, 100)은 위에서 지워줌 ㅎ
    multimap<int, int>::iterator itPair_Begin = mm.lower_bound(1); // == itPair.first
    multimap<int, int>::iterator itPair_End = mm.upper_bound(1); // == itPair.second
    for (multimap<int, int>::iterator it = itPair.first; it != itPair.second; ++it)
    {
        cout << it->first << " " << it->second << endl;
    }

    for (multimap<int, int>::iterator it = mm.begin(); it != mm.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }

    cout << "-------------------------------" << endl;

    multiset<int> ms;

    ms.insert(100);
    ms.insert(100);
    ms.insert(100);
    ms.insert(200);
    ms.insert(200);

    multiset<int>::iterator findIt_ms = ms.find(100); // 100값을 가진 것 중 첫번째

    auto itPair_ms = ms.equal_range(100);
    multiset<int>::iterator itPair_ms_Begin = ms.lower_bound(1); // == itPair_ms.first
    multiset<int>::iterator itPair_ms_End = ms.upper_bound(1); // == itPair_ms.second
    for (multiset<int>::iterator it = itPair_ms.first; it != itPair_ms.second; ++it)
    {
        cout << (*it) << endl;
    }
    for (multiset<int>::iterator it = ms.begin(); it != ms.end(); ++it)
    {
        cout << (*it) << endl;
    }

    // 실무에서 multimap, multiset 잘 안쓰임
    // set은 아주 가끔 쓰임

    return 0;
}
#pragma endregion
#pragma region STL 마무리, 알고리즘
#include <algorithm>
// 자료구조 (데이터를 저장하는 구조)
// 알고리즘 (데이터를 어떻게 사용할 것인가?)

// find
// find_if
// count
// count_if
// all_of
// any_of
// none_of
// for_Each
// remove
// remove_if

int main18()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<int> v;

    for (int i = 0; i < 100; i++)
    {
        int num = rand() % 100;
        v.push_back(num);
    }

    // Q1) number라는 숫자가 벡터에 체크하는 기능 (bool, 첫 등장 iterator)
    {
        int number = 50;

        bool found = false;
        vector<int>::iterator it;
        // A1
        for (vector<int>::iterator _it = v.begin(); _it != v.end(); ++_it)
        {
            if ((*_it) == number)
            {
                it = _it;
                found = true;
                break;
            }
        }
        // A2
        auto itFind = std::find(v.begin(), v.end(), number);
        if (itFind == v.end())
        {
            cout << "못찾음" << endl;
        }
        else
        {
            cout << "찾음" << endl;
        }
    }

    // Q2) 11로 나뉘는 숫자가 벡터에 있는지 체크하는 기능 (bool, 첫 등장 iterator)
    {
        bool found = false;
        vector<int>::iterator it;

        //A1
        for (vector<int>::iterator _it = v.begin(); _it != v.end(); ++_it)
        {
            if ((*_it) != 0 && (*_it) % 11 == 0)
            {
                it = _it;
                found = true;
                cout << "11로 나뉘는 숫자 존재 확인 : " << (*it) << endl;
                break;
            }
        }
        //A2
        struct CanDivideByNumber
        {
            CanDivideByNumber(int _num) : num(_num) {}
            int num;
            bool operator()(int n)
            {
                return (n % num) == 0;
            }
        };
        auto itFind = std::find_if(v.begin(), v.end(), CanDivideByNumber(11)); // CanDivideByNumber(11) -> [](int n) { return (n % 11) == 0; } // 람다식 표현
        if (itFind == v.end())
        {
            cout << "못찾음" << endl;
        }
        else
        {
            cout << "찾음" << endl;
            cout << "11로 나뉘는 숫자 존재 확인 : " << (*itFind) << endl;
        }
    }

    // Q3) 홀수인 숫자의 개수는?
    {
        int count = 0;
        // A1
        for (vector<int>::iterator _it = v.begin(); _it != v.end(); ++_it)
        {
            if ((*_it) % 2 != 0)
            {
                count++;
            }
        }
        cout << "홀수인 숫자 : " << count << "개" << endl;
        // A2
        auto count_if_result = std::count_if(v.begin(), v.end(), [](int n) { return n % 2 != 0; });
        cout << "홀수인 숫자 : " << count_if_result << "개" << endl;

        bool b1 = std::all_of(v.begin(), v.end(), [](int n) { return n % 2 != 0; }); // 모두가 홀수인지 확인
        bool b2 = std::any_of(v.begin(), v.end(), [](int n) { return n % 2 != 0; }); // 홀수인 데이터가 하나라도 있는가
        bool b3 = std::none_of(v.begin(), v.end(), [](int n) { return n % 2 != 0; }); // 홀수인 데이터가 하나도 없는가
    }

    // Q4) 벡터에 들어가 있는 모든 숫자들에 3을 곱해주세요!
    {
        // A1
        /*for (int i = 0; i < v.size(); i++)
        {
            v[i] *= 3;
        }*/
        // A2
        std::for_each(v.begin(), v.end(), [](int& n) { n *= 3; });
    }
    
    // Q5) 홀수인 데이터 일괄 삭제
    {
        // A1
        for (vector<int>::iterator it = v.begin(); it != v.end();)
        {
            if ((*it) % 2 != 0)
                it = v.erase(it);
            else
                ++it;
        }
        // A2

    }

    {
        v.clear();
        v.push_back(1);
        v.push_back(4);
        v.push_back(3);
        v.push_back(5);
        v.push_back(8);
        v.push_back(2);

        // 1 4 3 5 8 2
        //std::remove(v.begin(), v.end(), 4);
        auto remove_if_result = std::remove_if(v.begin(), v.end(), [](int n) { return (n % 2) != 0; });
        // 1 4 3 5 8 2
        // 4 8 2 5 8 2
        // remove_if는 여기서 5를 가리키는 iterator 리턴
        v.erase(remove_if_result, v.end());
        // v.erase(remove_if(v.begin(), v.end(), [](int n) { return (n % 2) != 0; }), v.end()); // 위 내용을 한줄로
        int a = 3;
    }


    return 0;
}

#pragma endregion
#pragma region Modern C++ (C++11 이후)
class ModernKnight
{
public:
    ModernKnight() {}
    ModernKnight(int a, int b)
    {
        cout << "ModernKnight(int, int)" << endl;
    }
    ModernKnight(initializer_list<int> li)
    {
        cout << "ModernKnight(initializer_list)" << endl;
    }
};
int main19()
{
    typedef ModernKnight Knight;
    // auto
    
    //int a = 3;
    //float b = 3.14f;
    //double c = 1.23;
    //Knight d = Knight();
    //const char* e = "HelloWorld";
    auto a = 3;
    auto b = 3.14f;
    auto c = 1.23;
    auto d = Knight();
    auto e = "HelloWorld";

    // type deduction(형식 연역)
    // 추론 규칙은 생각보다 복잡해질 수 있다
    auto f = &d;
    const auto test1 = b;
    auto* test2 = e;
    //auto* test3 = a; // 에러
    
    // 주의!
    // 기본 auto는 const, &가 무시됨 !!!!!!!!!
    int& reference = a;
    const int cst = a;
    auto test4 = reference;
    auto test5 = cst;

    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    for (vector<int>::size_type i = 0; i < v.size(); i++)
    {
        auto data = v[i]; //auto가 int&가 아닌 int로 인식되서 값 수정이 안됨. auto& 사용

        data = 10;;
    }

    // ----------------------------------------------------------------------------------------------------
    // 중괄호 초기화
    int n1 = 0;
    int n2(0);
    int n3{ 0 };

    Knight k1;
    Knight k2 = k1; // 복사 생성자 (대입 연산자X)
    Knight k3(k1); // 복사 생성자
    Knight k4{ k1 }; // 복사 생성자

    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    vector<int> v2(3, 1); // 그냥 값 1인거 3개
    vector<int> v3{ 1, 2, 3 }; // 원래 안됬었던듯

    // 중괄호 초기화
    // 1) vector 등 container와 잘 어울린다
    
    // 2) 축소 변환 방지
    int num = 0;
    double d1(num);
    // double d2{ num }; // 빌드하면 축소 변환 필요하다고 에러뜸
    
    // 3) Bonus
    Knight k5(); // 기본 생성자가 아님, 함수를 선언한 격
    Knight k6{ }; // 기본 생성자 출력
    Knight k7{ 1, 2, 3, 4, 5 }; //initializer_list 생성자 없으면 에러
    Knight k8{ 1, 2 }; // (int, int) 생성자가 아닌 initializer_list 생성자 호출됨. 애초에 { } 가 배열개념이니 당연한거 아닌가 라고 생각했지만 그렇다면 위에 빈값이 기본 생성자 호출하는것도 웃기고

    //개인적인 의견 : 배열, STL 컨테이너 아닌 이상 큰 의미 없는거 같고 클래스도 Knight k9( { 1, 2, 3 } ) 그냥 이런식으로 가는게 생성자 유추가 쉬워 가독성이 좋아보임
    return 0;
}
// ----------------------------------------------------------------------------------------------------
class NullCheckKnight
{
public:
    void Test() {}
};
NullCheckKnight* FindKnight()
{
    return nullptr;
}
void Test(int a) { cout << "Test(int)" << endl; }
void Test(void* ptr) { cout << "Test(*)" << endl; }

// NullPtr 구현
const class
{
public:
    // 그 어떤 타입의 포인터와도 치환 가능
    template<typename T>
    operator T* () const
    {
        cout << "operator T* ()" << endl;
        return 0;
    }
    // 그 어떤 타입의 멤버 포인터와도 치환 가능
    template<typename C, typename T>
    operator T C::* () const
    {
        cout << "operator T C::* ()" << endl;
        return 0;
    }
private:
    void operator&() const; // 주소값 참조 막기
} _NullPtr;
//const NullPtr _NullPtr;

int main20()
{
    typedef NullCheckKnight Knight;
    // nullptr
    // 기존에는 0, NULL(이것도 그냥 0) 사용
    int* ptr = NULL;

    // 1) 오동작
    Test(0); // Test(int) 호출
    Test(NULL); // Test(int) 호출
    Test(_NullPtr); // Test(*) 호출

    // 2) 가독성
    auto knight = FindKnight();
    if (knight == _NullPtr) // (knight == NULL) 이게 int형 오퍼레이터 가지고있으면 골때리게됨
    {

    }

    void (Knight:: * memFunc)();
    memFunc = &Knight::Test;
    if (memFunc == _NullPtr)
    {

    }
    //nullptr_t whoami = nullptr;

    // ----------------------------------------------------------------------------------------------------
    return 0;
}


// using
typedef __int64 id;
using id2 = int;

// 1) 직관성
typedef void (*MyFunc)();
using MyFunc2 = void(*)();

// 2) 템플릿
template<typename T>
using DefList2 = std::list<T>;
//typedef로 아래처럼 활용 할 수 있으나 이제는 안쓰임
template<typename T>
struct DefList
{
    typedef std::list<T> type;
};


// enum class (scoped enum)
// 1) 이름공간 관리 (scoped)
// 2) 암묵적인 변환 금지(장점이자 단점)

// 기존 enum : unscoped enum (범위없는)
enum PlayerType : char // 이렇게 특정 안하면 기본적으로 int
{
    None,
    PT_Knight,
    PT_Archer,
    PT_Mage
};
enum MonsterType
{
    //None, // PlayerType::None 때문에 재정의하라고 빌드에러뜸
};

enum class ObjectType
{
    Player,
    Monster,
    Projectile
};
enum class ObjectType2 // 기존 enum과 다르게 재정의 에러 없음
{
    Player,
    Monster,
    Projectile
};

int main21()
{
    double dValue1 = PT_Knight;
    //double dValue2 = ObjectType::Player; //암묵적인 변환 불가, static_cast<doulbe> 같은거 붙혀서 억지로 가능

    int choice;
    cin >> choice;
    if (choice == static_cast<int>(ObjectType::Monster))
    {

    }
    // 즉, enum class는 자신을 타입으로 받음, 형변환 필요
    return 0;
}


// delete (삭제된 함수)

class DKnight
{
public:

private:
    void operator=(const DKnight& k);
    friend class Admin;

private:
    int _hp = 100;
};
class DKnight2
{
public:
    void operator=(const DKnight2& k) = delete;
private:
    int _hp = 100;
};

class Admin
{
public:
    void CopyKnight(const DKnight& k)
    {
        DKnight k1;
        k1 = k; // friend class 등록으로 가능해짐, 하지만 구현부가 없어서 빌드하면 에러
    }
    void CopyKnight(const DKnight2& k)
    {
        DKnight2 k2;
        //k2 = k; // 삭제된 함수라며 에러
    }

};

int main22()
{
    DKnight k1;
    DKnight k2;
    //k1 = k2; private으로 해서 에러
    Admin admin;
    //admin.CopyKnight(k1); // DKnight operator=() 구현부가 없어서 빌드에러
    DKnight2 k3;
    admin.CopyKnight(k3);

    return 0;
}


// override, final

class OFCreature
{
public:
    virtual void Generate()
    {

    }
};

class OFPlayer : public OFCreature
{
public:
    virtual void Attack()
    {
        cout << "Player!" << endl;
    }
    virtual void Generate() override final
    {
        
    }
};
class OFKnight : public OFPlayer
{
public:
    // 재정의 (override)
    virtual void Attack() override // 이 함수가 최초 가상함수가 아니라는 것을 알 수 있게 되었다. 부모클래스에 가상함수 없으면 override 에러뜸
    {
        cout << "Knight!" << endl;
    }

    // overloading
    void Attack() const // 다른 매개변수 취급으로 overloading되는듯
    {
        //_stamina = 10; //const 키워드 때문에 에러, const 키워드 함수는 내부 함수 데이터 변경 불가능
    }
    void Attack(int a)
    {
        cout << "Knight(int)!" << endl;
    }

    //virtual void Generate(); // final 키워드 때문에 재정의 불가능
private:
    int _stamina = 100;
};

int main23()
{
    using Player = OFPlayer;
    using Knight = OFKnight;

    Player* player = new Knight();
    player->Attack();


    return 0;
}

// 오른값(rvalue) 참조와 std::move
// Modern C++11 에서 가장 중요한 변경점

// 왼값(lvalue) vs 오른값(rvalue)
// - lvalue : 단일식을 넘어서 계속 지속되는 개체
// - rvalue : lvaㅣue가 아닌 나머지 (임시 값, 열거형, 람다, i++ 등)

class RLPet
{
public:
};
class RLKnight
{
public:
    RLKnight()
    {
        cout << "Knight()" << endl;
    }
    // 복사 생성자
    RLKnight(const RLKnight& knight)
    {
        cout << "const Knight&" << endl;
    }
    // 이동 생성자
    RLKnight(RLKnight&& knight)
    {

    }

    ~RLKnight()
    {
        if (_pet)
            delete _pet;
    }

    // 복사 대입 연산자
    void operator=(const RLKnight& knight)
    {
        cout << "operator=(const Knight&)" << endl;

        _hp = knight._hp;
        // 깊은 복사, class 크기가 커짐에 따라 비용이 많이 발생할 수 있음
        if (knight._pet)
            _pet = new RLPet(*knight._pet);
    }
    // 이동 대입 연산자
    void operator=(RLKnight&& knight) noexcept
    {
        cout << "operator=(Knight&&)" << endl;

        _hp = knight._hp;
        _pet = knight._pet; // 굳이 깊은 복사를 할 필요가 없음. 어차피 사라질꺼 뺏어온다는 개념

        knight._pet = nullptr; // 소멸자에서 delete되는거 방지
    }

public:
    int _hp = 100;
    RLPet* _pet = nullptr;
};

void TestKnight_Copy(RLKnight knight) { }
void TestKnight_LValueRef(RLKnight& knight) { } // 읽기, 쓰기 가능
void TestKnight_ConstLValueRef(const RLKnight& knight) { } // 읽기만 가능
void TestKnight_RValueRef(RLKnight&& knight) { } // 원본유지가 어차피 안되니 읽기쓰기 다 가능, 이동 대상!
int main24()
{
    RLKnight k1;

    TestKnight_Copy(k1);

    TestKnight_LValueRef(k1);
    //TestKnight_LValueRef(Knight()); // 컴파일러에서 문법적으로 허용안함

    TestKnight_ConstLValueRef(RLKnight());

    //TestKnight_RValueRef(k1); // 에러
    TestKnight_RValueRef(RLKnight());
    TestKnight_RValueRef(static_cast<RLKnight&&>(k1)); //어거지로 캐스팅해서 사용은 가능

    RLKnight k2;
    k2._pet = new RLPet();
    k2._hp = 1000;

    RLKnight k3;
    // 오른값 참조로 캐스팅
    k3 = std::move(k2); //k3 = static_cast<RLKnight&&>(k2); 와 같은 의미
    // std::move의 본래 이름 후보 중 하나가 rvalue_cast

    // 자주쓰이는 예) unique_ptr 이동
    std::unique_ptr<RLKnight> uptr = std::make_unique<RLKnight>(); // 프로그램상 단 하나만 존재해야하는 포인터
    //std::unique_ptr<RLKnight> uptr2 = uptr; // 복사관련 함수들이 delete 되어있어서 에러
    std::unique_ptr<RLKnight> uptr2 = std::move(uptr);

    // 코어 라이브러리에서는 자주 쓰이는 문법

    return 0;
}


// 전달 참조(forwarding reference) C++17
// 옛날엔 보편 참조(universal reference) 라고도 불렸음

// && - 무조건 오른값 참조인건 아님

class FRKnight
{
public:
    FRKnight() { cout << "기본 생성자" << endl; }
    FRKnight(const FRKnight&) { cout << "복사 생성자" << endl; }
    FRKnight(FRKnight&&) noexcept { cout << "이동 생성자" << endl; }
};
void Test_Copy(FRKnight k)
{
    // 어떤 생성자가 사용되는지 지켜보기
}
void Test_RValueRef(FRKnight&& k) // 오른값 참조
{

}
template<typename T>
void Test_ForwardRef(T&& param) // 전달참조 (왼값 참조와 오른값 참조 동시에 처리 가능)
{
    //if (~)
    //    // 왼값 참조라면 복사
    //    Test_Copy(param); // 복사 생성자 호출
    //else
    //    // 오른값 참조라면 이동
    //    Test_Copy(std::move(param)); // 이동 생성자 호출

    // 위 내용을 한줄로
    Test_Copy(std::forward<T>(param));
}
template<typename T>
void Test_ConstRValueRef(const T&& param) // const같은 추가 키워드가 붙으면 전달참조가 아닌 오른값 참조가 됨
{

}
int main25()
{
    FRKnight k1;
    Test_RValueRef(std::move(k1)); // rvalue_cast
    Test_ForwardRef(std::move(k1));
    Test_ForwardRef(k1);
    Test_ConstRValueRef(std::move(k1));
    //Test_ConstRValueRef(k1); //에러

    auto&& k2 = k1;
    auto&& k3 = std::move(k1);

    // 공통점 : 형식 연역 (type deduction)이 일어날 때 (auto, template)

    // 전달 참조 구문하는 방법
    FRKnight& k4 = k1; // 왼값 참조
    FRKnight&& k5 = std::move(k1);

    // 오른값 : 왼값이 아니다 = 단일식에서 벗어나면 사용 불가
    // 오른값 참조 : 오른값만 참조할 수 있는 참조 타입
    //Test_RValueRef(k5); //에러, k5 타입은 오른값 참조형이긴 하지만 k5 자체는 오른값이 아닌 왼값이라 에러남(선언되어 단독적으로 사용 가능하므로 왼값임)
    Test_RValueRef(std::move(k5));

    return 0;
}

// 람다(lambda)
// 함수 객체를 빠르게 만드는 문법
enum class LItemType
{
    None,
    Armor,
    Weapon,
    Jewelry,
    Consumable,
};
enum class LRarity
{
    Common,
    Rare,
    Unique
};
class LItem
{
public:
    LItem() { }
    LItem(int itemId, LRarity rarity, LItemType type)
        : _itemId(itemId), _rarity(rarity), _type(type)
    {

    }
public:
    int _itemId = 0;
    LRarity _rarity = LRarity::Common;
    LItemType _type = LItemType::None;
};

int main26()
{
    vector<LItem> v;
    v.push_back(LItem(1, LRarity::Common, LItemType::Weapon));
    v.push_back(LItem(2, LRarity::Common, LItemType::Armor));
    v.push_back(LItem(3, LRarity::Rare, LItemType::Jewelry));
    v.push_back(LItem(4, LRarity::Unique, LItemType::Weapon));

    // 람다 = 함수 객체를 손쉽게 만드는 문법
    // 람다 자체로 C++11에 '새로운' 기능이 들어간 것은 아니다.
    {
        struct IsUniqueItem
        {
            bool operator()(LItem& item)
            {
                return item._rarity == LRarity::Unique;
            }
        };

        // 클로저 (closure) = 람에 의해 만들어진 실행시점 객체
        auto isUniqueLambda = [](LItem& item) { return item._rarity == LRarity::Unique; }; // 람다 표현식(lambda expression)
        //                    [](LItem& item) -> int { return item._rarity == LRarity::Unique; }; // 이러면 boolean이 아닌 int값 return

        auto findIt = std::find_if(v.begin(), v.end(), IsUniqueItem());
        if (findIt != v.end())
            cout << "아이템ID:" << findIt->_itemId << endl;
        findIt = std::find_if(v.begin(), v.end(), isUniqueLambda);
        if (findIt != v.end())
            cout << "아이템ID:" << findIt->_itemId << endl;
    }
    {
        struct FindItemByItemId
        {
            FindItemByItemId(int itemId) : _itemId(itemId) { }
            bool operator()(LItem& item)
            {
                return item._itemId == _itemId;
            }

            int _itemId;
        };

        int itemId = 4;
        // [ ] 캡처(capture) : 함수 객체 내부에 변수를 저장하는 개념과 유사
        // 일종의 스냅샷
        // 기본 캡처 모드 : 복사 방식(=) 참조 방식(&)
        auto findByItemIdLambda = [&](LItem& item) { return item._itemId == itemId; }; // & -> = 으로 하면 위 4 값으로 고정되어 들어감
        itemId = 3;
        auto findIt = std::find_if(v.begin(), v.end(), FindItemByItemId(itemId));
        if (findIt != v.end())
            cout << "아이템ID:" << findIt->_itemId << endl;
        findIt = std::find_if(v.begin(), v.end(), findByItemIdLambda);
        if (findIt != v.end())
            cout << "아이템ID:" << findIt->_itemId << endl;
    }

    {
        struct FindItem
        {
            FindItem(int itemId, LRarity rarity, LItemType type)
                : _itemId(itemId), _rarity(rarity), _type(type)
            {

            }
            bool operator()(LItem& item)
            {
                return item._itemId == _itemId && item._rarity == _rarity && item._type == _type;
            }

            int _itemId;
            LRarity _rarity;
            LItemType _type;
        };

        int itemId = 4;
        LRarity rarity = LRarity::Unique;
        LItemType type = LItemType::Weapon;

        // 변수마다 캡처모드를 지정해서 사용 가능
        auto findByItemLambda = [=, &type](LItem& item) // == [itemId, rarity, &type](LItem& item) // C++에선 = 또는 & 로 통일하는 것을 지양함
        {
            return item._itemId == itemId && item._rarity == rarity && item._type == type;
        };
        
        auto findIt = std::find_if(v.begin(), v.end(), FindItem(itemId, rarity, type));
        if (findIt != v.end())
            cout << "아이템ID:" << findIt->_itemId << endl;
        findIt = std::find_if(v.begin(), v.end(), findByItemLambda);
        if (findIt != v.end())
            cout << "아이템ID:" << findIt->_itemId << endl;
    }

    {
        class Knight
        {
        public:
            auto ResetHpJob()
            {
                auto f = [this]() // =, & 가 아닌 변수를 명시해서 가시성을 확보하여 오류 예방
                {
                    this->_hp = 200; 
                };

                return f;
            }
        public:
            int _hp = 100;
        };

        /*class Functor
        {
        public:
            Functor(Knight* k) : _knight(k)
            {

            }

            void operator()()
            {
                _knight->_hp = 200;
            }

        public:
            Knight* _knight;
        };*/

        Knight* k = new Knight();
        auto job = k->ResetHpJob();
        delete k;
        job(); // 엉뚱한 메모리를 참조하지만 crash가 안나기 때문에 조심!
    }

    // [캡처](인자값){구현부}ㅡ

    return 0;
}

// 스마트 포인터 (smart pointer)
// 멀티스레드 환경에서 atomic이랑 큰 연관이 있음
// 스마트 포인터 : 포인터를 알맞는 정책에 따라 관리하는 객체 (포인터를 래핑해서 사용)
// shared_ptr, weak_ptr, unique_ptr

class RefCountBlock
{
public:
    int _refCount = 1;
    int _weakCount = 1;
};

template<typename T>
class SharedPtr
{
public:
    SharedPtr() {}
    SharedPtr(T* ptr) : _ptr(ptr)
    {
        if (_ptr != nullptr)
        {
            _block = new RefCountBlock();
            cout << "RefCount : " << _block->_refCount << endl;
        }
    }
    SharedPtr(const SharedPtr& sptr) : _ptr(sptr._ptr), _block(sptr._block)
    {
        if (_ptr != nullptr)
        {
            _block->_refCount++;
            cout << "RefCount : " << _block->_refCount << endl;
        }
    }
    ~SharedPtr()
    {
        if (_ptr != nullptr)
        {
            _block->_refCount--;
            cout << "RefCount : " << _block->_refCount << endl;

            if (_block->_refCount == 0)
            {
                delete _ptr;
                delete _block;
                cout << "Delete Ptr" << endl;
            }
        }
    }

    void operator=(const SharedPtr& sptr)
    {
        _ptr = sptr._ptr;
        _block = sptr._block;
        if (_ptr != nullptr)
        {
            _block->_refCount++;
            cout << "RefCount : " << _block->_refCount << endl;
        }
    }
public:
    T* _ptr = nullptr;
    RefCountBlock* _block = nullptr;
};

int main27()
{
    class Knight
    {
    public:
        Knight() { cout << "Knight 생성" << endl; }
        ~Knight() { cout << "Knight 소멸" << endl; }
        void Attack()
        {
            if (_target)
            {
                _target->_hp -= _damage;
                cout << "Target HP : " << _target->_hp << endl;
            }
            if (_shared_target)
            {
                _shared_target->_hp -= _damage;
                cout << "Target HP : " << _shared_target->_hp << endl;
            }
            if (_weak_target.expired() == false)
            {
                shared_ptr<Knight> sptr = _weak_target.lock();
                sptr->_hp -= _damage;
                cout << "Target HP : " << sptr->_hp << endl;
            }
        }
    public:
        int _hp = 100;
        int _damage = 10;
        Knight* _target = nullptr;
        shared_ptr<Knight> _shared_target = nullptr; // 성능은 스마트포인터가 낮지만 안정성 때문에
        weak_ptr<Knight> _weak_target; // 객체 존재여부 확인용, weak_ptr 자체로는 직접적으로 생명주기에 관여하지 않음, 참조 카운터 순환 방지됨
    };

    Knight* k1 = new Knight();
    Knight* k2 = new Knight();

    k1->_target = k2;

    delete k2; // k2 데이터는 지워졌지만 k1에서 가지고있는 메모리 주소는 지워지지 않음

    k1->Attack();


    SharedPtr<Knight> k3;
    {
        SharedPtr<Knight> k1(new Knight);
        k3 = k1;
    }

    shared_ptr<Knight> k4 = make_shared<Knight>();
    {
        shared_ptr<Knight> k1 = make_shared<Knight>();
        k4->_shared_target = k1;
    }
    k4->Attack();

    cout << "--------- 참조 카운터 순환 문제 확인 --------" << endl;
    {
        // 참조 카운터 순환으로 인한 메모리 삭제 안되는 문제발생 가능
        shared_ptr<Knight> k5 = make_shared<Knight>(); // k5 [1], k6[0]
        shared_ptr<Knight> k6 = make_shared<Knight>(); // k5 [1], k6[1]
        k5->_shared_target = k6; // k5 [1], k6[2]
        k6->_shared_target = k5; // k5 [2], k6[2]
        // 이 상태로 끝나면 서로 소멸해도 참조 카운터가 1씩 남아서 메모리 삭제가 안됨 k5 [1], k6[1]
        k5->_shared_target = nullptr;
        k6->_shared_target = nullptr;
        // k5 [0], k6 [0]
    }

    cout << "--------- weak_ptr로 메모리 잘 정리되는지 확인 --------" << endl;
    {
        shared_ptr<Knight> k5 = make_shared<Knight>(); // k5 [1], k6[0]
        shared_ptr<Knight> k6 = make_shared<Knight>(); // k5 [1], k6[1]
        k5->_weak_target = k6; // k5 [1], k6[2]
        k6->_weak_target = k5; // k5 [2], k6[2]
    }
    cout << "-----------------" << endl;

    unique_ptr<Knight> uptr = make_unique<Knight>();
    //unique_ptr<Knight> uptr2 = uptr; // 에러
    unique_ptr<Knight> uptr2 = std::move(uptr); // uptr은 empty가 됨

    return 0;
}

#pragma endregion

int main()
{
    //TextRPG();
    main27();

    return 0;
}

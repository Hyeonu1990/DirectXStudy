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

class Dog
{

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

    void* p = malloc(1000);
    Dog* dog2 = reinterpret_cast<Dog*>(p); // (Dog*)p;

    return 0;
}

int main()
{
    main6();
    return 0;
}

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>
#include <windows.h>

// TIC_TAE_TOE
// - 해당 예제는 종만북(알고리즘 문제 해결 전략)에서 가져왔다고함

// [ ][ ][ ]
// [ ][O][X]
// [ ][ ][O]

vector<vector<char>> board;
int TTTcache[19683];

bool IsFinished(const vector<vector<char>>& board, char turn)
{
    // 좌우
    for (int i = 0; i < 3; i++)
        if (board[i][0] == turn && board[i][1] == turn && board[i][2] == turn)
            return true;

    // 상하
    for (int i = 0; i < 3; i++)
        if (board[0][i] == turn && board[1][i] == turn && board[2][i] == turn)
            return true;

    // 대각선
    if (board[0][0] == turn && board[1][1] == turn && board[2][2] == turn)
        return true;
    if (board[2][0] == turn && board[1][1] == turn && board[0][2] == turn)
        return true;

    return false;
}

enum
{
    DEFAULT = 2,
    WIN = 1,
    DRAW = 0,
    LOSE = -1
};

// 0 ~ 3 ^ 9 = 19683
int HashKey(const vector<vector<char>>& board)
{
    // 3진수 형식으로 출력
    int ret = 0;

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            ret = ret * 3;

            if (board[y][x] == 'o')
                ret += 1;
            else if (board[y][x] == 'x')
                ret += 2;
        }
    }

    return ret;
}

int CanWin(vector<vector<char>>& board, char turn)
{
    // 기저 사항
    if (IsFinished(board, 'o' + 'x' - turn))
        return LOSE;

    // 캐시 확인
    int key = HashKey(board);
    int& ret = TTTcache[key];
    if (ret != DEFAULT)
        return ret;


    // 풀기

    // [.][x][.]
    // [.][o][.]
    // [.][.][.]
    int minValue = DEFAULT;
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (board[y][x] != '.')
                continue;

            // 착수
            board[y][x] = turn;

            // 확인
            minValue = min(minValue, CanWin(board, 'o' + 'x' - turn)); // 상대방이 패배하는게 제일 좋은 케이스

            // 취소
            board[y][x] = '.';
        }
    }

    if (minValue == DRAW || minValue == DEFAULT)
        return ret = DRAW;

    return ret = -minValue; // minValue는 상대의 미래 상태
}

int TIC_TAE_TOE_Test()
{
    board = vector<vector<char>>
    {
        {'.', 'x', 'x'},
        {'.', 'o', '.'},
        {'.', 'o', '.'},
    };

    // 왜 DEFAULT로 설정하는거 memeset을 안쓰느냐?
    //memset(TTTcache, -2, sizeof(TTTcache));(X) // 0b 1111 1110 -> 1byte 단위로 반복적으로 밀기 때문에 이상한 값으로 설정됨
    //memset(TTTcache, 0, sizeof(TTTcache)); (O) // 0b 0000 0000 -> 1byte로 반복적으로 밀어도 상관없음
    //memset(TTTcache, -1, sizeof(TTTcache));(O) // 0b 1111 1111 -> 1byte로 반복적으로 밀어도 상관없음
    for (int i = 0; i < 19683; i++)
        TTTcache[i] = DEFAULT;

    int win = CanWin(board, 'o');

    switch (win)
    {
    case WIN:
        cout << "Win" << endl;
        break;
    case DRAW:
        cout << "Draw" << endl;
        break;
    case LOSE:
        cout << "Lose" << endl;
        break;
    }

    return 0;
}
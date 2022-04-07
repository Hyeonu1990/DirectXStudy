#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;
#include <thread>
#include <windows.h>

// TIC_TAE_TOE
// - �ش� ������ ������(�˰��� ���� �ذ� ����)���� �����Դٰ���

// [ ][ ][ ]
// [ ][O][X]
// [ ][ ][O]

vector<vector<char>> board;
int TTTcache[19683];

bool IsFinished(const vector<vector<char>>& board, char turn)
{
    // �¿�
    for (int i = 0; i < 3; i++)
        if (board[i][0] == turn && board[i][1] == turn && board[i][2] == turn)
            return true;

    // ����
    for (int i = 0; i < 3; i++)
        if (board[0][i] == turn && board[1][i] == turn && board[2][i] == turn)
            return true;

    // �밢��
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
    // 3���� �������� ���
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
    // ���� ����
    if (IsFinished(board, 'o' + 'x' - turn))
        return LOSE;

    // ĳ�� Ȯ��
    int key = HashKey(board);
    int& ret = TTTcache[key];
    if (ret != DEFAULT)
        return ret;


    // Ǯ��

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

            // ����
            board[y][x] = turn;

            // Ȯ��
            minValue = min(minValue, CanWin(board, 'o' + 'x' - turn)); // ������ �й��ϴ°� ���� ���� ���̽�

            // ���
            board[y][x] = '.';
        }
    }

    if (minValue == DRAW || minValue == DEFAULT)
        return ret = DRAW;

    return ret = -minValue; // minValue�� ����� �̷� ����
}

int TIC_TAE_TOE_Test()
{
    board = vector<vector<char>>
    {
        {'.', 'x', 'x'},
        {'.', 'o', '.'},
        {'.', 'o', '.'},
    };

    // �� DEFAULT�� �����ϴ°� memeset�� �Ⱦ�����?
    //memset(TTTcache, -2, sizeof(TTTcache));(X) // 0b 1111 1110 -> 1byte ������ �ݺ������� �б� ������ �̻��� ������ ������
    //memset(TTTcache, 0, sizeof(TTTcache)); (O) // 0b 0000 0000 -> 1byte�� �ݺ������� �о �������
    //memset(TTTcache, -1, sizeof(TTTcache));(O) // 0b 1111 1111 -> 1byte�� �ݺ������� �о �������
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
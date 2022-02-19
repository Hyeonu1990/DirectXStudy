#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	Bfs();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;
	
	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
	Pos pos = _pos; // 시뮬레이션용 좌표
	Pos dest = _board->GetExitPos();

	_path.clear();
	_path.push_back(pos);

	Pos front[4] =
	{
		Pos { -1, 0}, // UP
		Pos { 0, -1}, // LEFT
		Pos { 1, 0}, // DOWN
		Pos { 0, 1}, // RIGHT
	};

	while (pos != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
		int32 newRightDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newRightDir]))
		{
			// 오른쪽 방향으로 90도 회전
			_dir = newRightDir;
			//앞으로 한 보 전진
			pos += front[_dir];

			_path.push_back(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한 보 전진
			pos += front[_dir];

			_path.push_back(pos);
		}
		else
		{
			//왼쪽 방향으로 90도 회전
			_dir = (_dir + 1) % DIR_COUNT;
			// 이동은 안하고 회전만
		}
	}

	// 불필요한 길 거르기
	stack<Pos> s;
	for (int i = 0; i < _path.size() - 1; i++)
	{
		// 막히면 다시 돌아가므로 돌아가는 path들 제거
		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}

	// 목적지 도착
	if (_path.empty() == false)
		s.push(_path.back());

	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	std::reverse(path.begin(), path.end());
	_path = path;
}

void Player::Bfs()
{
	Pos pos = _pos; // 시뮬레이션용 좌표
	Pos dest = _board->GetExitPos();

	_path.clear();
	_path.push_back(pos);

	Pos front[4] =
	{
		Pos { -1, 0}, // UP
		Pos { 0, -1}, // LEFT
		Pos { 1, 0}, // DOWN
		Pos { 0, 1}, // RIGHT
	};

	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false));

	// parent[A] = B; -> A는 B로 인해 발견됨
	map<Pos, Pos> parent;

	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		// 방문
		if (pos == dest)
			break;
		for (int32 dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos + front[dir];

			if (CanGo(nextPos) == false)
				continue;

			if (discovered[nextPos.y][nextPos.x] == true)
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}

	_path.clear();
	while (true)
	{
		_path.push_back(pos);

		if (pos == parent[pos]) // 시작지점이라면
			break;

		pos = parent[pos];
	}
	
	std::reverse(_path.begin(), _path.end());
}

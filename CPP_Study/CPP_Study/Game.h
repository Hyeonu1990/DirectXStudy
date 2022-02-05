#pragma once

// 전방선언
class GPlayer; // 그냥 포인터만 참고할것이기 때문에 굳이 헤더파일 포함할 필요가 없어서 이렇게 구현
class Field;

class Game
{
public:
	Game();
	~Game();

	void Init();
	void Update();
	void CreatePlayer();

private:
	GPlayer* _player;
	Field* _field;
};


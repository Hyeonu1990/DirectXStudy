#pragma once

// ���漱��
class GPlayer; // �׳� �����͸� �����Ұ��̱� ������ ���� ������� ������ �ʿ䰡 ��� �̷��� ����
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


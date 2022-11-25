#pragma once

struct Point {
	int xPos;
	int yPos;
};

enum class Dire { Left, Right, Up, Down };

class CSnake {
public:
	CSnake();
	~CSnake();
	int len;
	Dire head;
	Point body[1500];
	void Init();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
};

#pragma once
#include "MaShape.h"
#include "Ball.h"
class Paddle :public MaShape {
private:
	int score;
	Vector2f hereIStart;
	Font font;
	Ball* ball;
	bool CheckCollision(Ball* b);
public:
	Text text;
	RectangleShape* rect;
	Paddle(Vector2f pos, float thic, float length, Ball* b);
	void Reset();
	void HardReset();
	void SetScore(int value);
	void IncrementScore();
	void Update(float dt, Vector2f vel);
	int GetScore();
	void Win();
	void Loose();
	void Render(RenderWindow* window);
	
};
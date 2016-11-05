#pragma once

#include "Paddle.h"
#include <SFML/Audio.hpp>
#include <iostream>
class Ball :public MaShape {
private:
	CircleShape* circle;
	Vector2f position;
	Texture texture;
	SoundBuffer buf;
	Sound sound;
	float vel;
	Vector2f direction;
public:
	Paddle* p1;
	Paddle* p2;
	float angle = 0.f;
//	float ballSpeed = 100;
	Paddle* brick;


	Ball(Paddle* pad1, Paddle* pad2, Paddle* br);
	void Update(float dt);
	Vector2f getPosition();
	void Render(sf::RenderWindow* wind);
	void Reset();
	void CheckBorders();
	void CheckPaddle(Paddle * p);
	void FlipYVel();
	void FlipXVel();
	Vector2f RandomizeAngle();
};
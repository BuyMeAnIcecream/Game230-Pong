#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
static const float  SCREEN_WIDTH =  800;
static const float  SCREEN_HEIGHT = 600;
static const float PADDLE_THICKNESS = 30.f;
static const float PADDLE_LENGTH = 100.f;
using namespace sf;
class MaShape { //this stuff is here because I want a list of objects in the scene. I wanna loop through them updating and rendering 1by1; but I'm very lazy and I'm loosing faith in this scenario...
public:
	Vector2f velocity;
	virtual void Render(RenderWindow* wind) {};
	virtual void Update(float dt) {};
	
};
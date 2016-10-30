
#include <vector>
#include "Ball.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;
using namespace std;
/*
void updateScene();
void renderFrame();

class Shape {
public:
	struct position {
		float x;
		float y;
	};

	void render() {

	}
};
*/

const float pi = 3.14159f;
class MaShape {
public:
	Vector2f velocity;
	//sf::Vector2f position;

	void Render(RenderWindow* wind) {};
	void Update(float dt) {};
	/*bool CheckCollision(Entity* entity)
	{
		return this->getGlobalBounds().intersects(entity->getGlobalBounds());
	}
	*/
//	void DetectCollision(MaShape* other) {};
};
std::vector <MaShape*> objectsInDaScene;// = new std::vector <MaShape*>;
class Ball:public MaShape {
public:
	float angle = 0.f;
	CircleShape* circle;

	Ball() {
		circle = new sf::CircleShape(10.f);
		circle->setFillColor(sf::Color::Red);
		velocity.y = 1;
		velocity.x = 1;
	}
	void Update(float dt) {
		Vector2f tempPos = circle->getPosition();
		tempPos += velocity*dt;
		circle->setPosition(tempPos);

		float factor = ballSpeed * dt;
		ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);

	//TODO
	//DetectCollision
	}

	void Render(sf::RenderWindow* wind) {
		//wind->draw(circle);
		wind->draw(*circle);
	}
	/*
	Vector2f DetectCollision(Ball* b) {
		b->circle->getPosition();
			return NULL;
	}
	*/

	void RandomizeAngle() {
		do
		{
			// Make sure the ball initial angle is not too much vertical
			angle = (std::rand() % 360) * 2 * pi / 360;
		} while (std::abs(std::cos(angle)) < 0.7f);
	}
};
class Paddle :public MaShape {
private: 
	//float thickness = 30.f, length=100.f;
	
public:
	//float thickness = 30.f, length = 100.f;
	RectangleShape* rect;
	Paddle(Vector2f position, float thic, float length) {
		rect = new sf::RectangleShape(Vector2f(thic, length));
		rect->setFillColor(sf::Color::Blue);
		rect->setPosition(position);

	}
	//suda peredaem speed i obnovlyaem, ok?
	void Update(float dt, Vector2f vel) {//todo if if if if button pressed i tede
		this->velocity = vel;
		
		Vector2f tempPos = rect->getPosition();
		tempPos += velocity*dt;
		if (tempPos.y <= 0 || tempPos.y + rect->getSize().y > 600)
			return;
		rect->setPosition(tempPos);
		cout<<rect->getPosition().y<<endl;
	}

	void Render(RenderWindow* window){
		window->draw(*rect);
	}
};

//class PlayerPaddle:public Paddle {
class Player{
public:
	//using Paddle::Paddle;
	static Vector2f CheckInput() {
	
		if (Keyboard::isKeyPressed(Keyboard::Up)) return Vector2f(0, -200);
		else if(Keyboard::isKeyPressed(Keyboard::Down)) return Vector2f(0, 200);
		else return Vector2f(0, 0);
	}
};

//class AIPaddle {
//public:
	

//}

float screenWidth = 800, screenHeight = 600;
float paddleThickness = 30.f, paddleLength = 100.f;
int main()
{
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");
	Ball* b = new Ball();
	Clock clock;
	//PlayerPaddle* p1 = new PlayerPaddle(Vector2f(200.f, 400.f));
	Paddle* p1 = new Paddle(Vector2f(screenWidth - paddleThickness, screenHeight/2), paddleThickness, paddleLength);
	Paddle* p2 = new Paddle(Vector2f(0, screenHeight / 2), paddleThickness, paddleLength);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//window.draw(shape);
		float dt = clock.restart().asSeconds();
		for each (MaShape* var in objectsInDaScene)
		{
			var->Update(dt);
			var->Render(&window);
		}
		//objectsInDaScene[0]->Update();
		//objectsInDaScene[0]->Render(window);
		b->Update(dt);
		
		p1->Update(dt,Player::CheckInput());
		p2->Update(dt, Vector2f(0,200));
		b->Render(&window);
		p1->Render(&window);
		p2->Render(&window);
		window.display();


	}


	return 0;
}


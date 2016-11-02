
#include <vector>
#include "Ball.h"
#include <random>
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

float screenWidth = 800, screenHeight = 600;
float paddleThickness = 30.f, paddleLength = 100.f;
float paddleSpeed = 300.f;
string ttfPath = "ITCBLKAD.ttf";
Font font;


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
class MaShape { //this stuff is here because I want a list of objects in the scene. I wanna loop through them updating and rendering 1by1; but I'm very lazy and I'm loosing faith in this scenario...
public:
	Vector2f velocity;
	//sf::Vector2f position;

	virtual void Render(RenderWindow* wind) {};
	virtual void Update(float dt) {};
	/*bool CheckCollision(Entity* entity)
	{
		return this->getGlobalBounds().intersects(entity->getGlobalBounds());
	}
	*/
//	void DetectCollision(MaShape* other) {};
};
std::vector <MaShape*> objectsInDaScene;// = new std::vector <MaShape*>;
class Paddle :public MaShape {
private:
	//float thickness = 30.f, length=100.f;

public:
	int score;
	Text text;
	//float thickness = 30.f, length = 100.f;
	RectangleShape* rect;
	Paddle(Vector2f position, float thic, float length) {
		rect = new sf::RectangleShape(Vector2f(thic, length));
		rect->setFillColor(sf::Color::Blue);
		rect->setPosition(position);
		score = 0;
//		Font test;
//		test.loadFromFile("arial.ttf");
	}
	//suda peredaem speed i obnovlyaem, ok?
	void Update(float dt, Vector2f vel) {//todo if if if if button pressed i tede
		this->velocity = vel;

		Vector2f tempPos = rect->getPosition();
		tempPos += velocity*dt;
		if (tempPos.y <= 0 || tempPos.y + rect->getSize().y > 600)
			return;
		rect->setPosition(tempPos);
		//cout << rect->getPosition().y << endl;
		
		
	}

	void Render(RenderWindow* window) {

		window->draw(*rect);
		
		/*
		if(font.loadFromFile("arial.ttf"))
		{
			text.setPosition(0, 0);
			text.setFillColor(Color::Red);
			text.setFont(font);
			text.setCharacterSize(150);
			text.setString("i want to sleep");
		}
		*/
		window->draw(text);
	}
};
class Ball:public MaShape {
public:
	Paddle* p1;
	Paddle* p2;
	float angle = 0.f;
	float ballSpeed = 100;
	CircleShape* circle;

	Ball(Paddle* pad1, Paddle* pad2) {
		circle = new sf::CircleShape(10.f);
		circle->setFillColor(sf::Color::Red);
		circle->setOrigin(Vector2f(circle->getRadius(), circle->getRadius()));
		velocity = RandomizeAngle();
		p1 = pad1;
		p2 = pad2;
		Reset();
		
	}
	void Update(float dt) {
		CheckBorders();
		Vector2f tempPos = circle->getPosition();
		tempPos += velocity*dt;
		circle->setPosition(tempPos);
		CheckPaddle(p1);
		CheckPaddle(p2);
	//TODO
	//DetectCollision
	}

	void Render(sf::RenderWindow* wind) {
		//wind->draw(circle);
		wind->draw(*circle);
	}
	void Reset() {
		circle->setPosition(Vector2f(screenWidth / 2, screenHeight / 2));
	}
	/*
	Vector2f DetectCollision(Ball* b) {
		b->circle->getPosition();
			return NULL;
	}
	*/

	
	void CheckBorders() {
		if (circle->getGlobalBounds().top  <= 0)
			FlipYVel();
		if (circle->getGlobalBounds().top + circle->getGlobalBounds().height >= screenHeight)
			FlipYVel();
		
	}
	
	void CheckPaddle(Paddle * p ) {
		
		if (this->circle->getGlobalBounds().intersects(p->rect->getGlobalBounds())) 	
			{
//			FlipXVel();
//			FlipYVel();
			
			//Vector2f padCenter = Vector2f(p->rect->getPosition().x + paddleLength/2, p->rect->getPosition().x + paddleThickness/2);
			float padCenter = p->rect->getPosition().y  + paddleLength/ 2;
			
			float yDifference = padCenter - this->circle->getPosition().y;
			float yRatio = yDifference / (paddleLength / 2);
			if (yDifference > 0)
				FlipYVel();
			velocity.y *= 2+yRatio;          //It's not exactly how it's supposed to work, but it somehow does..
		    velocity *=  1.1f;
			//cout << "getBallPos: " << yRatio << endl;
			cout << "getPos().y " << this->circle->getPosition().y << endl;
			cout << "padCenter.y " << padCenter << endl;
			cout << "yDIf: " << yDifference << endl;
			cout << "yRat: " << yRatio << endl;
			cout << velocity.x<<endl;
			cout << velocity.y << endl;
			FlipXVel();
	
//			Vector2f padCenter = Vector2f(p->rect->getPosition().x + paddleLength / 2, p->rect->getPosition().x + paddleThickness / 2);

		}
	}
	void FlipYVel() {
		velocity.y = -velocity.y;
	}
	void FlipXVel() {
		velocity.x = -velocity.x;
	}

	Vector2f RandomizeAngle() {
		float Xvel;
		float Yvel;
		Xvel = rand() % (270 - 230 + 1) + 230;
		Yvel = 300 - Xvel;
		if (rand() % 2 > 0) //0or1
			Xvel = -Xvel;
		return Vector2f(Xvel, Yvel);
		
	}
};

class StupidAI {
public:
	static float WhereDoIGo(Ball* b, Paddle* p ) {
		if (b->circle->getPosition().y > p->rect->getPosition().y + paddleLength / 2)
			return paddleSpeed;
		else
			return -paddleSpeed;
	}
};



class Player{ 
public:
	static Vector2f CheckInputP1() {
		if (Keyboard::isKeyPressed(Keyboard::Up)) return Vector2f(0, -paddleSpeed);
		else if(Keyboard::isKeyPressed(Keyboard::Down)) return Vector2f(0, paddleSpeed);
		else return Vector2f(0, 0);
	}
	static Vector2f CheckInputP2() { //There is a nice Command pattern, which I ,sadly,have no time to implement

		if (Keyboard::isKeyPressed(Keyboard::W)) return Vector2f(0, -paddleSpeed);
		else if (Keyboard::isKeyPressed(Keyboard::S)) return Vector2f(0, paddleSpeed);
		else return Vector2f(0, 0);
	}
};


int main()
//static void Main()
{
	
	bool vsAI = true;
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");
	Paddle* p1 = new Paddle(Vector2f(screenWidth - paddleThickness, screenHeight / 2), paddleThickness, paddleLength);
	Paddle* p2 = new Paddle(Vector2f(0, screenHeight / 2), paddleThickness, paddleLength);
	Ball* b = new Ball(p1,p2);
	Clock clock;
	//PlayerPaddle* p1 = new PlayerPaddle(Vector2f(200.f, 400.f));
	
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
		p1->Update(dt, Player::CheckInputP1());
		if(vsAI)p2->Update(dt, Vector2f(0,StupidAI::WhereDoIGo(b, p2)));
		else p2->Update(dt, Player::CheckInputP2());
		b->Render(&window);
		p1->Render(&window);
		p2->Render(&window);
		window.display();


	}


	return 0;
}


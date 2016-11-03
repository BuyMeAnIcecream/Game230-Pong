
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
#include <string>
using namespace sf;
using namespace std;

float screenWidth = 800, screenHeight = 600;
float paddleThickness = 30.f, paddleLength = 100.f;
float paddleSpeed = 300.f;
//string ttfPath = "ITCBLKAD.ttf";

sf::Texture texture;
SoundBuffer buf;
Sound sound;


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
	int score;
	Vector2f hereIStart;
	Font font;
public:
	//int score;
	Text text;
	//float thickness = 30.f, length = 100.f;
	RectangleShape* rect;
	Paddle(Vector2f pos, float thic, float length) {
		rect = new sf::RectangleShape(Vector2f(thic, length));
		rect->setFillColor(sf::Color::Blue);
		hereIStart = pos;
//		score = 0;
//		Font test;
//		test.loadFromFile("arial.ttf");
//		Font font1;
		HardReset();
		font.loadFromFile("arial.ttf");
		text.setFillColor(Color::Red);
		text.setFont(font);
		text.setCharacterSize(50);
		//font.loadFromFile("arial.ttf");
	}

	void Reset() {
		rect->setPosition(hereIStart);
		
	}
	void HardReset() {
		rect->setPosition(hereIStart);
		SetScore(0);
	}
	void SetScore(int value) {
		score = value;
		text.setString(to_string(score));
	}
	void IncrementScore() {
		score++;
		text.setString(to_string(score));
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

	int GetScore() {
		return score;
	}

	void Win() {
		text.setString("Winner");

	}
	void Loose() {
		text.setString("Looser");
	}
	void Render(RenderWindow* window) {

		window->draw(*rect);
		
		
			text.setPosition(rect->getPosition()) ;
			
//			text.setString("i want to sleep");
		
		
		window->draw(text);
	}
};


class Ball:public MaShape {
private:
	CircleShape* circle;
	Vector2f position;
public:
	Paddle* p1;
	Paddle* p2;
	float angle = 0.f;
	float ballSpeed = 100;
	Paddle* brick;
	

	Ball(Paddle* pad1, Paddle* pad2, Paddle* br) {
		circle = new sf::CircleShape(10.f);
		circle->setFillColor(sf::Color::Red);
		circle->setOrigin(Vector2f(circle->getRadius(), circle->getRadius()));
		velocity = RandomizeAngle();
		p1 = pad1;
		p2 = pad2;
		brick = br;
		Reset();
		if (texture.loadFromFile("ball.png")) {
			cout << "ok";
		}
		circle->setTexture(&texture);
		buf.loadFromFile("bounce.ogg");
		sound.setBuffer(buf);
	}
	void Update(float dt) {
		CheckBorders();
		Vector2f tempPos = circle->getPosition();
		tempPos += velocity*dt;
		circle->setPosition(tempPos);
		position = tempPos;
		
		CheckPaddle(p1);
		CheckPaddle(p2);
		CheckPaddle(brick);
	//TODO
	//DetectCollision
	}

	Vector2f getPosition() {
		return circle->getPosition();
	}

	void Render(sf::RenderWindow* wind) {
		//wind->draw(circle);
		wind->draw(*circle);
	}
	void Reset() {
		circle->setPosition(Vector2f(screenWidth / 2, screenHeight / 2));
		velocity = RandomizeAngle();
	}
	/*
	Vector2f DetectCollision(Ball* b) {
		b->circle->getPosition();
			return NULL;
	}
	*/
	
	
	void CheckBorders() {
		if (circle->getGlobalBounds().top <= 0) {
			FlipYVel();
			sound.play();
		}
		if (circle->getGlobalBounds().top + circle->getGlobalBounds().height >= screenHeight) {
			FlipYVel();
			sound.play();
		}
		
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
			sound.play();
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

class GameManager {
public:
	bool pressToRestart;
	Ball* ball;
	Ball* ball2;
	Paddle* pad1;
	Paddle* pad2;
	RenderWindow* window;
	GameManager(Ball* b,Ball*b2, Paddle* p1, Paddle* p2, RenderWindow* win) {
		ball = b;
		ball2 = b2;
		pad1 = p1;
		pad2 = p2;
		window = win;
		pressToRestart = false;
	}
	
	void CheckWin() {

		if (pad1->GetScore() > 4) {
			//pad1->Win();
			//pad2->Loose();
			Text t;
			Font font;
			font.loadFromFile("arial.ttf");
			t.setFillColor(Color::Red);
			t.setFont(font);
			t.setCharacterSize(50);
			t.setPosition(screenWidth / 2, screenHeight / 2);
			t.setString("player2 wins");
			window->draw(t);
			pressToRestart = true;

		}
		if (pad2->GetScore() > 4) {
			//pad2->Win();
			//pad1->Loose();
			Text t;
			Font font;
			font.loadFromFile("arial.ttf");
			t.setFillColor(Color::Red);
			t.setFont(font);
			t.setCharacterSize(50);
			t.setPosition(screenWidth / 2, screenHeight / 2);
			t.setString("player1 wins");
			window->draw(t);
			pressToRestart = true;
		}

	}

	void PreRestart() {
		if (pad1->GetScore() > 4) {
			ball2->Reset();
			ball->Reset();
			pad1->HardReset();
			pad2->HardReset();
			while (!Keyboard::isKeyPressed(Keyboard::Space)) {
				sf::Event event;
				while (window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window->close();
				}
			}
			
			pressToRestart = false;
		}
		if (pad2->GetScore() > 4) {
			ball2->Reset();
			ball->Reset();
			pad1->HardReset();
			pad2->HardReset();
			pressToRestart = false;
			while (!Keyboard::isKeyPressed(Keyboard::Space)) {
				sf::Event event;
				while (window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window->close();
				}
			}
			
		}
	}
	void BallWhereAreYou() {
		if (ball->getPosition().x < 0 || ball2->getPosition().x < 0) {
			cout << ball->getPosition().x<<endl;
			cout << ball2->getPosition().x << endl;
			ball->Reset();
			ball2->Reset();
			pad1->Reset();
			pad2->Reset();
			pad1->IncrementScore();
		}
		if (ball->getPosition().x > screenWidth || ball2->getPosition().x>  screenWidth)
		{
			cout << ball->getPosition().x << endl;
			cout << ball2->getPosition().x << endl;
			ball->Reset();
			ball2->Reset();
			pad1->Reset();
			pad2->Reset();
			pad2->IncrementScore();

		}

	}

	
};
class StupidAI {
public:
	static float WhereDoIGo(Ball* b,Ball* b2, Paddle* p ) {
		if (b->getPosition().x < b2->getPosition().x) {
			if (b->getPosition().y > p->rect->getPosition().y + paddleLength / 2)
				return paddleSpeed;
			else
				return -paddleSpeed;
		}
		else
			if (b2->getPosition().y > p->rect->getPosition().y + paddleLength / 2)
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
	Paddle* brick = new Paddle(Vector2f(screenWidth/1.5, screenHeight / 1.5), paddleThickness, paddleLength);
	Ball* b = new Ball(p1,p2, brick);
	Ball* b2 = new Ball(p1, p2,brick);
	GameManager* gm = new GameManager(b,b2, p1, p2, &window);

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

		
		float dt = clock.restart().asSeconds();
		b->Update(dt);
		b2->Update(dt);
		p1->Update(dt, Player::CheckInputP1());
		if(vsAI)p2->Update(dt, Vector2f(0,StupidAI::WhereDoIGo(b,b2, p2)));
		else p2->Update(dt, Player::CheckInputP2());
		gm->BallWhereAreYou();
		gm->CheckWin();
		b->Render(&window);
		b2->Render(&window);
		p1->Render(&window);
		p2->Render(&window);
		brick->Render(&window);
		
		window.display();
		if (gm->pressToRestart) {
			gm->PreRestart();
			clock.restart().asSeconds();
		}
		
	}


	return 0;
}


#include "Ball.h"
using namespace std;
static const float ballVelocity = 300.f;
static const int BALL_RADIUS = 10;
	Ball::Ball() {
		circle = new sf::CircleShape(BALL_RADIUS);
		circle->setFillColor(sf::Color::Red);
		circle->setOrigin(Vector2f(circle->getRadius(), circle->getRadius()));
//		velocity = RandomizeAngle();
		vel = ballVelocity;
		direction = RandomizeAngle();
		srand(time(NULL));
//		p1 = pad1;
//		p2 = pad2;
//		brick = br;
		Reset();
		texture.loadFromFile("ball.png");
		circle->setTexture(&texture);
		buf.loadFromFile("bounce.ogg");
		sound.setBuffer(buf);
	}
	
	Vector2f Ball::getPosition() {
		return circle->getPosition();
	}
		void Ball::Update(float dt) {
		CheckBorders();
		Vector2f tempPos = getPosition();
		tempPos.x += direction.x*vel*dt;
		tempPos.y += direction.y*vel*dt;
		circle->setPosition(tempPos);
//		position = tempPos;
//		CheckPaddle(p1);
//		CheckPaddle(p2);
//		CheckPaddle(brick);
	}



	void Ball::Render(sf::RenderWindow* wind) {
		wind->draw(*circle);
	}
	void Ball::Reset() {
		circle->setPosition(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		velocity = RandomizeAngle();
	}
	void Ball::CheckBorders() {
		if (circle->getGlobalBounds().top <= 0) {
			FlipYVel();
			sound.play();
		}
		if (circle->getGlobalBounds().top + circle->getGlobalBounds().height >= SCREEN_HEIGHT) {
			FlipYVel();
			sound.play();
		}

	}

	FloatRect Ball::GetGlobalBounds() {
		return circle->getGlobalBounds();
	}
	

	void Ball::BounceOff(float padCenterY) {
//		float padCenter = p->rect->getPosition().y + PADDLE_LENGTH / 2;
//		float padCenter = padCenterY 
		float yDifference = padCenterY - getPosition().y;

		float yRatio = yDifference / (PADDLE_LENGTH / 2);
		direction.y = -yRatio;
		FlipXVel();

		sound.play();
	}

	void Ball::FlipYVel() {
		direction.y = -direction.y;
	}
	void Ball::FlipXVel() {
		direction.x = -direction.x;
	}

	Vector2f Ball::RandomizeAngle() {
		float Xvel;
		float Yvel;
		Xvel = rand() % (90 - 70 + 1) + 70;
		Yvel = 100 - Xvel;
		if (rand() % 2 > 0) //0or1
			Xvel = -Xvel;
//		cout << Xvel/100.f << " " << Yvel/100.f;
		return Vector2f(Xvel/100.f, Yvel/100.f);

	}

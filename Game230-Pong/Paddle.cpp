#include "Paddle.h"
using namespace std;

	Paddle::Paddle(Vector2f pos, float thic, float length) {
		rect = new sf::RectangleShape(Vector2f(thic, length));
		rect->setFillColor(sf::Color::Blue);
		hereIStart = pos;
		HardReset();
		font.loadFromFile("arial.ttf");
		text.setFillColor(Color::Red);
		text.setFont(font);
		text.setCharacterSize(50);
	}

	void Paddle::Reset() {
		rect->setPosition(hereIStart);

	}
	void Paddle::HardReset() {
		rect->setPosition(hereIStart);
		SetScore(0);
	}
	void Paddle::SetScore(int value) {
		score = value;
		text.setString(to_string(score));
	}
	void Paddle::IncrementScore() {
		score++;
		text.setString(to_string(score));
	}

	void Paddle::Update(float dt, Vector2f vel) {//todo if if if if button pressed i tede
		this->velocity = vel;
		Vector2f tempPos = rect->getPosition();
		tempPos += velocity*dt;
		if (tempPos.y <= 0 || tempPos.y + rect->getSize().y > 600)
			return;
		rect->setPosition(tempPos);
	}

	int Paddle::GetScore() {
		return score;
	}

	void Paddle::Win() {
		text.setString("Winner");
	}
	void Paddle::Loose() {
		text.setString("Looser");
	}
	void Paddle::Render(RenderWindow* window) {
		window->draw(*rect);
		text.setPosition(rect->getPosition());
		window->draw(text);
	}
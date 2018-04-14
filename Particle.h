#pragma once

class Particle
{
public:

	sf::Time lifeTime;
	sf::Vector2f velocity;

	sf::Vector2f size;
	sf::Vector2f endSize;
	float availableAngle;

	sf::RectangleShape body;

	Particle();
	void Reset();
	
};

Particle::Particle()
{
	Reset();
	size = sf::Vector2f(1, 1);
	endSize = sf::Vector2f(5, 5);
	body.setSize(size);
	availableAngle = 1;



	//body.setPrimitiveType(sf::Quads);
	//body.resize(4);

	//body[0].texCoords = sf::Vector2f(0, 0);
	//body[1].texCoords = sf::Vector2f(25, 0);
	//body[2].texCoords = sf::Vector2f(25, 50);
	//body[3].texCoords = sf::Vector2f(0, 50);

	//body[0].color = sf::Color::White;
	//body[1].color = sf::Color::White;
	//body[2].color = sf::Color::White;
	//body[3].color = sf::Color::White;
}

void Particle::Reset()
{
	body.setSize(size);
	float angle = ((std::rand() % 360) * 3.14 / 180) * availableAngle;
	//float speed = (std::rand() % 50) + 50.f;
	float speed = 1;

	velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	lifeTime = sf::milliseconds((std::rand() % 2000) + 1000);

	//std::cout << lifeTime.asSeconds() << std::endl;


}
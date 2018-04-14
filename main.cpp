#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include "ParticleSystem.h"
#include "Particle.h"


using namespace std;

sf::Texture particleTexture;

sf::Text particleOneText;
sf::Text particleTwoText;
sf::Text particleThreeText;

int main()
{

	sf::RenderWindow window(sf::VideoMode(1200, 400), "Particles");

	ParticleSystem particleSystemOne(1000, true, false, false);
	ParticleSystem particleSystemTwo(1000, false, true, false);
	ParticleSystem particleSystemThree(1000, false, false, true);

	particleSystemOne.SetEmitter(sf::Vector2f(200, 200));     //I was originally going to hold all particles systems in a vector, and for any operations needed I would
	particleSystemTwo.SetEmitter(sf::Vector2f(600, 200));     //loop through said vector, but I found that this approach slowed down the program quite a bit
	particleSystemThree.SetEmitter(sf::Vector2f(1000, 200));

	sf::Clock clock;

	particleTexture.loadFromFile("bork.png");

	cout << particleSystemOne.emitter.x << ", " << particleSystemOne.emitter.y << endl;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		sf::Time elapsed = clock.restart();
		particleSystemOne.Update(elapsed);
		particleSystemTwo.Update(elapsed);
		particleSystemThree.Update(elapsed);

		for (int i = 0; i < particleSystemOne.particles.size(); i++)
		{
			particleSystemOne.particles[i].body.setPosition(
				particleSystemOne.particles[i].body.getPosition().x + particleSystemOne.particles[i].velocity.x,
				particleSystemOne.particles[i].body.getPosition().y + particleSystemOne.particles[i].velocity.y
			);
		}

		for (int i = 0; i < particleSystemTwo.particles.size(); i++)
		{
			particleSystemTwo.particles[i].body.setPosition(
				particleSystemTwo.particles[i].body.getPosition().x + particleSystemTwo.particles[i].velocity.x,
				particleSystemTwo.particles[i].body.getPosition().y + particleSystemTwo.particles[i].velocity.y
			);
		}

		for (int i = 0; i < particleSystemThree.particles.size(); i++)
		{
			particleSystemThree.particles[i].body.setPosition(
				particleSystemThree.particles[i].body.getPosition().x + particleSystemThree.particles[i].velocity.x,
				particleSystemThree.particles[i].body.getPosition().y + particleSystemThree.particles[i].velocity.y
			);
		}

		//Input for increasing/decreasing amount of particles

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{

			Particle* p = new Particle();
			p->body.setPosition(particleSystemOne.emitter);
			particleSystemOne.particles.push_back(*p);

			p = new Particle();
			p->body.setPosition(particleSystemTwo.emitter);
			particleSystemTwo.particles.push_back(*p);

			p = new Particle();
			p->body.setPosition(particleSystemThree.emitter);
			particleSystemThree.particles.push_back(*p);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{

			for (int i = 0; i < 5; i++)
			{
				particleSystemOne.particles.pop_back();
				particleSystemTwo.particles.pop_back();
				particleSystemThree.particles.pop_back();
			}
		}

		//Input for adjusting emmission angle

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			cout << "Angle Up" << endl;
			particleSystemOne.AdjustAngle(.01);
			particleSystemTwo.AdjustAngle(.01);
			particleSystemThree.AdjustAngle(.01);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{

			cout << "Angle Down" << endl;
			particleSystemOne.AdjustAngle(-.01);
			particleSystemTwo.AdjustAngle(-.01);
			particleSystemThree.AdjustAngle(-.01);

		}

		window.clear(sf::Color::Blue);
		
		for (int i = 0; i < particleSystemOne.particles.size(); i++)
		{
			particleSystemOne.particles[i].body.setTexture(&particleTexture);
			window.draw(particleSystemOne.particles[i].body);
		}

		for (int i = 0; i < particleSystemTwo.particles.size(); i++)
		{
			particleSystemTwo.particles[i].body.setTexture(&particleTexture);
			window.draw(particleSystemTwo.particles[i].body);
		}

		for (int i = 0; i < particleSystemThree.particles.size(); i++)
		{
			particleSystemThree.particles[i].body.setTexture(&particleTexture);
			window.draw(particleSystemThree.particles[i].body);
		}

		window.display();
	}

	return 0;
}
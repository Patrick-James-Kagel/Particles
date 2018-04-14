#pragma once

#include <vector>

#include "Particle.h"

class ParticleSystem
{

public:

	std::vector<Particle> particles;
	sf::Vector2f emitter;

	bool linearGrow;
	bool linearShrink;
	bool linearAccelerate;

	float emmissionAngle;

	ParticleSystem();
	ParticleSystem(unsigned int count, bool p_linearGrow, bool p_linearShrink, bool p_linearAccelerate);
	~ParticleSystem();

	float sizeOverLifetimeMultiplier;
	int sizeCounter;

	void SetEmitter(sf::Vector2f position);
	void AdjustAngle(float amount);
	void Update(sf::Time elapsed);

};

//////////////Constructors, Destructor//////////////////////
ParticleSystem::ParticleSystem()
{

}

ParticleSystem::ParticleSystem(unsigned int count, bool p_linearGrow, bool p_linearShrink, bool p_linearAccelerate)
{
	std::cout << "System made" << std::endl;

	sizeOverLifetimeMultiplier = 1;
	sizeCounter = 0;

	emmissionAngle = 1;

	linearGrow = p_linearGrow;
	linearShrink = p_linearShrink;
	linearAccelerate = p_linearAccelerate;

	Particle* p;

	for (int i = 0; i < count; i++)
	{
		p = new Particle();

		if (linearShrink)
		{
			p->size = sf::Vector2f(50, 50);
			p->endSize = sf::Vector2f(1, 1);
		}
		else if (linearGrow)
		{
			p->size = sf::Vector2f(1, 1);
			p->endSize = sf::Vector2f(50, 50);
		}

		particles.push_back(*p);
	}

	SetEmitter(sf::Vector2f(0, 0));

}

ParticleSystem::~ParticleSystem()
{

}

//////////////Other Methods/////////////////////////
void ParticleSystem::SetEmitter(sf::Vector2f position)
{
	emitter = position;
}

void ParticleSystem::AdjustAngle(float amount)
{
	emmissionAngle += amount;

	if (emmissionAngle > 1)
		emmissionAngle = 1;

	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].availableAngle = emmissionAngle;
	}
}

void ParticleSystem::Update(sf::Time elapsed)
{

	std::cout << "Update" << std::endl;

	for (int i = 0; i < particles.size(); i++)
	{
		Particle& p = particles[i];
		p.lifeTime -= elapsed;
			
		if (linearGrow)
		{
			p.body.setSize(sf::Vector2f(p.body.getSize().x + .5f, p.body.getSize().y + .5f));

			if (p.body.getSize().x >= p.endSize.x)
			{
				p.body.setPosition(emitter);
				p.Reset();
			}
		}
		else if (linearShrink)
		{
			p.body.setSize(sf::Vector2f(p.body.getSize().x - .5f, p.body.getSize().y - .5f));

			if (p.body.getSize().x <= p.endSize.x)
			{
				p.body.setPosition(emitter);
				p.Reset();
			}
		}
		else if (linearAccelerate)
		{
			p.body.setSize(sf::Vector2f(10, 10));
			p.velocity = (sf::Vector2f(p.velocity.x * 1.02, p.velocity.y * 1.02));
		}

		if (p.lifeTime <= sf::Time::Zero)
		{
			p.body.setPosition(emitter);
			p.Reset();
		}

		if (pow(((p.body.getPosition().x - emitter.x) * (p.body.getPosition().x - emitter.x)) + ((p.body.getPosition().y - emitter.y) * (p.body.getPosition().y - emitter.y)), 0.5) > 200)
		{
			p.body.setPosition(emitter);
			p.Reset();
		}
	}
}

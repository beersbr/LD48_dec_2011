#ifndef _alone_particle_
#define _alone_particle_

#include <cmath>
#include <iostream>
#include "entity.h"

const double PI = 3.14159;

class Particle : public Entity{
public:
	Particle();
	Particle(double _x, double _y, int _dir, double _speed, int _ttl, sf::Color _c);

	int Draw(sf::RenderWindow *rt);
	int Update();

protected:
	sf::Shape sh;
	sf::Color c;
	double speed;
	int ttl;
	int direction;
};

class ParticleHandler : public Entity{
public:
	ParticleHandler();
	ParticleHandler(int _x, int _y, double _speed, int _size, int _direction, int ttl, sf::Color _c);

	~ParticleHandler();

	int Draw(sf::RenderWindow *rt);
	int Update();

	int Start();
	int Stop();

private:
	int size;
	int direction;
	double speed;
	int ttl;
	sf::Color c;

	std::vector<Particle*> particles;
};

#endif
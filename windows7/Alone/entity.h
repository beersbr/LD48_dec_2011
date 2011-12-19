#ifndef _alone_entity_
#define _alone_entity_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Entity{
public:
	Entity();
	virtual ~Entity();

	virtual int Draw(sf::RenderWindow *rt);
	virtual int Update();
	virtual bool operator==(const Entity *ent);

	double x, y;
	double vx, vy;
	int w, h;
};

#endif
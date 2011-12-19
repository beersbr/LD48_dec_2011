#include "entity.h"

Entity::Entity(){
	x = 0, y = 0, w = 0, h = 0;
	vx = 0.0, vy = 0.0;
}

Entity::~Entity(){
	x = 0, y = 0, w = 0, h = 0;
	vx = 0.0, vy = 0.0;
}

int Entity::Draw(sf::RenderWindow *rt){
	return 0;
}

int Entity::Update(){
	return 0;
}

bool Entity::operator==(const Entity *ent){
	
	if(this != ent)
		return false;
	return true;
}
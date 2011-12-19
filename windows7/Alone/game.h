#ifndef _alone_game_
#define _alone_game_

#include "entity.h"
#include <vector>
#include <cstring>
#include <iostream>

class Warden{
public:
	Warden();

	int UpdateEntities();
	int DrawEntities(sf::RenderWindow *rt);

	int AddEntity(Entity *ent);
	int RemoveEntity(Entity *ent);

	int TagImage(std::string tag, std::string image_name);
	int LoadImages();
	sf::Image *GetImage(std::string tag);

	int Clear();

private:

	std::map<std::string, std::string> toLoad;

	std::vector<Entity*> entities;
	std::map<std::string, sf::Image> images;
};

#endif
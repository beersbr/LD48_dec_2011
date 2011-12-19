#ifndef _alone_block_
#define _alone_block_

#include "entity.h"

const int SOFT = 0;
const int HARD = 1;
const int POWER = 2;
const int EMPTY = 3;

class Block : public Entity{
public:
	Block();
	Block(int _x, int _y, sf::Image *im, int type, bool vis = false);
	~Block();

	int Draw(sf::RenderWindow *rt);
	int Update();

	static int Clean();
	int type;
	bool visible;

private:
	sf::Sprite block_sprite;
};

#endif


#ifndef _alone_player_
#define _alone_player_

#include "entity.h"
#include "block.h"
#include "point.h"

#include <iostream>
#include <map>
#include <vector>

const int DOWN  = 0;
const int UP    = 1;
const int RIGHT = 2;
const int LEFT  = 3;

class Player : public Entity{
public:
	Player();
	Player(double x, double y, sf::Image *_player_image, sf::Image *_attack_image);

	int Draw(sf::RenderWindow *rt);
	int Update();

	int Attack();
	std::vector<Block*> GenerateMap(sf::Image* _level, sf::Image *_block_image, sf::Image *_wall_image, sf::Image *_start, sf::Image *_end, sf::Image *_power);

	int GetDirection();
	int Die();

	int GetHitsLeft();
	int Win();

private:
	sf::Sprite player_sprite;
	sf::IntRect frames[4];

	sf::Sprite attack_sprite;

	int levelWon;
	int hitsLeft;

	int tileX;
	int tileY;

	double friction;
	int isMoving;
	int isAttacking;
	int atkCounter;
	int attacked;

	bool countFrame;
	int dirFacing;

	aPoint start;
	aPoint end;

	std::vector<std::vector<Block*> > gameMap;
};

#endif
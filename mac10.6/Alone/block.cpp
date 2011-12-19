#include "block.h"

Block::Block(){
}

Block::Block(int _x, int _y, sf::Image *im, int _type, bool vis){
	this->x = _x;
	this->y = _y;
	this->w = 40;
	this->h = 40;

	this->visible = vis;
	this->type = _type;

	block_sprite.SetPosition(this->x, this->y);
	if(im)
		block_sprite.SetImage(*im);
}

Block::~Block(){
}

int Block::Draw(sf::RenderWindow *rt){
	if(visible && type != EMPTY)
		rt->Draw(block_sprite);

	return 0;
}

int Block::Update(){
	return 0;
}
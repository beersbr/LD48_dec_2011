#include "player.h"

Player::Player():Entity(){
}

Player::Player(double _x, double _y, sf::Image *_player_image, sf::Image *_attack_image){
	this->x = _x;
	this->y = _y;

	this->tileY = (int)this->y/40;
	this->tileX = (int)this->x/40;

	this->vx = 0;
	this->vy = 0;
	this->friction = 0.79;
	this->isMoving = false;
	this->isAttacking = false;
	this->atkCounter = 0;
	this->attacked = false;
	this->countFrame = false;
	this->dirFacing = DOWN;

	this->hitsLeft = 50;
	this->levelWon = false;

	this->w = 40;
	this->h = 40;

	frames[DOWN]  = sf::IntRect(w*DOWN, 0, w*DOWN+w, h);
	frames[UP]    = sf::IntRect(w*UP, 0, w*UP+w, h);
	frames[RIGHT] = sf::IntRect(w*RIGHT, 0, w*RIGHT+w, h);
	frames[LEFT]  = sf::IntRect(w*LEFT, 0, w*LEFT+w, h);

	player_sprite.SetImage(*_player_image);
	attack_sprite.SetImage(*_attack_image);

	player_sprite.SetSubRect(frames[DOWN]);
	player_sprite.SetPosition((float)this->x-20, (float)this->y-20);
}

int Player::Draw(sf::RenderWindow *rt){
	switch(dirFacing){
	case DOWN:
		player_sprite.SetSubRect(frames[DOWN]);
		break;
	case UP:
		player_sprite.SetSubRect(frames[UP]);
		break;
	case RIGHT:
		player_sprite.SetSubRect(frames[RIGHT]);
		break;
	case LEFT:
		player_sprite.SetSubRect(frames[LEFT]);
		break;
	}

	if(dirFacing != UP)
		rt->Draw(player_sprite);

	if(isAttacking){
		attack_sprite.SetPosition((float)this->x-40, (float)this->y-20);

		if(dirFacing == RIGHT)
			attack_sprite.SetPosition((float)this->x-11, (float)this->y-20);

		sf::IntRect r(atkCounter*w, 0, atkCounter*w+w, h);
		attack_sprite.SetSubRect(r);

		if(countFrame){
			atkCounter += 1;
		}

		countFrame = !countFrame;

		rt->Draw(attack_sprite);

		if(atkCounter == 4) isAttacking = false;
	}

	if(dirFacing == UP)
		rt->Draw(player_sprite);

	return 0;
}

int Player::Update(){
	this->isMoving = false;

	this->x += this->vx;
	this->y += this->vy;

	this->vx *= this->friction;
	this->vy *= this->friction;

	if(this->x < 0 || this->x > 800)
		(*this).Die();

	if(this->y < 0 || this->y > 800)
		(*this).Die();


	if(abs(vx) < 0.01) vx = 0;
	if(abs(vy) < 0.01) vy = 0;
	
	this->tileX = floor(x/40.0);
	this->tileY = floor(y/40.0);

	if(abs(this->vy) > 0.3 || abs(this->vx) > 0.3){
		if(abs(this->vx) > abs(this->vy)){
			this->dirFacing = (this->vx >= 0) ? RIGHT : LEFT;
		}else{
			this->dirFacing = (this->vy >= 0) ? DOWN : UP;
		}
		this->isMoving = true;
	}

	//std::cout << gameMap[tileY][tileX].type << std::endl;
	if(gameMap[tileY][tileX]->type == EMPTY || gameMap[tileY][tileX]->visible == false){
		(*this).Die();
	}

	if(this->attacked){
		switch(this->dirFacing){
		case UP:
			if(tileY-1 >= 0){
			switch(gameMap[tileY-1][tileX]->type){
				case SOFT:
					gameMap[tileY-1][tileX]->visible = true;
					break;
				case HARD:
					gameMap[tileY-1][tileX]->visible = true;
					this->hitsLeft--;
					break;
				case POWER:
					gameMap[tileY-1][tileX]->visible = true;
					this->hitsLeft+=20;
					break;
				}
			}
			break;
		case DOWN:
			if(tileY+1 < 15){
			switch(this->gameMap[tileY+1][tileX]->type){
				case SOFT:
					gameMap[tileY+1][tileX]->visible = true;
					break;
				case HARD:
					gameMap[tileY+1][tileX]->visible = true;
					this->hitsLeft--;
					break;
				case POWER:
					gameMap[tileY+1][tileX]->visible = true;
					this->hitsLeft+=20;
					break;
				}
			}
			break;
		case LEFT:
			if(tileX-1 >= 0){
			switch(gameMap[tileY][tileX-1]->type){
				case SOFT:
					gameMap[tileY][tileX-1]->visible = true;
					break;
				case HARD:
					gameMap[tileY][tileX-1]->visible = true;
					this->hitsLeft--;
					break;
				case POWER:
					gameMap[tileY][tileX-1]->visible = true;
					this->hitsLeft+=20;
					break;
				}
			}
			break;
		case RIGHT:
			if(tileX+1 < 20){
				switch(gameMap[tileY][tileX+1]->type){
				case SOFT:
					gameMap[tileY][tileX+1]->visible = true;
					break;
				case HARD:
					gameMap[tileY][tileX+1]->visible = true;
					this->hitsLeft--;
					break;
				case POWER:
					gameMap[tileY][tileX+1]->visible = true;
					this->hitsLeft+=20;
					break;
				}
			}
			break;
		}
		attacked = false;
	}

	if(this->tileX == end.x && this->tileY == end.y){
		this->levelWon = true;
	}

	player_sprite.SetPosition((float)this->x-25, (float)this->y-30);
	return 0;
}

int Player::Attack(){
	if(this->hitsLeft == 0) return 1;
	if(this->isAttacking) return 1;
	this->hitsLeft -= 1;
	this->atkCounter = 0;
	this->attacked = true;
	this->isAttacking = true;

	return 1;
}

int Player::GetDirection(){
	return this->dirFacing;
}

std::vector<Block*> Player::GenerateMap(sf::Image* _level, sf::Image* _block_image, sf::Image* _wall_image, sf::Image *_start, sf::Image *_end, sf::Image* _power){
	int mw = 800/40;
	int mh = 600/40;

	this->hitsLeft = 50;
	this->levelWon = false;

	std::vector<Block*> blocks;
	sf::Color c;
	aPoint p;

	gameMap.resize(static_cast<int>(_level->GetHeight()));
	for(int height = 0; height < static_cast<int>(_level->GetHeight()); height++){

		gameMap[height].resize(static_cast<int>(_level->GetWidth()));

		for(int width = 0; width < static_cast<int>(_level->GetWidth()); width++){
			
			c = _level->GetPixel(width, height);
			p.x = width; p.y = height;
			
			gameMap[height][width] = new Block(width*40, height*40, NULL, EMPTY);

			if(c == sf::Color(255, 255, 255)){
				
				gameMap[height][width] = new Block(width*40, height*40, _block_image, SOFT);
				blocks.push_back(gameMap[height][width]);
			}
			if(c == sf::Color(0, 0, 255)){
				new Block(width*40, height*40, _wall_image, HARD);

				gameMap[height][width] = new Block(width*40, height*40, _wall_image, HARD);
				blocks.push_back(gameMap[height][width]);
			}
			if(c == sf::Color(0, 255, 0)){
				//Block b = Block(width*40, height*40, _start, SOFT, true);
				this->x = width*40 +20; 
				this->y = height*40 +20;

				start.x = width*40+20;
				start.y = height*40+20;

				gameMap[height][width] = new Block(width*40, height*40, _start, SOFT, true);
				blocks.push_back(gameMap[height][width]);
			}
			if(c == sf::Color(255, 0, 0)){
				//Block b(width*40, height*40, _end, SOFT, true);

				end.x = width;
				end.y = height;

				gameMap[height][width] = new Block(width*40, height*40, _end, SOFT, true);
				blocks.push_back((gameMap[height][width]));
			}
			if(c == sf::Color(255, 255, 0)){
				//Block b(width*40, height*40, _end, SOFT, true);

				gameMap[height][width] = new Block(width*40, height*40, _power, POWER, true);
				blocks.push_back((gameMap[height][width]));
			}


		}
	}

	return blocks;
}

int Player::Die(){
	(*this).x = (*this).start.x;
	(*this).y = (*this).start.y;
	(*this).hitsLeft = (*this).hitsLeft + 10;
	return 1;
}

int Player::GetHitsLeft(){
	return this->hitsLeft;
}

int Player::Win(){
	return levelWon;
}
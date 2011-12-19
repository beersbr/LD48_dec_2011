#include "particle.h"

Particle::Particle():Entity(){
}

Particle::Particle(double _x, double _y, int _dir, double _speed, int _ttl, sf::Color _c):Entity(){
	c = _c;
	sh = sf::Shape::Rectangle((float)x-1, (float)y-1, (float)x+1, (float)y+1, c);
	this->ttl = _ttl+rand()%100; this->ttl = (this->ttl < 0)? this->ttl * -1: this->ttl;
	this->x = _x;
	this->y = _y;
	this->direction = _dir;
	this->speed = _speed;
	this->vx = cos(this->direction * PI/180) * this->speed; // this->speed;
	this->vy = sin(this->direction * PI/180) * this->speed; // this->speed;
}

int Particle::Draw(sf::RenderWindow *rt){
	rt->Draw(sh);
	return 0;
}

int Particle::Update(){
	if(this->ttl--){
		this->x += this->vx;
		this->y += this->vy;

		this->sh = sf::Shape::Rectangle((float)x-2, (float)y-2, (float)x+2, (float)y+2, c);
		return 1;
	}
	return 0;
}

// ParticleHandler
ParticleHandler::ParticleHandler(){

}

ParticleHandler::~ParticleHandler(){

}

ParticleHandler::ParticleHandler(int _x, int _y, double _speed, int _size, int _direction, int _ttl, sf::Color _c){
	this->size = _size;
	this->direction = _direction;
	this->ttl = _ttl;
	this->x = _x;
	this->y = _y;
	this->speed = _speed;
	int r = 0;
	this->c = _c;

	for(int i = 0; i < this->size; i++){
		r = rand()%360;
		this->particles.push_back(new Particle(this->x, this->y, this->direction+r, this->speed, this->ttl, this->c));
	}
}

int ParticleHandler::Draw(sf::RenderWindow *rt){
	std::vector<Particle*>::iterator it = this->particles.begin();
	for(it; it < particles.end(); it++){
		(*it)->Draw(rt);
	}
	return 0;
}

int ParticleHandler::Update(){
	std::vector<Particle*>::iterator it = this->particles.begin();
	int r = 0;
	int cmod = rand()%255;
	sf::Color tc = sf::Color((c.r+cmod)%255, (c.g+cmod)%255, (c.b+cmod)%255, 100);
	for(it; it < particles.end(); it++){
		if(!((*it)->Update())){
			r = rand()%360;
			this->particles.erase(it);
			this->particles.push_back(new Particle(this->x, this->y, this->direction+r, this->speed, this->ttl, tc));
		}
	}
	return 0;
}
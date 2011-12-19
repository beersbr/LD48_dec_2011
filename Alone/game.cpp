#include "game.h"

Warden::Warden(){
}

int Warden::UpdateEntities(){
	std::vector<Entity*>::iterator it;
	it = this->entities.begin();

	for(it; it < this->entities.end(); it++){
		(*it)->Update();
	}

	return 0;
}

int Warden::DrawEntities(sf::RenderWindow *rt){
	std::vector<Entity*>::iterator it;
	it = this->entities.begin();

	for(it; it < this->entities.end(); it++){
		(*it)->Draw(rt);
	}

	return 0;
}

int Warden::AddEntity(Entity *ent){
	this->entities.push_back(ent);
	return 0;
}

int Warden::RemoveEntity(Entity *ent){

	std::vector<Entity*>::iterator it = entities.begin();
	for(it; it < entities.end(); it++){
		if((*it) == ent){
			this->entities.erase(it);
			return 1;
		}
	}
	return 0;
}

int Warden::TagImage(std::string tag, std::string image_name){
	this->toLoad[tag] = image_name;
	return 0;
}

int Warden::LoadImages(){
	std::map<std::string, std::string>::iterator it = toLoad.begin();
	for(it; it != toLoad.end(); it++){

		std::cout << "Loading image: " << (*it).first << "(" << (*it).second << ")";
		if(!this->images[(*it).first].LoadFromFile((*it).second)){
			std::cout << "could not load file: " << (*it).second << std::endl;
			this->images.erase(it->first);
		};
		std::cout << " done." << std::endl;
	}

	return toLoad.size();
}

sf::Image* Warden::GetImage(std::string tag){
	return &(this->images[tag]);
}

int Warden::Clear(){
	this->entities.clear();
	return 0;
}
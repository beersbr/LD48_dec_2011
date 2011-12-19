#include "keyhandler.h"

KeyHandler::KeyHandler(){

}

int KeyHandler::UpdateEvents(sf::Event e){
	if(e.Type == sf::Event::KeyPressed){
		this->keys[e.Key.Code] = 1;
	}
	else if(e.Type == sf::Event::KeyReleased){
		this->keys[e.Key.Code] = 0;
	}
	return 0;
}

int KeyHandler::KeyIsDown(sf::Key::Code k){
	return keys[k];
}
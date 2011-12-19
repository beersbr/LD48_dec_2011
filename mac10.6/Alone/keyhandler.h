#ifndef _alone_keyhandler_
#define _alone_keyhandler_

#include <map>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class KeyHandler{
public:
	KeyHandler();

	int UpdateEvents(sf::Event e);
	int KeyIsDown(sf::Key::Code k);

private:
	std::map<sf::Key::Code, int> keys;

};

#endif
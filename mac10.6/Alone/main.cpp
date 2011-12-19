// NOTES:

/*

 mouse shoots light accross screen revealing path. Have to get to the finish point without running out of time
 10 levels. the light has a longer cooldown the more you use it. the cooldown shortens to a certain point.

*/

#include "keyhandler.h"
#include "entity.h"
#include "particle.h"
#include "game.h"
#include "player.h"
#include "block.h"
#include <cstdlib>

#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(){
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Alone");
	App.SetFramerateLimit(30);
	sf::Event Event;

	KeyHandler kh;
	int playing = true;
	float Framerate = 0.0;

	Warden warden;
	warden.TagImage("player", "../alone_assets/player_map.png");
	warden.TagImage("attack", "../alone_assets/attack_map.png");
	warden.TagImage("bg",	  "../alone_assets/background.png");
	warden.TagImage("block",  "../alone_assets/block.png");
	warden.TagImage("wall",   "../alone_assets/block_wall.png");
	warden.TagImage("start",  "../alone_assets/start.png");
	warden.TagImage("end",    "../alone_assets/end.png");
	warden.TagImage("power",  "../alone_assets/power.png");
	warden.TagImage("level1", "../alone_assets/level1.bmp");
	warden.TagImage("level2", "../alone_assets/level2.bmp");
	warden.LoadImages();

	Player p(400, 300, warden.GetImage("player"), warden.GetImage("attack"));
	std::vector<Block*> blocks = p.GenerateMap(warden.GetImage("level1"), warden.GetImage("block"), warden.GetImage("wall"), warden.GetImage("start"), warden.GetImage("end"), warden.GetImage("power"));

	std::vector<Block*>::iterator it = blocks.begin();
	for(it; it != blocks.end(); it++){
		warden.AddEntity((*it));
	}

	warden.AddEntity(&p);

	sf::Sprite bg; bg.SetImage(*warden.GetImage("bg"));
	sf::String hits;
	hits.SetPosition(720, 1);
	char str[3];

	while(playing){
		Framerate = 1.f / App.GetFrameTime();
		//std::cout << Framerate << "\r";
		//hits.SetText(itoa(p.GetHitsLeft(), str, 10));

		while(App.GetEvent(Event)){
			kh.UpdateEvents(Event);
		}

		if(kh.KeyIsDown(sf::Key::W)){
			p.vy -= 1.3;
		}
		if(kh.KeyIsDown(sf::Key::A)){
			p.vx -= 1.3;
		}
		if(kh.KeyIsDown(sf::Key::S)){
			p.vy += 1.3;
		}
		if(kh.KeyIsDown(sf::Key::D)){
			p.vx += 1.3;
		}
		if(kh.KeyIsDown(sf::Key::J)){
			p.Attack();
		}

		if(kh.KeyIsDown(sf::Key::Escape)){
			playing = false;
		}

		if(p.Win()){
			blocks.clear();
			warden.Clear();
			blocks = p.GenerateMap(warden.GetImage("level2"), warden.GetImage("block"), warden.GetImage("wall"), warden.GetImage("start"), warden.GetImage("end"), warden.GetImage("power"));
			for(it = blocks.begin(); it != blocks.end(); it++){
				warden.AddEntity((*it));
			}
			warden.AddEntity(&p);

		}

		warden.UpdateEntities();

		//App.Clear(sf::Color(0, 0, 0));
		App.Draw(bg);
		warden.DrawEntities(&App);
		App.Draw(hits);
		App.Display();
	}

	App.Close();

	return EXIT_SUCCESS;
}
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "background.hh"


void Background::Update(float dt)
{
	extern float difficulty;
	cRect.y = 0;
	frameCounter += dt;
	
	//Plus la difficulté , plus l'arrière plan va vite... Cependant, il faut limiter la vitesse pour pas qu'elle devienne infinie
	float updater = 0.1f - (difficulty/5000.0); 
	if  (updater < 0.01f){
		updater = 0.01f;
	}

	//Partie Scroll
	if(frameCounter >= updater)
	{
		frameCounter = 0;
		cRect.x += 1; //On scroll l'arriere plan
		if(cRect.x >= textureWidth){
			cRect.x = 0; //On retourne au frame initial en cas de deoassement
		}
	}

}

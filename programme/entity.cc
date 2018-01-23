#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "entity.hh"
#include "sound.hh"


Entity::Entity(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY){

	//On génère la Texture du personnage
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if (surface == NULL){
		std::cout <<"ERREUR !"<<std::endl;	
	}
	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_FreeSurface(surface);

	//On va ensuite obtenir le rect de la texture
	SDL_QueryTexture(texture, NULL, NULL, &cRect.w, &cRect.h);

	//Traitement de l'image source des texture pour la subdiviser en petite image CF RAPPORT pour explication
	textureWidth = cRect.w;
	posX = x;  //postion initiale X de l'image
	posY = y;
	cRect.w /= framesX; //framesX est le nombres de frames X dans l'image source
	cRect.h /= framesY;
	frameWidth = posRect.w = cRect.w; //taille d'un frame après subdivision par frameX et definition de la position du rect
	frameHeight = posRect.h = cRect.h;
	cRect.x = 0;
	cRect.y = 0;
	frameCounter = 0.0f;
	isEnabled = true;
	//definition de la move speed
	moveSpeed = 300.0f;


}



Entity::~Entity()
{
	SDL_DestroyTexture(texture);
}



void Entity::Draw(SDL_Renderer *renderTarget)
{
    	posRect.x = ((int) posX);
	posRect.y = ((int) posY);
	if (isEnabled){
		SDL_RenderCopy(renderTarget, texture, &cRect, &posRect);
	}
}



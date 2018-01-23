#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "coin.hh"
#include "sound.hh"
#include "entity.hh"

extern float difficulty;

Coin::Coin(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY){

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
	isEnabled = true; //On affiche la texture et peut interragir avec le joueur
	//definition de la move speed
	moveSpeed = 200.0f;
	
	colSound = new Sound("coin.wav"); // On lui donne le son de collision



}
Coin::~Coin()
{
	SDL_DestroyTexture(texture);
}

void Coin::Update(float dt)
{

	cRect.y = 0;
	cRect.x = 0;
	moveSpeed = 200.0f + difficulty;
	//Partie Changement texture
	posX -= moveSpeed * dt;
	
}


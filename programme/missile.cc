#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "missile.hh"
#include "entity.hh"

extern float difficulty;

Missile::Missile(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY){
	
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
    	cRect.y  =  (int(difficulty)%4) *frameHeight; // Quand on avance dans la difficulté les missiles changent

}

Missile::~Missile()
{
	SDL_DestroyTexture(texture); // Liberation de la texture
}

void Missile::Update(float dt)
{
	moveSpeed = 400.0f + difficulty; //Plus le jeu devient difficile, plus le missile ira vite
	posX -= moveSpeed * dt;  // Mise a jour de la nouvelle coordonee X du missile
	

	//Partie Changement texture
	frameCounter += dt;
	if(frameCounter >= 0.25f) //Tout les 0,25s, on change le frame du missile, pour l'animer
	{
		frameCounter = 0; //reinitialise le compteur
		cRect.x += frameWidth; // On se deplace sur le fichier image du sprite
		if(cRect.x >= textureWidth){
			cRect.x = 0; //On retourne au frame initial si on depasse du cadre
		}
	}
	
}


#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>
#include<iostream>
#include"background.hh"
#include"player.hh"
#include "game.hh"
#include "entity.hh"
#include "sound.hh"


float difficulty = 0.00f; // Difficulté du jeu... s'incrémente avec la durée du jeu


void updater(SDL_Renderer *rendererTarget, Background& background, Player& player, Game& game, const Uint8 *keyState, float delta){

	background.Update(delta);
	player.Update(keyState, delta);
	game.coinsUpdate(rendererTarget, delta);
	game.missilesUpdate(rendererTarget, delta);
	game.checkColision(&player);
	game.textUpdate(rendererTarget);
	game.eventUpdate(delta);

}

void drawer(SDL_Renderer *rendererTarget, Background& background, Player& player, Game& game){

	SDL_RenderClear(rendererTarget);	
	background.Draw(rendererTarget);
	player.Draw(rendererTarget);
	game.missilesDraw(rendererTarget);
	game.coinsDraw(rendererTarget);
	game.textDraw(rendererTarget);
	SDL_RenderPresent(rendererTarget);

}


int main(int argc, char **argv){
	
	//Initialisation des variables principales de la SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	SDL_Window *window = SDL_CreateWindow("MarxCocoRun", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 520, SDL_WINDOW_SHOWN);
	SDL_Renderer *rendererTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //creation d'un renderer( sorte de canvas ) pour y afficher des image dessus
	SDL_Event ev; // variable qui gere les evenements SDL
	float delta = 0.0f; // Temps ecoulé entre mise à jour du jeu en seconde
	const Uint8 *keyState; // Recupere les entrées clavier
	int currentTime = 0; // La difference entre currentTime et prevTime donnera le temps ecoulé entre deux MAJ
	int prevTime = 0;
	
	Background background(rendererTarget, "background2.png", 0,0,1,1); //Initialisation de l'arrière plan
	Player player(rendererTarget, "player.png", 100, 420, 2, 2); //Initialisation du texture de Joueur
	Game game(rendererTarget); //Initialisation du gestionnaire du Jeu ( c'est la classe qui gere tout le gameplay )
	game.score = 0; // Init du score du score à 0 .. Indispensable sinon un bug fait que le score de départ est aléatoire...
	while(game.isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks(); //Recuperation du temps actuel
		delta = (currentTime - prevTime) / 1000.0f;
		while(SDL_PollEvent(&ev) != 0) // Si il y a un evenement detecté alors...
		{
			if(ev.type == SDL_QUIT){ // si on clique sur la petite croix de la fenetre, le jeu s'arrete
				game.isRunning = 0;			
			}		
		}	
		
		keyState = SDL_GetKeyboardState(NULL); // Recuperation de l'etat du clavier

		updater(rendererTarget, background, player, game, keyState, delta); // On applique toutes les mises à jours du gameplay entre 2 appels
		drawer(rendererTarget, background, player, game); //Une fois les infos mises à jours, on affiche le tout a l'ecran
	}
	SDL_DestroyWindow(window); // Destruction de la fenetre ... appelé seulement à l'arret du jeu
	SDL_DestroyRenderer(rendererTarget);

	IMG_Quit();//De-initialisation de tout ce qui a ete initialisé
	SDL_Quit();

	return 0;	

}

#include "game.hh"
#include "coin.hh"
#include "text.hh"
#include "missile.hh"
#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <map>

extern float difficulty;

//Surcharge d'operateur qui permet de voir si il y a collision entre texture
bool operator==(const SDL_Rect &a, const SDL_Rect &b){
	return SDL_HasIntersection(&a, &b);
}


Game::Game(SDL_Renderer *rendererTarget){
	interv = 0.0f; // Intervale de temps avant arrivée des pieces
	intervScore = 0.0f; //Intervale de temps avant d'augmenter le score de 1 et d'augmenter la difficulté
	intervMiss = 0.0f; // Intervale de temps avant arrivée des nouveau missiles
	int score = 0;
	int isRunning = 1; // A 0 le jeu se coupe
	(void)isRunning; // Si ya pas ca, on a un warning unused variable...pourtant il est indispensable pour savoir quand couper le jeu
	int colors[4] = {255, 255, 255, 255};
	//Textes de depart. Identification des elements du tableau texte par une clé std::string
	texts.insert(std::make_pair("ScoreTitle",new Text("SCORE :", 20, 20, 490,colors,rendererTarget)));
	texts.insert(std::make_pair("ScoreNumber",new Text(std::to_string(score), 20, 100, 490,colors,rendererTarget)));
	texts.insert(std::make_pair("DistanceTitle",new Text("Distance KM :", 20, 320, 490,colors,rendererTarget)));
	texts.insert(std::make_pair("DistanceNumber",new Text(std::to_string(difficulty), 20, 440, 490,colors,rendererTarget)));
	//On met la musique	
	bgm = Mix_LoadMUS("money.ogg");
	Mix_PlayMusic(bgm, -1);

}


void Game::eventUpdate(float dt){
	intervScore += dt;

	if(intervScore >= 0.2f)
	{
		score += 1;
		difficulty += 0.01f;
		intervScore = 0.0f;

	}
	
}

void Game::coinsUpdate(SDL_Renderer *rendererTarget, float dt){
	int i;
	if(!coins.empty()){
		for(i=0; i < (int)(coins.size()); i++){ 
			coins[i]->Update(dt);	//On met a jour la position de toutes les pieces
		}
		if (coins[0]->posRect.x< 0){
			if (coins[0] != NULL){
				coins.pop_front(); //pop_front fait ref. au 1er element de la pile... correspond au coins[0]... fonctionnement FIFO
			}
		} 
	}


	std::srand(std::time(nullptr)); // use current time as seed for random generator
    	int coinRow = std::rand() % 450; //Position aleatoire de la position Y de la rangée de piece
	int coinNb = std::rand() % 30; // Nombre aleatoire de pièce par rangée 
	int nextRowWait = std::rand() % 10; // Temps aléatoire avant la nouvelle rangée
	interv += dt;

	if(interv >= (3.00f + (float)nextRowWait))
	{
		for (i=0; i<coinNb;i++){
			coins.push_back(new Coin(rendererTarget, "coin.png", 650+20*i,coinRow,1,1)); // Nouvelle rangée de piece 
			
		}
		interv = 0.0f;

	}
		
}

void Game::missilesUpdate(SDL_Renderer *rendererTarget, float dt){
	int i;
	//Meme fonctionnement que les pieces
	if(!missiles.empty()){
		for(i=0; i < (int)(missiles.size()); i++){ 
			missiles[i]->Update(dt);	
		}
		if (missiles[0]->posRect.x< -200){
			if (missiles[0] != NULL){
				missiles.pop_front();		
			}
		} 
	}


	std::srand(std::time(nullptr)); // use current time as seed for random generator
    	int missileRow = std::rand() % 450;
	intervMiss += dt;
	//Plus le jeu avance plus les missiles vont pleuvoir !
	float diff = 5.00f - difficulty;
	if (diff < 0.5f){
		diff = 0.5f;	
	} 
	if(intervMiss >= diff){
		
		missiles.push_back(new Missile(rendererTarget, "ennemy.png", 650,missileRow,2,4));
		if (difficulty > 6.00f){
			missiles.push_back(new Missile(rendererTarget, "ennemy.png", 650,(missileRow-22),2,4));
		}
		if (difficulty > 9.00f){
			missiles.push_back(new Missile(rendererTarget, "ennemy.png", 650,(missileRow-44),2,4));
		}
		intervMiss = 0.0f;

	}
		
}


void Game::textUpdate(SDL_Renderer *rendererTarget){

	for(std::map<std::string, Text*>::iterator it = texts.begin(); it != texts.end(); it++)//On poarcours les elements des maps avec un iterateur
	{
		if((it->first) == "ScoreNumber" )
		{
			*(it->second) = std::to_string(score); //On met a jour les textes avec les valeurs actuelles (Pas de ref. a ce journal de droite svp)
		}
		if((it->first) == "DistanceNumber" )
		{
			std::string dist = std::to_string(difficulty);
			*(it->second)= dist.substr(0, dist.length()-4);
		}
	}

}


void Game::missilesDraw(SDL_Renderer *rendererTarget){
	//On affiche toutes les missiles
	int i;
	for(i=0; i < (int)(missiles.size()); i++){
		missiles[i]->Draw(rendererTarget);
	} 
}

void Game::coinsDraw(SDL_Renderer *rendererTarget){
	//Pareil
	int i;
	for(i=0; i < (int)(coins.size()); i++){
		coins[i]->Draw(rendererTarget);
	} 
}


void Game::textDraw(SDL_Renderer *rendererTarget){
	//encore pareil mais la on utilise un iterateur
	std::map<std::string, Text*>::iterator it;
	for(it = texts.begin(); it != texts.end(); it++){
		it->second->Draw(rendererTarget);
	} 
}



void Game::checkColision(Player* p){

	int i;
	//Verif des colisions des pieces
	Coin* it = nullptr;
	for (i=0; i<(int)(coins.size()); i++){ 
		it = coins[i];
		if (p->posRect == it->posRect){	// Si il y a collision ( surchage operateur== )
			
			if(it->isEnabled == true){
				it->isEnabled = false; // Il faut desactiver la piece pour pas que le joueur le reprenne
				score += 20;
				Mix_PlayChannel(-1,it->colSound->soundEffect, 0);// On joue le son
			}
				
				
		}
	}
	//Verif des colisions avec les missiles
	Missile* it2 = nullptr;
	for (i=0; i<(int)(missiles.size()); i++){ 
		it2 = missiles[i];
		if (p->posRect == it2->posRect){	//si t'es touché c'est la fin de ta richesse.
			std::cout<<"GAME OVER !"<<std::endl;
			std::cout<<"Score : "<<score<<" Distance : " << difficulty<<std::endl;
			isRunning = 0;
		}
	}
	
}


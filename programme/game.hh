#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include<iostream>
#include"coin.hh"
#include "player.hh"
#include<deque>
#include<map>
#include"text.hh"
#include "missile.hh"
#include "sound.hh"

class Player;

class Game{

public:
	Game(SDL_Renderer *rendererTarget);
	Mix_Music *bgm;
	void coinsUpdate(SDL_Renderer *rendererTarget, float dt);
	void coinsDraw(SDL_Renderer *rendererTarget);
	void checkColision(Player* p);
	void textUpdate(SDL_Renderer *rendererTarget);
	void textDraw(SDL_Renderer *rendererTarget);
	void eventUpdate(float dt);
	void missilesUpdate(SDL_Renderer *rendererTarget, float dt);
	void missilesDraw(SDL_Renderer *rendererTarget);
	int isRunning;
	int score;

private:
	std::deque<Coin*> coins;
	std::deque<Missile*> missiles;
	std::map<std::string, Text*> texts;
	float interv;
	float intervScore;
	float intervMiss;
};

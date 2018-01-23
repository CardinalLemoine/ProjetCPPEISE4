#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<iostream>
#include<string>

class Text{
	

public:
	Text(const std::string t, int s, int x, int y, int c[4], SDL_Renderer *r);
	~Text();
	void Draw(SDL_Renderer *renderTarget);
	void operator=(const std::string t);

private:
	TTF_Font *font;
	int size;
	SDL_Color color;
	SDL_Surface *textSurface;
	SDL_Texture *textTexture;
	SDL_Renderer *render;
	SDL_Rect textRect;

};



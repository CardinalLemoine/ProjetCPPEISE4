#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include"text.hh"
#include<string>

Text::Text(const std::string t, int s, int x, int y, int c[4], SDL_Renderer *r){
	
	font = TTF_OpenFont("FSEX300.ttf", s); // On definit la police utilisé
	render = r; // Une copie du renderer pour l'exploiter dans une surcharge d'opérateur =
	color.r = c[0]; // On definit la couleur du text + transparance
	color.g = c[1];
	color.b = c[2];
	color.a = c[3];
	textSurface = TTF_RenderText_Solid(font, t.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(r, textSurface);
	textRect.x = x;
	textRect.y = y;
	
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);// Le rect s'adapte automatiquement à la taille de l'image-texte

}

Text::~Text()
{
	SDL_DestroyTexture(textTexture);
}

void Text::operator=(const std::string t){
	//Surcharge d'operateur= . Permet de mettre a jour un texte ( score par exempel ) en faisant Text t = "Le nouveau texte"
	SDL_FreeSurface(textSurface); //on veille a tout liberer. Une reecriture par dessus peut provoquer un SEGFAULT
	SDL_DestroyTexture(textTexture);
	textSurface = TTF_RenderText_Solid(font, t.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

}
void Text::Draw(SDL_Renderer *renderTarget)
{
	
	SDL_RenderCopy(renderTarget, textTexture, NULL, &textRect);

}

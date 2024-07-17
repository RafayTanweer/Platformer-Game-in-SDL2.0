#pragma once

#include<iostream>
#include <stdlib.h> 
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include"SDL_ttf.h"
#include <vector>

using namespace std;

class Button {

private:

	SDL_Rect* ButtonRect = nullptr;
	SDL_Texture* ButtonTexture = nullptr;
	string Text;
	SDL_Surface* TextSurface = nullptr;
	SDL_Texture* TextTexture = nullptr;
	SDL_Rect* TextRect = nullptr;

public:

	Button(string text, SDL_Renderer* gRenderer, TTF_Font* gFont);
	~Button();
	void Render(SDL_Renderer* gRenderer);
	SDL_Rect* GetRectangle();
	void SetCoordinates(int x, int y);


};

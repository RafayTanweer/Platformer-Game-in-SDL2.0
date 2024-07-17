#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class Enemy : public GameObject //Inheriting From Abstract GameObject Class
{

private:

	int frames = 0;
	int DistCovered = 0;
	int StompedCounter = 0;

public:

	Enemy();
	Enemy(int x, int y, SDL_Renderer* gRenderer, string path);
	void Move();
	SDL_Rect* GetClip();
	void Render(SDL_Renderer* gRenderer);

};
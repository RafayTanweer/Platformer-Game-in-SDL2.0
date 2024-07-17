#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class Water : public GameObject //Inheriting From Abstract GameObject Class
{

private:

	int DistanceMoved = 0;
	bool initialMovement = false;

public:

	Water();
	Water(int x, int y, SDL_Renderer* gRenderer, string path);
	void Move();
	void Render(SDL_Renderer* gRenderer);

};

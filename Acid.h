#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class Acid : public GameObject //Inheriting From Abstract GameObject Class
{

private:

	int DistanceMoved = 0;
	bool initialMovement = false;

public:

	Acid();
	Acid(int x, int y, SDL_Renderer* gRenderer, string path);
	void Move();
	void Render(SDL_Renderer* gRenderer);

};
#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class SourceContainer : public GameObject //Inheriting From Abstract GameObject Class
{

public:

	SourceContainer();
	SourceContainer(int x, int y, SDL_Renderer* gRenderer, string path);
	void Move();
	void Render(SDL_Renderer* gRenderer);

};

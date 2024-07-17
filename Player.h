#pragma once

#include<iostream>
#include <stdlib.h> 
#include "GameObject.h"

using namespace std;

class Player : public GameObject //Inheriting From Abstract GameObject Class
{

private:

	Player();
	Player(int x, int y, SDL_Renderer* gRenderer, string path);

public:


	static Player* GetInstance(int x, int y, SDL_Renderer* gRenderer, string path);
	void Move();
	void Render(SDL_Renderer* gRenderer);

};
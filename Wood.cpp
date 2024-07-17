#include "Wood.h"
//#include "GameObject.h"

//Constructor
Wood::Wood() {


}

//Constructor
Wood::Wood(int x, int y, SDL_Renderer* gRenderer, string path) {

	this->alive = true;

	this->Type = "Wood";

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 2;
	this->Rectangle->h = 2;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = path;

	this->ObjectTexture = IMG_LoadTexture(gRenderer, this->path.c_str());

	if (ObjectTexture == NULL)
		printf("Unable to create texture from %s! SDL Error: %s\n", this->path.c_str(), SDL_GetError());

}


//Defining the Pure Virtual Function of Move() in the inherited class
void Wood::Move() {


}

void Wood::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

}
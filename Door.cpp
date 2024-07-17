
#include "Door.h"
//#include "GameObject.h"

//Constructor
Door::Door() {


}

//Constructor
Door::Door(int x, int y, SDL_Renderer* gRenderer, string path) {

	this->alive = true;

	this->Type = "Door";

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 64;
	this->Rectangle->h = 64;

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
void Door::Move() {

	//Doors are static on the map

}

void Door::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

}
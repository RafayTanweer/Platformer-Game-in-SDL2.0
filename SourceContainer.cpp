#include "SourceContainer.h"
//#include "GameObject.h"

//Constructor
SourceContainer::SourceContainer() {


}

//Constructor
SourceContainer::SourceContainer(int x, int y, SDL_Renderer* gRenderer, string path) {

	this->alive = true;

	this->Type = "SourceContainer";

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

	this->LeftRect = new SDL_Rect();
	this->LeftRect->w = 32;
	this->LeftRect->h = 64;
	this->LeftRect->x = x;
	this->LeftRect->y = y;

	this->RightRect = new SDL_Rect();
	this->RightRect->w = 32;
	this->RightRect->h = 64;
	this->RightRect->x = x + 32;
	this->RightRect->y = y;

}


//Defining the Pure Virtual Function of Move() in the inherited class
void SourceContainer::Move() {

	//Bricks are static on the map

}

void SourceContainer::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

}
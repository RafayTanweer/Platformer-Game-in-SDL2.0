#include "PowerupBlock.h"
//#include "GameObject.h"

//Constructor
PowerupBlock::PowerupBlock() {



}

//Constructor
PowerupBlock::PowerupBlock(int x, int y, SDL_Renderer* gRenderer, string path) {

	this->alive = true;

	this->Type = "PowerupBlock";

	this->Rectangle = new SDL_Rect();
	this->Rectangle->w = 32;
	this->Rectangle->h = 32;

	this->Rectangle->x = x;
	this->Rectangle->y = y;

	this->x = x;
	this->y = y;

	this->path = path;

	this->ObjectTexture = IMG_LoadTexture(gRenderer, this->path.c_str());

	if (ObjectTexture == NULL)
		printf("Unable to create texture from %s! SDL Error: %s\n", this->path.c_str(), SDL_GetError());

	this->TopRect = new SDL_Rect();
	this->TopRect->w = 2;
	this->TopRect->h = 2;
	this->TopRect->x = x + 15;
	this->TopRect->y = y;

	this->DownRect = new SDL_Rect();
	this->DownRect->w = 32;
	this->DownRect->h = 30;
	this->DownRect->x = x;
	this->DownRect->y = y + 2;

	this->LeftRect = new SDL_Rect();
	this->LeftRect->w = 16;
	this->LeftRect->h = 24;
	this->LeftRect->x = x;
	this->LeftRect->y = y + 2;

	this->RightRect = new SDL_Rect();
	this->RightRect->w = 16;
	this->RightRect->h = 24;
	this->RightRect->x = x + 16;
	this->RightRect->y = y + 2;


}


//Defining the Pure Virtual Function of Move() in the inherited class
void PowerupBlock::Move() {

	//Bricks are static on the map

}

void PowerupBlock::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

}
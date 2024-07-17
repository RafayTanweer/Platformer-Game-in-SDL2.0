#include "Water.h"
//#include "GameObject.h"

//Constructor
Water::Water() {


}

//Constructor
Water::Water(int x, int y, SDL_Renderer* gRenderer, string path) {

	this->alive = true;

	this->Type = "Water";

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
void Water::Move() {

	if (this->UpwardMotion) {

		y += (int)ty;

		DistanceMoved = DistanceMoved + abs((int)ty);

		if (DistanceMoved >= this->Distance) {

			this->UpwardMotion = false;

			if (!initialMovement) {
				ty = (this->Distance * 2);
				this->Distance = this->Distance * 2;
				initialMovement = true;
			}
			else
				ty = this->Distance;
			
			this->DistanceMoved = 0;

		}

		ty *= friction;

	}
	else {

		y += (int)ty;

		DistanceMoved = DistanceMoved + abs((int)ty);

		if (DistanceMoved >= this->Distance) {

			this->UpwardMotion = true;
			//this->Distance = this->Distance;
			ty = -1 * this->Distance;
			this->DistanceMoved = 0;

		}

		ty *= friction;

	}

	this->Rectangle->x = this->x;
	this->Rectangle->y = this->y;
}

void Water::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

}
#include "Mushroom.h"
//#include "GameObject.h"

//Constructor
Mushroom::Mushroom() {


}

//Constructor
Mushroom::Mushroom(int x, int y, SDL_Renderer* gRenderer, string path) {

	this->alive = true;

	this->Type = "Powerup";

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


}


//Defining the Pure Virtual Function of Move() in the inherited class
void Mushroom::Move() {

	if (!HasMushAppeared) {

		y += (int)ty;

		Distance = Distance + abs((int)ty);

		ty *= friction;

		if ((int)ty == 0)
			ty = -5.0;

		if (Distance >= 32)
			this->HasMushAppeared = true;

	}
	else {

		if (!this->OnBrick) {

			if (this->y == 668) {

				x += (int)tx;

				tx *= friction;

				if ((int)tx == 0)
					tx = 10.0;

				if (this->CollissionFlag) {

					x = CollissionCoordinateX;
					CollissionCoordinateX = 0;
					CollissionFlag = false;
					
				}

				if (x < 0) {
					this->alive = false;
				}
				else if (x > 868) {
					this->alive = false;
				}

			}
			else {

				ty = 10;

				y += (int)ty;

				ty *= friction;

				if (y > 668)
					y = 668;

			}

		}
		else {

			x += (int)tx;

			tx *= friction;

			if ((int)tx == 0)
				tx = 10.0;

			if (this->CollissionFlag) {

				x = CollissionCoordinateX;
				CollissionCoordinateX = 0;
				CollissionFlag = false;

			}

			if (x < 0) {
				this->alive = false;
			}
			else if (x > 868) {
				this->alive = false;
			}



		}

	}

	this->Rectangle->x = this->x;
	this->Rectangle->y = this->y;

}

void Mushroom::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

}
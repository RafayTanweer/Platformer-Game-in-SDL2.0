#include "Acid.h"
//#include "GameObject.h"

//Constructor
Acid::Acid() {


}

//Constructor
Acid::Acid(int x, int y, SDL_Renderer* gRenderer, string path) {

	this->alive = true;

	this->Type = "Acid";

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
void Acid::Move() {

	if (!this->InsideDestContainer) {

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

	}
	else {

		if (!this->OnGround) {

			x += (int)tx;
			y += (int)ty;

			tx *= friction;
			ty *= friction;

			if ((int)tx == 0)
				this->tx = this->OriginalTx;

			if ((int)ty == 0)
				this->ty = this->OriginalTy;

			if (y > 538) {

				this->tx = 0.0;

			}

			if (y >= 698) {

				this->OnGround = true;
				y = 698;

			}

		}

	}

	this->Rectangle->x = this->x;
	this->Rectangle->y = this->y;
}

void Acid::Render(SDL_Renderer* gRenderer) {

	SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

}
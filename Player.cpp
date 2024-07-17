#include "Player.h"
//#include "GameObject.h"

//Constructor
Player::Player() {


}

//Constructor
Player::Player(int x, int y, SDL_Renderer* gRenderer, string path) {

	this->alive = true;

	this->Health = 3;

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

Player* Player::GetInstance(int x, int y, SDL_Renderer* gRenderer, string path) {

	static Player* player = new Player(x, y, gRenderer, path);
	return player;


}


//Defining the Pure Virtual Function of Move() in the inherited class
void Player::Move() {

	if (!this->OnBrick) {

		if (this->y == 668) {

			x += (int)tx;
			y += (int)ty;


			if (x < 0) {
				x = 0;
			}
			else if (x > 868) {
				x = 868;
			}

			if (y < 0) {
				y = 0;
			}
			else if (y > 668) {
				y = 668;
			}

			if (this->CollissionFlag) {

				if (CollissionCoordinateX == 0) {

					y = CollissionCoordinateY + 5;
					CollissionFlag = false;
					CollissionCoordinateY = 0;
					VelocityY = -1.0 * VelocityY;

				}
				else {

					x = CollissionCoordinateX;
					CollissionCoordinateX = 0;
					CollissionFlag = false;
					//VelocityY = -1.0 * VelocityY;

				}


			}

			tx *= friction;
			ty *= friction;

		}
		else {

			ty = 10;

			x += (int)tx;
			y += (int)ty;


			if (x < 0) {
				x = 0;
			}
			else if (x > 868) {
				x = 868;
			}

			if (y < 0) {
				y = 0;
			}
			else if (y > 668) {
				y = 668;
			}

			if (this->CollissionFlag) {

				if (CollissionCoordinateX == 0) {

					y = CollissionCoordinateY + 5;
					CollissionFlag = false;
					CollissionCoordinateY = 0;
					VelocityY = -1.0 * VelocityY;

				}
				else {

					x = CollissionCoordinateX;
					CollissionCoordinateX = 0;
					CollissionFlag = false;
					//VelocityY = -1.0 * VelocityY;

				}


			}

			tx *= friction;
			ty *= friction;

		}

	}
	else {

		x += (int)tx;
		y += (int)ty;


		if (x < 0) {
			x = 0;
		}
		else if (x > 868) {
			x = 868;
		}

		if (y < 0) {
			y = 0;
		}
		else if (y > 668) {
			y = 668;
		}

		if (this->CollissionFlag) {

			if (CollissionCoordinateX == 0) {

				y = CollissionCoordinateY + 5;
				CollissionFlag = false;
				CollissionCoordinateY = 0;

			}
			else {

				x = CollissionCoordinateX;
				CollissionCoordinateX = 0;
				CollissionFlag = false;
				//VelocityY = -1.0 * VelocityY;

			}


		}

		tx *= friction;
		ty *= friction;


	}

	
	this->Rectangle->x = this->x;
	this->Rectangle->y = this->y;



}

void Player::Render(SDL_Renderer* gRenderer) {

	if (this->DamageBoost) {

		if (this->Alpha == 255)
			Alpha = 127;
		else
			Alpha = 255;

		SDL_SetTextureAlphaMod(ObjectTexture, Alpha);

		if(this->IsLeft)
			SDL_RenderCopyEx(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopyEx(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle, 0.0, nullptr, SDL_FLIP_NONE);

	}
	else {

		if (this->IsLeft)
			SDL_RenderCopyEx(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
		else
			SDL_RenderCopyEx(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle, 0.0, nullptr, SDL_FLIP_NONE);

	}

}
#include "Enemy.h"
//#include "GameObject.h"

//Constructor
Enemy::Enemy() {


}

//Constructor
Enemy::Enemy(int x, int y, SDL_Renderer* gRenderer, string path) {

	this->alive = true;

	this->Type = "Enemy";

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


	SpriteSheetClips[0] = new SDL_Rect();
	SpriteSheetClips[1] = new SDL_Rect();
	SpriteSheetClips[2] = new SDL_Rect();


	//Set sprite clips
	SpriteSheetClips[0]->x = 0;
	SpriteSheetClips[0]->y = 0;
	SpriteSheetClips[0]->w = 16;
	SpriteSheetClips[0]->h = 16;

	SpriteSheetClips[1]->x = 16;
	SpriteSheetClips[1]->y = 0;
	SpriteSheetClips[1]->w = 16;
	SpriteSheetClips[1]->h = 16;

	SpriteSheetClips[2]->x = 32;
	SpriteSheetClips[2]->y = 0;
	SpriteSheetClips[2]->w = 16;
	SpriteSheetClips[2]->h = 16;

	this->TopRect = new SDL_Rect();
	this->TopRect->w = 32;
	this->TopRect->h = 16;
	this->TopRect->x = x;
	this->TopRect->y = y;

	this->LeftRect = new SDL_Rect();
	this->LeftRect->w = 10;
	this->LeftRect->h = 16;
	this->LeftRect->x = x;
	this->LeftRect->y = y + 16;

	this->RightRect = new SDL_Rect();
	this->RightRect->w = 10;
	this->RightRect->h = 16;
	this->RightRect->x = x + 22;
	this->RightRect->y = y + 16;

}


//Defining the Pure Virtual Function of Move() in the inherited class
void Enemy::Move() {

	if (Movement == "right") {

		x += (int)tx;

		this->DistCovered = DistCovered + abs((int)tx);

		tx *= friction;

		if ((int)tx == 0)
			tx = 4.0;

		if (DistCovered >= this->Distance) {

			DistCovered = 0;
			tx = -4.0;
			Movement = "left";

		}

	}
	else {

		x += (int)tx;

		this->DistCovered = DistCovered + abs((int)tx);

		tx *= friction;

		if ((int)tx == 0)
			tx = -4.0;

		if (DistCovered >= this->Distance) {

			DistCovered = 0;
			tx = +4.0;
			Movement = "right";

		}

	}

	this->Rectangle->x = this->x;
	this->Rectangle->y = this->y;

	this->TopRect->x = x;
	this->TopRect->y = y;

	this->LeftRect->x = x;
	this->LeftRect->y = y + 16;

	this->RightRect->x = x + 22;
	this->RightRect->y = y + 16;
	
}

SDL_Rect* Enemy::GetClip() {

	clip = SpriteSheetClips[frames / 3];
	frames++;
	if (frames / 3 == 2)
		frames = 0;

	return clip;

}

void Enemy::Render(SDL_Renderer* gRenderer) {

	if (IsStomped) {

		StompedCounter++;
		clip = SpriteSheetClips[2];
		if (StompedCounter >= 12)
			this->alive = false;

		SDL_RenderCopy(gRenderer, this->ObjectTexture, clip, this->Rectangle);

	}
	else {

		SDL_RenderCopy(gRenderer, this->ObjectTexture, this->GetClip(), this->Rectangle);

	}

}
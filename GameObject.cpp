#include "GameObject.h"

//Constructor
GameObject::GameObject() {

	this->alive = true;

}

//Constructor
GameObject::GameObject(int x, int y, SDL_Renderer* gRenderer, string path) {

	this->alive = true;

}

GameObject::~GameObject() {

	SDL_DestroyTexture(this->ObjectTexture);
	ObjectTexture = nullptr;

	for (int i = 0; i < 3; i++) {

		if (this->SpriteSheetClips[i] != nullptr) {

			delete this->SpriteSheetClips[i];
			this->SpriteSheetClips[i] = nullptr;

		}

	}

	

}

/*SDL_Texture* GameObject::Art() {

	return this->ObjectTexture;

}*/

SDL_Rect* GameObject::GetRectangle() {

	return this->Rectangle;

}

SDL_Rect* GameObject::GetTopRect() {

	return this->TopRect;

}

SDL_Rect* GameObject::GetDownRect() {

	return this->DownRect;

}

SDL_Rect* GameObject::GetLeftRect() {

	return this->LeftRect;

}

SDL_Rect* GameObject::GetRightRect() {

	return this->RightRect;

}

void GameObject::Move() {
	//Pure Virtual Function for Movement
}

SDL_Rect* GameObject::GetClip() {

	//Virtual Function for Getting The Clip Of the Sprite Sheet
	return nullptr;

}


//Function for returning the status of alive
bool GameObject::Alive() {

	return this->alive;

}

//Function for changing the alive status
void GameObject::ChangeAliveStatus(bool alive) {

	this->alive = alive;

}

void GameObject::Translate(int x, int y) {

	this->tx = x;
	this->ty = y;

	this->OriginalTx = this->tx;
	this->OriginalTy = this->ty;

}

void GameObject::SetPlatform(GameObject* Target) {

	this->Platform = Target;


}

GameObject* GameObject::GetPlatform() {

	return this->Platform;

}


int GameObject::GetHealth() {

	return this->Health;

}

void GameObject::DecHealth() {

	this->Health--;

}

void GameObject::setAngle(float Angle) {


	this->AngleToMoveAt = Angle;


}

void GameObject::SetSpeed(int Speed) {

	this->Speed = Speed;

}

void GameObject::SetCoordinates(int x, int y) {

	this->Rectangle->x = x;
	this->Rectangle->y = y;
	this->x = x;
	this->y = y;

}

void GameObject::SetColor(Uint8 r, Uint8 g, Uint8 b) {

	SDL_SetTextureColorMod(this->ObjectTexture, r, g, b);

}

void GameObject::SetJumpingStatus(bool flag) {

	this->isJumping = flag;

}

bool GameObject::GetJumpingStatus() {

	return this->isJumping;

}

void GameObject::Jump() {

	this->x = ceil(this->x + (deltaTime * VelocityX));
	this->y = ceil(this->y + (deltaTime * VelocityY));

	VelocityY = VelocityY + (deltaTime * Gravity);

	//if (VelocityY == 0)
		//this->isJumping = false;

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
		this->isJumping = false;
		this->JumpingDirectionSet = false;
	}

	if (this->CollissionFlag) {

		if (CollissionCoordinateX == 0) {

			y = CollissionCoordinateY + 10;
			CollissionFlag = false;
			CollissionCoordinateY = 0;
			if(VelocityY < 0)
				VelocityY = -1.0 * VelocityY;

		}
		else {

			x = CollissionCoordinateX;
			CollissionCoordinateX = 0;
			CollissionFlag = false;
			//VelocityY = -1.0 * VelocityY;

		}
		

	}

	this->Rectangle->x = this->x;
	this->Rectangle->y = this->y;

}

void GameObject::SetVelocity(float x, float y) {

	this->VelocityX = x;
	this->VelocityY = y;

}

void GameObject::SetJumpingDirectionStatus(bool flag) {

	this->JumpingDirectionSet = flag;

}

bool GameObject::GetJumpingDirectionStatus() {

	return this->JumpingDirectionSet;

}

void GameObject::SetCollissionFlag(bool flag){

	this->CollissionFlag = flag;

}

void GameObject::SetCollissionY(int y) {

	this->CollissionCoordinateY = y;

}

void GameObject::SetCollissionX(int x) {

	this->CollissionCoordinateX = x;

}

void GameObject::SetPlatformStatus(bool flag) {

	this->OnBrick = flag;

}

bool GameObject::GetPlatformStatus() {

	return this->OnBrick;

}

string GameObject::GetGameObjectType() {

	return this->Type;

}

void GameObject::SetDistance(int Dist) {

	if (this->Type == "Enemy") {

		if (Dist > 0) {

			this->Movement = "right";
			this->Translate(4.0, 0);

		}
		else {

			this->Movement = "left";
			this->Translate(-4.0, 0);

		}

	}

	this->Distance = abs(Dist);


}

void GameObject::SetDamageBoostStatus(bool status) {

	this->DamageBoost = status;

}

bool GameObject::GetDamageBoostStatus() {

	return this->DamageBoost;

}

void GameObject::SetAlphaValue(Uint8 Alpha) {

	this->Alpha = Alpha;
	SDL_SetTextureAlphaMod(this->ObjectTexture, this->Alpha);

}

bool GameObject::GetMushAppeared() {

	return this->HasMushAppeared;

}

void GameObject::DecAlphaValue(int percent) {

	if (this->alive) {

		this->Alpha = this->Alpha - percent;

		if (this->Alpha == 5) {

			this->Alpha = 0;
			this->alive = false;

		}

		SDL_SetTextureAlphaMod(this->ObjectTexture, this->Alpha);

	}

}


void GameObject::SetDestinationStatus(bool flag) {

	this->InsideDestContainer = flag;

}

void GameObject::SetSecret(bool flag) {

	this->IsSecret = flag;

}

bool GameObject::GetSecret() {

	return this->IsSecret;

}

bool GameObject::GetFillStatus() {

	return this->IsFilled;

}

void GameObject::SetFillStatus(bool flag) {

	this->IsFilled = flag;

}

void GameObject::SetPowerUpStatus(bool flag) {

	this->PowerUpAvailed = flag;

}

bool GameObject::GetPowerUpStatus() {

	return this->PowerUpAvailed;

}

void GameObject::IncHealth() {

	this->Health = this->Health + 3;

}

void GameObject::SetLeftRight(bool flag) {

	this->IsLeft = flag;

}

void GameObject::SetStomped(bool flag) {

	this->IsStomped = flag;

}

bool GameObject::GetStompedStatus() {

	return this->IsStomped;

}
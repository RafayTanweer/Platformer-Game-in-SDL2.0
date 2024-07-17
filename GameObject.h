#pragma once

#include<iostream>
#include <stdlib.h> 
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <vector>

using namespace std;

//Abstract Class For GameObject
class GameObject {

protected:

	SDL_Texture* ObjectTexture = nullptr;
	//SDL_Texture* SmokeTexture = nullptr;
	//vector<SDL_Rect*> SmokeRects;
	SDL_Rect* Rectangle = nullptr;
	SDL_Rect* LeftRect = nullptr;
	SDL_Rect* RightRect = nullptr;
	SDL_Rect* TopRect = nullptr;
	SDL_Rect* DownRect = nullptr;
	SDL_Rect* SpriteSheetClips[3] = { nullptr, nullptr, nullptr };
	SDL_Rect* clip = nullptr;
	string path;
	bool alive;
	float tx = 0.0;
	float ty = 0.0;
	float OriginalTx = 0.0;
	float OriginalTy = 0.0;
	float friction = 0.8;
	float VelocityX = 0.0;
	float VelocityY = 0.0;
	double deltaTime = 0.35;
	float Gravity = 25.0;
	GameObject* Platform = nullptr;
	int x = 0;
	int y = 0;
	int Health = 0;
	float AngleToMoveAt = 0.0;
	int Speed = 0;
	bool isJumping = false;
	bool JumpingDirectionSet = false;
	bool CollissionFlag = false;
	int CollissionCoordinateY = 0;
	int CollissionCoordinateX = 0;
	bool OnBrick = false;
	string Type;
	int Distance = 0;
	string Movement;
	bool DamageBoost = false;
	Uint8 Alpha = 255;
	bool HasMushAppeared = false;
	bool UpwardMotion = true;
	bool InsideDestContainer = false;
	bool OnGround = false;
	bool IsSecret = false;
	bool IsFilled = false;
	bool PowerUpAvailed = false;
	bool IsLeft = false;
	bool IsStomped = false;

public:

	GameObject();
	GameObject(int x, int y, SDL_Renderer* gRenderer, string path);
	~GameObject();
	SDL_Rect* GetRectangle();
	SDL_Rect* GetTopRect();
	SDL_Rect* GetDownRect();
	SDL_Rect* GetLeftRect();
	SDL_Rect* GetRightRect();
	virtual void Render(SDL_Renderer* gRenderer) = 0;
	virtual void Move() = 0; //Pure Virtual Function For Movement
	bool Alive();
	void ChangeAliveStatus(bool alive);
	void Translate(int x, int y);
	virtual void SetPlatform(GameObject* Target);
	GameObject* GetPlatform();
	virtual SDL_Rect* GetClip();
	int GetHealth();
	void DecHealth();
	void setAngle(float Angle);
	void SetSpeed(int Speed);
	void SetCoordinates(int x, int y);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void SetJumpingStatus(bool flag);
	bool GetJumpingStatus();
	void SetJumpingDirectionStatus(bool flag);
	bool GetJumpingDirectionStatus();
	void Jump();
	void SetVelocity(float x, float y);
	void SetCollissionFlag(bool flag);
	void SetCollissionY(int y);
	void SetCollissionX(int x);
	bool GetPlatformStatus();
	void SetPlatformStatus(bool flag);
	string GetGameObjectType();
	void SetDistance(int Dist);
	bool GetDamageBoostStatus();
	void SetDamageBoostStatus(bool status);
	void SetAlphaValue(Uint8 Alpha);
	void DecAlphaValue(int percent);
	bool GetMushAppeared();
	void SetDestinationStatus(bool flag);
	void SetSecret(bool flag);
	bool GetSecret();
	bool GetFillStatus();
	void SetFillStatus(bool flag);
	void SetPowerUpStatus(bool flag);
	bool GetPowerUpStatus();
	void IncHealth();
	void SetLeftRight(bool flag);
	void SetStomped(bool flag);
	bool GetStompedStatus();


};


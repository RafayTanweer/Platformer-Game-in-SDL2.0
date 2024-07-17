#include "Button.h"

Button::Button(string text, SDL_Renderer* gRenderer, TTF_Font* gFont) {

	this->Text = text;

    TextRect = new SDL_Rect();

    TextSurface = TTF_RenderText_Solid(gFont, Text.c_str(), { 0,0,0 });

    TextTexture = SDL_CreateTextureFromSurface(gRenderer, TextSurface);

    SDL_FreeSurface(TextSurface);

    SDL_QueryTexture(TextTexture, nullptr, nullptr, &TextRect->w, &TextRect->h);
    
    ButtonTexture = IMG_LoadTexture(gRenderer, "Button2.png");

    ButtonRect = new SDL_Rect();
    ButtonRect->w = TextRect->w + 10;
    ButtonRect->h = TextRect->h;
    
}

void Button::SetCoordinates(int x, int y) {

    TextRect->x = x + 5;
    TextRect->y = y;

    ButtonRect->x = x;
    ButtonRect->y = y;

}

void Button::Render(SDL_Renderer* gRenderer) {


    SDL_RenderCopy(gRenderer, ButtonTexture, nullptr, ButtonRect);
    SDL_RenderCopy(gRenderer, TextTexture, nullptr, TextRect);


}

SDL_Rect* Button::GetRectangle(){

    return this->ButtonRect;

}

Button::~Button() {

    SDL_DestroyTexture(ButtonTexture);
    ButtonTexture = nullptr;

    SDL_DestroyTexture(TextTexture);
    TextTexture = nullptr;

    delete ButtonRect;
    ButtonRect = nullptr;

    delete TextRect;
    TextRect = nullptr;

}

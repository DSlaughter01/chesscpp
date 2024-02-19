#include "PieceSet.hpp"

PieceSet::PieceSet(SDL_Renderer* renderer, std::string imgPath) 
    : imgTex(nullptr), bitboard(0ULL) {

    // Load the image from this, creating a surface
    SDL_Surface* imgSurf = IMG_Load(imgPath.c_str());
    if (!imgSurf) {
        std::cerr << "Problem with surf: " << IMG_GetError() << std::endl;
        return;
    }

    // Create a texture from the surface and assign to object
    this->imgTex = SDL_CreateTextureFromSurface(renderer, imgSurf);
    if (!this->imgTex) {
        std::cerr << "Problem with tex: " << IMG_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(imgSurf);
}
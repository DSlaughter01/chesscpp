#pragma once
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "PieceSet.hpp"
#include <vector>

class GUI {

    public:
        GUI();
        void CreateBoardSquares();
        void RenderBoardSquares();
        void RenderPieces(std::vector<PieceSet> &allPieces, uint64_t allPieceBitboard);
        void FreeBoardSquares();
        void RenderScreen(std::vector<PieceSet> &allPieces, uint64_t allPieceBitboard);
        void Quit();
    
        static SDL_Window* window;
        static SDL_Renderer* renderer;
        
    private:

        SDL_Color DarkSquare = {80, 80, 80};
        SDL_Color LightSquare = {230, 230, 230};

        // Window dimensions
        const int WIN_WIDTH = 640;
        const int WIN_HEIGHT = 640;

        // Board dimensions, space around the size
        const int SQUARE_DIM = WIN_HEIGHT / 10;
        const int BOARD_DIM = 8 * SQUARE_DIM;
        const int BOARD_LEFT = SQUARE_DIM;
        const int BOARD_TOP = SQUARE_DIM;
        const int BOARD_BOTTOM = SQUARE_DIM;

        // Board squares
        SDL_Rect boardDestRect[8][8] {};
};
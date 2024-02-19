#include "GUI.hpp"

SDL_Window* GUI::window = nullptr;
SDL_Renderer* GUI::renderer = nullptr;

GUI::GUI() {

    // Initialise SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL Initialisation Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Initialise SDL_ttf
    if (TTF_Init() < 0) {
        std::cerr << "TTF Initialisation Error: " << TTF_GetError() << std::endl;
        TTF_Quit();
        return;
    }

    // Create a window and a renderer
    window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!window || !renderer) {
        std::cerr << "Whoops! There's a problem with the window or the renderer! " << SDL_GetError() << std::endl; 
        SDL_Quit();
        TTF_Quit();
        return;
    }

    // Set the background to dark grey
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, SDL_ALPHA_OPAQUE);
}


// Create the coordinates for each of the rectangles in boardDestRect
void GUI::CreateBoardSquares() {
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            boardDestRect[i][j] = {BOARD_LEFT + (i * SQUARE_DIM),
                                   BOARD_TOP + (j * SQUARE_DIM),
                                   SQUARE_DIM,
                                   SQUARE_DIM};
        }
    }
}


void GUI::RenderBoardSquares() {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0)
                SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
            else   
                SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
            SDL_RenderFillRect(renderer, &boardDestRect[i][j]);
        }
    }

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 30);
}


void GUI::RenderPieces(std::vector<PieceSet> &allPieces, uint64_t allPieceBitboard) {

    int row{}, col{};

    for (int idx = 0; idx < 64; idx++) {

        uint64_t mask = 1ULL << idx;

        // Enter the loop if any piece is present on the current square
        if ((allPieceBitboard & mask) != 0ULL) {

            for (auto &piece : allPieces) {
                
                // Use bitwise AND to check if the corresponding bit is set in the bitboard
                if ((piece.bitboard & mask) != 0ULL) {
                    row = idx % 8;
                    col = idx / 8;
                    SDL_RenderCopy(renderer, piece.imgTex, NULL, &boardDestRect[row][col]);
                    break;
                }
            }
        }
    }
}

void GUI::RenderScreen(std::vector<PieceSet> &allPieces, uint64_t allPieceBitboard) {

    SDL_RenderClear(renderer);
    RenderBoardSquares();
    RenderPieces(allPieces, allPieceBitboard);
    SDL_RenderPresent(renderer);
}


void GUI::Quit() {

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
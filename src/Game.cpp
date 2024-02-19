#include "Game.hpp"

Game::Game()
    : whitePieceBitboard(0ULL), blackPieceBitboard(0ULL), allPieceBitboard(0ULL) {

    // Initialise SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cerr << "SDL Initialisation Error: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        std::cerr << "IMG Initialisation Error: " << IMG_GetError() << std::endl;

    isRunning = true;
}


std::vector<PieceSet> Game::MakePieces(SDL_Renderer* renderer) {
    
    // White pieces
    PieceSet WhitePawns(renderer, "assets/wP.svg"); 
    PieceSet WhiteRooks(renderer, "assets/wR.svg");
    PieceSet WhiteKnights(renderer, "assets/wN.svg"); 
    PieceSet WhiteBishops(renderer, "assets/wB.svg"); 
    PieceSet WhiteQueen(renderer, "assets/wQ.svg"); 
    PieceSet WhiteKing(renderer, "assets/wK.svg"); 

    // Black pieces
    PieceSet BlackPawns(renderer, "assets/bP.svg");
    PieceSet BlackRooks(renderer, "assets/bR.svg"); 
    PieceSet BlackKnights(renderer, "assets/bN.svg"); 
    PieceSet BlackBishops(renderer, "assets/BB.svg"); 
    PieceSet BlackQueen(renderer, "assets/bQ.svg"); 
    PieceSet BlackKing(renderer, "assets/bK.svg"); 

    return std::vector<PieceSet> {WhitePawns, WhiteRooks, WhiteKnights, WhiteBishops, WhiteQueen, WhiteKing,
                                  BlackPawns, BlackRooks, BlackKnights, BlackBishops, BlackQueen, BlackKing};
}

// Creates | bitboards for convenience
void Game::UpdateCompositeBitboards(std::vector<PieceSet> &allPieces) {

    for (int i = 0; i < 6; i++)
        whitePieceBitboard |= allPieces.at(i).bitboard;
    for (int i = 6; i < 12; i++)
        blackPieceBitboard |= allPieces.at(i).bitboard;
    
    allPieceBitboard = whitePieceBitboard | blackPieceBitboard;

}

void Game::SetBit(uint64_t& pieceBitboard, int position) {
    // Insert a 1 at the position "position"
    pieceBitboard |= 1ULL << position;
}


void Game::HandleFenString(std::string fenString, std::vector<PieceSet> &allPieces) {
    
    int position = 0;
    for (auto& i: fenString) {
        // Break when we reach a space
        if (i == ' ')
            break;
        // Move the position if the square is empty
        else if (i > '0' && i < '9')
            position += i - '0';
        // Slash is irrelevant
        else if (i == '/')
            continue;
        // if the character is a letter
        else {
            // The index of the piece type in allPieces vector
            int idx = charToIdx.find(i)->second;
            // Update relevant bitboard
            SetBit((allPieces.at(idx).bitboard), position);
            position++;
        }
    }
}


void Game::GameLoop(GUI &gui) {

    // Create a vector of all the piece types
    std::vector<PieceSet> allPieces = MakePieces(gui.renderer);
    HandleFenString(startFen, allPieces);
    UpdateCompositeBitboards(allPieces);

    SDL_Event event;

    gui.CreateBoardSquares();

    while (isRunning) {

        gui.RenderScreen(allPieces, allPieceBitboard);  

        // Check for event: close
        while (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
                break;
            }
        }
    }
}

void Game::Quit(GUI &gui) {

    gui.Quit();

    SDL_Quit();
}
#pragma once
#include <iostream>
#include "GUI.hpp"
#include "SDL2/SDL.h"
#include "PieceSet.hpp"
#include "SDL2/SDL_image.h"
#include <vector>
#include <map>

class Game {

    public:
        Game();
        std::vector<PieceSet> MakePieces(SDL_Renderer* renderer);
        void UpdateCompositeBitboards(std::vector<PieceSet> &allPieces);
        void HandleFenString(std::string fenString, std::vector<PieceSet> &allPieces);
        void SetBit(uint64_t& pieceBitboard, int position);
        void GameLoop(GUI &gui);
        void Quit(GUI &gui);

        
    private:
        bool isRunning;

        uint64_t whitePieceBitboard;
        uint64_t blackPieceBitboard;
        uint64_t allPieceBitboard;

        // Characters are present in FEN strings, and enum'd to an index in the std::vector<PieceSet> which is the result of MakePieces();
        std::map<char, int> charToIdx {
            {'P', 0},
            {'R', 1},
            {'N', 2},
            {'B', 3},
            {'Q', 4},
            {'K', 5},
            {'p', 6},
            {'r', 7},
            {'n', 8},
            {'b', 9},
            {'q', 10},
            {'k', 11}
        };

        std::string startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
        // Things that happen in the game
        char pieceToMove;
        char enPassantSquare = '-';
        int halfmove = 0;
        int fullmove = 0;
};
all:
	g++ -I include/ -L lib/ -o main src/main.cpp src/GUI.cpp src/Game.cpp src/PieceSet.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
#ifndef GRID_H
#define GRID_H
#include <vector>

#include "Tile.h"
#endif // !GRID_H


struct Grid {
	Grid(int horizontalTiles, int verticalTiles , const char* dirtTextureFP, int time);
	void RenderTiles(SDL_Renderer* renderer);
	void UpdateGrass(int timer, SDL_Renderer* renderer);

	std::vector<Tile*> tiles_;

	std::vector<Grass*> grass_;

	int horizontalTiles_;
};

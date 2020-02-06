#ifndef GRID_H
#define GRID_H
#include <vector>

#include "Tile.h"

struct Grid {
	Grid(int horizontalTiles, int verticalTiles , const char* dirtTextureFP);
	void RenderTiles(SDL_Renderer* renderer);

	std::vector<Tile*> tiles_;

	int horizontalTiles_;
};

#endif // !GRID_H

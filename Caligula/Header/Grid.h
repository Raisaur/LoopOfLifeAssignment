#pragma once
#include <vector>

#include "Tile.h"

struct Grid {
	Grid(int horizontalTiles, int verticalTiles, int size, const char* dirtTextureFP);
	void RenderTiles(SDL_Renderer* renderer);

	std::vector<Tile*> tiles_;
};

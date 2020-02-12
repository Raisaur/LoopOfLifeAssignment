#ifndef GRID_H
#define GRID_H
#include <vector>
#include "Vector2.h"
#include "Tile.h"

class Tile;

struct Grid {
	Grid(int horizontalTiles, int verticalTiles , const char* dirtTextureFP);
	void RenderTiles(SDL_Renderer* renderer);

	int CurrentTileIndex(Vector2 center);

	std::vector<Tile*> tiles_;

	int horizontalTiles_;
};

#endif // !GRID_H

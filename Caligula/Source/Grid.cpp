#include "Grid.h"

#include "Service.h"
#include "SpriteHandler.h"

Grid::Grid(int horizontalTiles, int verticalTiles, int size, const char* dirtTextureFP)
{
	Tile* newTile;

	for (int i = 0; i < verticalTiles; i++)
	{
		for (int j = 0; j < horizontalTiles; j++)
		{
			newTile = new Tile(j * size, i * size, size, size, dirtTextureFP);
			tiles_.push_back(newTile);
		}
	}
}

void Grid::RenderTiles(SDL_Renderer* renderer)
{
	for (Tile* tile : tiles_)
	{
		tile->Render(renderer);
	}
}

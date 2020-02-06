#include "Grid.h"

#include "Service.h"
#include "SpriteHandler.h"
#include "Config.h" 

Grid::Grid(int horizontalTiles, int verticalTiles, const char* dirtTextureFP)
{
	horizontalTiles_ = horizontalTiles;

	int width = Service<Config>::Get()->SCREEN_WIDTH / horizontalTiles;
	int height = Service<Config>::Get()->SCREEN_HEIGHT / verticalTiles;

	Tile* newTile;
	int tileindex = 0;

	for (int i = 0; i < verticalTiles; i++)
	{
		for (int j = 0; j < horizontalTiles; j++)
		{
			newTile = new Tile(j * width, i * height, width, height, dirtTextureFP, tileindex);
			tiles_.push_back(newTile);
			tileindex++;
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



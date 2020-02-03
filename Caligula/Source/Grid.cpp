#include "Grid.h"

#include "Service.h"
#include "SpriteHandler.h"
#include "Config.h" 

#include "Grass.h"

Grid::Grid(int horizontalTiles, int verticalTiles, const char* dirtTextureFP, int time)
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

	int grassTiles[5];
	for (int i = 0; i < 5; i++)
	{
		int nr = 15 * (i + 1);
		Grass* newGrass = new Grass("../Assets/grass.png", this, nr, i + 1, time + 50);
		grass_.push_back(newGrass);
	}
}

void Grid::RenderTiles(SDL_Renderer* renderer)
{
	for (Tile* tile : tiles_)
	{
		tile->Render(renderer);
	}
}

void Grid::UpdateGrass(int timer, SDL_Renderer* renderer)
{
	for (Grass* grass : grass_)
	{
		grass->Act(timer);
		grass->Render(renderer);
	}
}



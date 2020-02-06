#ifndef TILE_H
#define TILE_H
#include <vector>
#include "Sprite.h"
#include "Grass.h"

class Sheep;
class Wolf;

struct Tile {
	Tile(int x, int y, int w, int h, const char* filepath, int index);
	void Render(SDL_Renderer* renderer);

	int tileIndex_;

	SDL_Rect rect_;

	Sprite* dirtSprite_;

	Grass* grass_;
	std::vector<Sheep*> sheep_;
	std::vector<Wolf*> wolves_;
};

#endif // !TILE_H

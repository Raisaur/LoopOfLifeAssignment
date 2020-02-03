#ifndef TILE_H
#define TILE_H
#include <vector>

#include "Sprite.h"

#endif // !TILE_H

class Grass;
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

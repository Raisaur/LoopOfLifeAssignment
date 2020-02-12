#ifndef TILE_H
#define TILE_H
#include <vector>
#include "Sprite.h"

class Grass;
class Sheep;
class Wolf;

struct Tile {
	Tile(int x, int y, int w, int h, const char* filepath, int index);
	void Render(SDL_Renderer* renderer);

	Grass* grass_;
	std::vector<Sheep*> sheep_;
	std::vector<Wolf*> wolves_;

	SDL_Rect rect_;

private:
	int tileIndex_;

	Sprite* dirtSprite_;

};

#endif // !TILE_H

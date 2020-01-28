#pragma once
#include <vector>

#include "Vector2.h"
#include "Sprite.h"

#include "Grass.h"
#include "Sheep.h"
#include "Wolf.h"


struct Tile {
	Tile(int x, int y, int w, int h, const char* filepath);
	void Render(SDL_Renderer* renderer);

	SDL_Rect rect_;

	Sprite* dirtSprite_;

	Grass* grass_;
	std::vector<Sheep*> sheep_;
	std::vector<Wolf*> wolves_;
};

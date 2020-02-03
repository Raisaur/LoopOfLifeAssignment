#ifndef GRASS_H
#define GRASS_H
#include "Sprite.h"
#endif // !GRASS_H

class Grid;
class vector;

struct Grass {
	Grass(const char* filepath, Grid* grid, int tileIndex, int health, int startTime);
	void Render(SDL_Renderer* renderer);

	void Act(int timer);
	void Grow();
	void Wither();
	void Spread();

	int health_;
	bool mature_;

	int nextActTime_;

	Grid* grid_;
	int tileIndex_;

	const char* spriteFP_;

	SDL_Rect rect_;

	Sprite* grassSprite_;
};
#ifndef GRASS_H
#define GRASS_H
#include "Sprite.h"
#include <vector>

class Grid;

enum GrassAction
{
	NOTHING,
	GROW,
	SPREAD,
	EATEN
};

struct Grass {
	Grass(const char* filepath, Grid* grid, std::vector<Grass*>* grassContainer, int tileIndex, int health);
	void Render(SDL_Renderer* renderer);

	void Sense();
	void Decide();
	void Act();

private:
	void Grow();
	void Wither();
	void Spread();
	void Eaten();

	int health_;
	int tileIndex_;

	bool mature_;
	bool trampled_, eaten_;

	GrassAction action_;

	Grid* grid_;
	std::vector<Grass*>* grassVector_;

	const char* spriteFP_;

	SDL_Rect rect_;

	Sprite* grassSprite_;
};

#endif // !GRASS_H
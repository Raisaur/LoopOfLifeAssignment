#ifndef SHEEP_H
#define SHEEP_H

#include "Sprite.h"
#include <vector>

class Grid;

struct Sheep {
	Sheep(const char* filepath, Grid* grid, std::vector<Sheep*>* sheepContainer, int tileIndex, int health);
	void Render(SDL_Renderer* renderer);

	void Sense();
	void Decide();
	void Act();

private:
	void Roam();
	void Eat();
	void RunAway();

	int health_;
	float movespeed_;
};

#endif // !SHEEP_H

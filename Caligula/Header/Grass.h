#ifndef GRASS_H
#define GRASS_H
#include "Sprite.h"
#include <vector>
#include "Grid.h"

class Vector2;
class EntityManager;

struct Grass {
	Grass(const char* filepath, EntityManager* em, int tileIndex, int health);
	void Render(SDL_Renderer* renderer);

	void Sense();
	void Decide();
	void Act();

	Vector2 pos_;
	int tileIndex_;

	bool isDead_;

private:
	enum GrassAction
	{
		NOTHING,
		GROW,
		SPREAD,
		WITHER,
		EATEN
	};

	void Grow();
	void Wither();
	void Spread();
	void Eaten();

	int health_;

	int spreadCount_;

	bool mature_;
	bool trampled_, eaten_;

	GrassAction action_;

	EntityManager* em_;

	const char* spriteFP_;
	Sprite* grassSprite_;
};

#endif // !GRASS_H
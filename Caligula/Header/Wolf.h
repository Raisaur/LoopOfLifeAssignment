#ifndef WOLF_H
#define WOLF_H
#include "Sprite.h"
#include <vector>
#include "Vector2.h"

class Grid;
class Sheep;
class EntityManager;

struct Wolf {
	Wolf(const char* filepath, EntityManager* em, int xPos, int yPos, int health);
	void Render(SDL_Renderer* renderer);

	void Sense();
	void Decide();
	void Act();

	Vector2 pos_;

private:
	enum WolfAction {
		ROAM,
		SEEK,
		EAT,
		BREED
	};

	//void Roam();
	//void Seek();
	void Move();
	void Eat();
	void Breed();

	Vector2 direction_;

	int health_;
	float movespeed_;
	float detectionRange_;

	WolfAction action_;

	int tileIndex;
	int closestSheepIndex_;
	Sheep* closestSheep_;

	EntityManager* em_;

	const char* spriteFP_;
	Sprite* wolfSprite_;
};

#endif // !WOLF_H
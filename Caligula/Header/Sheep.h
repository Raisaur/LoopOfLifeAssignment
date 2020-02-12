#ifndef SHEEP_H
#define SHEEP_H
#include "Sprite.h"
#include <vector>
#include "Vector2.h"

class Grid;
class Grass;
class Wolf;
class EntityManager;

struct Sheep {
	Sheep(const char* filepath, EntityManager* em, int xPos, int yPos, int health);
	void Render(SDL_Renderer* renderer);

	void Sense();
	void Decide();
	void Act();

	Vector2 pos_;

private:
	enum SheepAction {
		ROAM,
		SEEK,
		EAT,
		RUNAWAY,
		BREED
	};

	//void Roam();
	//void Seek();
	void Move();
	void Eat();
	//void RunAway();
	void Breed();

	Vector2 direction_;

	int health_;
	float movespeed_;
	float detectionRange_;

	SheepAction action_;

	int tileIndex;
	int closestGrassIndex_;
	int closestWolfIndex_;
	EntityManager* em_;
	Grass* closestGrass_;
	Wolf* closestWolf_;

	bool breedOnce_;

	const char* spriteFP_;
	Sprite* sheepSprite_;
};

#endif // !SHEEP_H

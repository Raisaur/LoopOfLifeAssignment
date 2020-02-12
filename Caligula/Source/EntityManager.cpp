#include "EntityManager.h"
#include "Grid.h"
#include "Grass.h"
#include "Sheep.h"
#include "Wolf.h"

EntityManager::EntityManager()
{

}

void EntityManager::GenerateGrid()
{
	grid_ = new Grid(16, 16, "../Assets/dirt.png");
}

void EntityManager::PlaceGrass()
{
	int tileNr;
	int startHealth;

	for (int i = 0; i < 20; i++)
	{
		tileNr = rand() % grid_->tiles_.size();

		if (grid_->tiles_[tileNr]->grass_ == nullptr)
		{
			startHealth = rand() % 15 + 1;
			Grass* newGrass = new Grass("../Assets/grass.png", this, tileNr, startHealth);
			grass_.push_back(newGrass);
		}
	}
}

void EntityManager::PlaceSheep()
{
	int tileNr;
	int startHealth;

	for (int i = 0; i < 10; i++)
	{
		tileNr = rand() % grid_->tiles_.size();

		if (grid_->tiles_[tileNr]->sheep_.empty())
		{
			startHealth = rand() % 45 + 1;
			Sheep* newSheep = new Sheep("../Assets/sheep.png", this, grid_->tiles_[tileNr]->rect_.x, grid_->tiles_[tileNr]->rect_.y, startHealth);
			sheep_.push_back(newSheep);
			grid_->tiles_[tileNr]->sheep_.push_back(newSheep);
		}
	}
}
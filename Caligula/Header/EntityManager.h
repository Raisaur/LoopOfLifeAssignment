#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <vector>

class Grid;
class Grass;
class Sheep;
class Wolf;

struct EntityManager
{
	EntityManager();
	void GenerateGrid();
	void PlaceGrass();
	void PlaceSheep();

	Grid* grid_;
	std::vector<Grass*> grass_;
	std::vector<Sheep*> sheep_;
	std::vector<Wolf*> wolves_;
};

#endif // !ENTITY_MANAGER_H

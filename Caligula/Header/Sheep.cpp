#include "Sheep.h"

#include "Service.h"
#include "SpriteHandler.h"
#include "Config.h"
#include "Grass.h"
#include "Wolf.h"
#include "Grid.h"
#include "Tile.h"
#include "EntityManager.h"


Sheep::Sheep(const char* filepath, EntityManager* em, int xPos, int yPos, int health)
	: action_(ROAM),
	closestGrassIndex_(0),
	closestGrass_(nullptr),
	closestWolfIndex_(0),
	closestWolf_(nullptr),
	tileIndex(0)
{
	em_ = em;

	health_ = health;
	movespeed_ = 0.3f;
	detectionRange_ = em_->grid_->tiles_[0]->rect_.w * 3;

	pos_.x_ = xPos;//grid_->tiles_[tileIndex]->rect_.x + grid_->tiles_[tileIndex]->rect_.w / 2;
	pos_.y_ = yPos;//grid_->tiles_[tileIndex]->rect_.y + grid_->tiles_[tileIndex]->rect_.h / 2;

	sheepSprite_ = Service<SpriteHandler>::Get()->CreateSprite(filepath, 0, 0,
															   em_->grid_->tiles_[0]->rect_.w- em_->grid_->tiles_[0]->rect_.w / 5,
															   em_->grid_->tiles_[0]->rect_.h - em_->grid_->tiles_[0]->rect_.h / 5);
	
	spriteFP_ = filepath;
}

void Sheep::Render(SDL_Renderer* renderer)
{
	SDL_Rect dst = { pos_.x_, pos_.y_, sheepSprite_->GetArea().w, sheepSprite_->GetArea().h };
	SDL_RenderCopy(renderer, sheepSprite_->GetTexture(), &sheepSprite_->GetArea(), &dst);
}

void Sheep::Sense()
{
	// Find closest grass
	float distance;
	float shortestDistance;
	closestGrassIndex_ = 0;

	for (int i = 0; i < em_->grass_.size(); i++)
	{
		distance = 0.0f;
		Grass* tempGrass = em_->grass_.at(i);

		distance += abs(pos_.x_ - tempGrass->pos_.x_);
		distance += abs(pos_.y_ - tempGrass->pos_.y_);

		if (i == 0)
			shortestDistance = distance;

		else
		{
			if (distance < shortestDistance)
			{
				shortestDistance = distance;
				closestGrass_ = tempGrass;
			}
		}
	}

	//find closest wolf
	closestWolfIndex_ = 0;

	for (int i = 0; i < em_->wolves_.size(); i++)
	{
		distance = 0.0f;
		Wolf* tempWolf = em_->wolves_.at(i);

		distance += abs(pos_.x_ - tempWolf->pos_.x_);
		distance += abs(pos_.y_ - tempWolf->pos_.y_);

		if (i == 0)
			shortestDistance = distance;

		else
		{
			if (distance < shortestDistance)
			{
				shortestDistance = distance;
				closestWolf_ = tempWolf;
			}
		}
	}

	breedOnce_ = false;
}

void Sheep::Decide()
{
	action_ = ROAM;

	if (closestWolf_ != nullptr)
	{
		if (abs(pos_.x_ - closestWolf_->pos_.x_) < detectionRange_ &&
			abs(pos_.y_ - closestWolf_->pos_.y_) < detectionRange_)
		{
			if (pos_.x_ - closestWolf_->pos_.x_ < 0)
			{
				direction_.x_ = 1;
			}

			else if (pos_.x_ - closestWolf_->pos_.x_ > 0)
			{
				direction_.x_ = -1;
			}

			else
				direction_.x_ = 0;

			if (pos_.y_ - closestWolf_->pos_.y_ < 0)
			{
				direction_.y_ = 1;
			}

			else if (pos_.y_ - closestWolf_->pos_.y_ > 0)
			{
				direction_.x_ = -1;
			}

			else
				direction_.y_ = 0;

			action_ = RUNAWAY;
			return;
		}
	}


	if (health_ > Config::SHEEP_HEALTH_TO_BREED)
	{
		action_ = BREED;
		return;
	}

	if (closestGrass_ != nullptr)
	{
		if (pos_.x_ > em_->grid_->tiles_[closestGrass_->tileIndex_]->rect_.x&&
			pos_.x_ < em_->grid_->tiles_[closestGrass_->tileIndex_]->rect_.x + em_->grid_->tiles_[closestGrass_->tileIndex_]->rect_.w)
		{
			if (pos_.y_ > em_->grid_->tiles_[closestGrass_->tileIndex_]->rect_.y&&
				pos_.y_ < em_->grid_->tiles_[closestGrass_->tileIndex_]->rect_.y + em_->grid_->tiles_[closestGrass_->tileIndex_]->rect_.h)
			{
				action_ = EAT;
				return;
			}
		}

		if (abs(pos_.x_ - closestGrass_->pos_.x_) < detectionRange_ &&
			abs(pos_.y_ - closestGrass_->pos_.y_) < detectionRange_)
		{
			if (pos_.x_ - closestGrass_->pos_.x_ < 0)
			{
				direction_.x_ = -1;
			}

			else if (pos_.x_ - closestGrass_->pos_.x_ > 0)
			{
				direction_.x_ = 1;
			}

			else
				direction_.x_ = 0;

			if (pos_.y_ - closestGrass_->pos_.y_ < 0)
			{
				direction_.y_ = -1;
			}

			else if (pos_.y_ - closestGrass_->pos_.y_ > 0)
			{
				direction_.x_ = 1;
			}
			else
				direction_.y_ = 0;
		}

		action_ = SEEK;
		return;
	}

	else
	{
		direction_.x_ = rand() % 2 + (-1);
		direction_.y_ = rand() % 2 + (-1);

		action_ = ROAM;
	}
}

void Sheep::Act()
{
	switch (action_)
	{
	case (ROAM):
	{
		Move();
		break;
	}

	case (SEEK):
	{
		Move();
		break;
	}

	case (EAT):
	{
		Eat();
		break;
	}

	case (RUNAWAY):
	{
		Move();
		break;
	}

	case (BREED):
	{
		Breed();
		return;
	}
	default:
		break;
	}
}

void Sheep::Move()
{
	tileIndex = em_->grid_->CurrentTileIndex(Vector2(pos_.x_ + sheepSprite_->GetArea().w / 2,
												pos_.y_ + sheepSprite_->GetArea().h / 2));

	for (int i = 0; i < em_->grid_->tiles_[tileIndex]->sheep_.size(); i++)
	{
		if (em_->grid_->tiles_[tileIndex]->sheep_[i] == this)
		{
			em_->grid_->tiles_[tileIndex]->sheep_.erase(em_->grid_->tiles_[tileIndex]->sheep_.begin() + i);
		}
	}

	pos_ = pos_ + (direction_ * movespeed_);
	tileIndex = em_->grid_->CurrentTileIndex(Vector2(pos_.x_ + sheepSprite_->GetArea().w / 2,
												pos_.y_ + sheepSprite_->GetArea().h / 2));
	em_->grid_->tiles_[tileIndex]->sheep_.push_back(this);

	if (pos_.x_ < 0)
	{
		pos_.x_ += 0.5;
	}

	if (pos_.y_ > 0)
	{
		pos_.y_ += 0.5;
	}

	if (pos_.x_ > em_->grid_->tiles_[0]->rect_.w * 16)
	{
		pos_.x_ -= 0.5;
	}

	if (pos_.y_ > em_->grid_->tiles_[0]->rect_.h * 16)
	{
		pos_.y_ -= 0.5;
	}
}

//void Sheep::Seek()
//{
//	pos_ = pos_ + (direction_ * movespeed_);
//	tileIndex = grid_->CurrentTileIndex(Vector2(pos_.x_ + sheepSprite_->GetArea().w / 2,
//												pos_.y_ + sheepSprite_->GetArea().h / 2));
//	grid_->tiles_[tileIndex]->sheep_.push_back(this);
//}

void Sheep::Eat()
{
	if (health_ < Config::SHEEP_MAX_HEALTH)
	{
		health_ += Config::SHEEP_HEALTH_PER_EAT;
		
		if (health_ > 50)
			health_ = 50;
	}
}

//void Sheep::RunAway()
//{
//}

void Sheep::Breed()
{
	if (!breedOnce_)
	{
		Sheep* newSheep = new Sheep(spriteFP_, em_, pos_.x_ + em_->grid_->tiles_[0]->rect_.w, pos_.y_ + em_->grid_->tiles_[0]->rect_.h, 10);
		em_->sheep_.push_back(newSheep);
		health_ -= 30;
		breedOnce_ = true;
	}
}

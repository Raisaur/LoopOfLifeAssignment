#include "Grass.h"

#include "Service.h"
#include "SpriteHandler.h"

#include "Config.h"
#include "EntityManager.h"
#include "Vector2.h"
#include "Grid.h"

#include <iostream>
#include <ctime>

Grass::Grass(const char* filepath, EntityManager* em, int tileIndex, int health)
	:action_(NOTHING)
{
	em_ = em;

	tileIndex_ = tileIndex;
	em_->grid_->tiles_[tileIndex_]->grass_ = this;

	pos_.x_ = em_->grid_->tiles_[tileIndex_]->rect_.x;
	pos_.y_ = em_->grid_->tiles_[tileIndex_]->rect_.y;

	grassSprite_ = Service<SpriteHandler>::Get()->CreateSprite(filepath, 0, 0, em_->grid_->tiles_[0]->rect_.w, em_->grid_->tiles_[0]->rect_.h);
	spriteFP_ = filepath;

	health_ = health;
	mature_ = false;
	trampled_ = false;
	eaten_ = false;
	isDead_ = false;

	spreadCount_ = 0;
}

void Grass::Render(SDL_Renderer* renderer)
{
	SDL_Rect dst = { pos_.x_ + Config::GRASS_MAX_HEALTH - health_, pos_.y_ + Config::GRASS_MAX_HEALTH - health_,
					 grassSprite_->GetArea().w -(Config::GRASS_MAX_HEALTH - health_) * 2, grassSprite_->GetArea().h - (Config::GRASS_MAX_HEALTH - health_) * 2 };
	SDL_RenderCopy(renderer, grassSprite_->GetTexture(), &grassSprite_->GetArea(), &dst);
}

void Grass::Sense()
{
	if (health_ >= Config::GRASS_MAX_HEALTH && !mature_)
	{
		mature_ = true;
	}

	if (!em_->grid_->tiles_[tileIndex_]->wolves_.empty() && em_->grid_->tiles_[tileIndex_]->sheep_.empty())
	{
		trampled_ = true;
		eaten_ = false;
		return;
	}

	if (!em_->grid_->tiles_[tileIndex_]->sheep_.empty())
	{
		trampled_ = true;
		eaten_ = true;
	}
}

void Grass::Decide()
{
	if (!mature_)
	{
		if (!trampled_ || !eaten_)
		{
			action_ = GROW;
		}
	}

	else if (mature_)
	{
		if (!eaten_)
		{
			action_ = SPREAD;
		}

		if (spreadCount_ > 1)
		{
			action_ = WITHER;
		}
	}

	if (eaten_)
	{
		action_ = EATEN;
	}
}

void Grass::Act()
{
	switch (action_)
	{
		case (NOTHING):
			break;

		case (GROW):
		{
			Grow();
			break;
		}

		case (SPREAD):
		{
			Spread();
			break;
		}

		case (WITHER):
		{
			Wither();
			break;
		}

		case (EATEN):
		{
			Eaten();
			break;
		}

	default:
		break;
	}

	if (health_ <= 0)
	{
		isDead_ = true;
	}
}

void Grass::Grow()
{
	if (health_ < Config::GRASS_MAX_HEALTH)
		health_++;
}

void Grass::Wither()
{
	health_ -= 1;
}

void Grass::Spread()
{
	if (spreadCount_ < 2)
	{
		int startHealth = 2;
		int spreadTile = rand() % 3;

		switch (spreadTile)
		{
		case (0):
			if (tileIndex_ - em_->grid_->horizontalTiles_ > 0 && em_->grid_->tiles_[tileIndex_ - em_->grid_->horizontalTiles_]->grass_ == nullptr) //check if tile above is empty
			{
				Grass* newGrass = new Grass(spriteFP_, em_, tileIndex_ - em_->grid_->horizontalTiles_, startHealth);
				em_->grass_.push_back(newGrass);
				spreadCount_++;;
			}
			break;

		case(1):
			if (tileIndex_ - em_->grid_->horizontalTiles_ > 0 && em_->grid_->tiles_[tileIndex_ - 1]->grass_ == nullptr) //check if tile to the left is empty
			{
				Grass* newGrass = new Grass(spriteFP_,em_, tileIndex_ - 1, startHealth);
				em_->grass_.push_back(newGrass);
				spreadCount_++;
			}
			break;

		case(2):
			if (tileIndex_ + em_->grid_->horizontalTiles_ < 256 && em_->grid_->tiles_[tileIndex_ + 1]->grass_ == nullptr) //check if tile to the right is empty
			{
				Grass* newGrass = new Grass(spriteFP_, em_, tileIndex_ + 1, startHealth);
				em_->grass_.push_back(newGrass);
				spreadCount_++;
			}
			break;

		case(3):
			if (tileIndex_ + em_->grid_->horizontalTiles_ < 256 && em_->grid_->tiles_[tileIndex_ + em_->grid_->horizontalTiles_]->grass_ == nullptr) //check if tile below is empty
			{
				Grass* newGrass = new Grass(spriteFP_, em_, tileIndex_ + em_->grid_->horizontalTiles_, startHealth);
				em_->grass_.push_back(newGrass);
				spreadCount_++;
			}
			break;

		default:
			break;
		}
	}
}

void Grass::Eaten()
{
	health_ -= Config::GRASS_DAMAGE_WHEN_EATEN;
}

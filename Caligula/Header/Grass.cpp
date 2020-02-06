#include "Grass.h"

#include "Service.h"
#include "SpriteHandler.h"

#include "Grid.h"
#include "Config.h"

#include <iostream>

Grass::Grass(const char* filepath,Grid* grid, std::vector<Grass*>* grassContainer, int tileIndex, int health)
	:action_(NOTHING)
{
	grid_ = grid;
	grassVector_ = grassContainer;
	tileIndex_ = tileIndex;
	grid_->tiles_[tileIndex_]->grass_ = this;

	rect_.x = grid_->tiles_[tileIndex_]->rect_.x;
	rect_.y = grid_->tiles_[tileIndex_]->rect_.y;
	rect_.w = grid_->tiles_[tileIndex_]->rect_.w;
	rect_.h = grid_->tiles_[tileIndex_]->rect_.h;

	grassSprite_ = Service<SpriteHandler>::Get()->CreateSprite(filepath, 0, 0, rect_.w, rect_.h);
	spriteFP_ = filepath;

	health_ = health;
	mature_ = false;
	trampled_ = false;
	eaten_ = false;

	//std::cout << "Grass spawned on tile #" << tileIndex_ << ", mmr adress: " << &grid_->tiles_[tileIndex_]->grass_ << std::endl;
}

void Grass::Render(SDL_Renderer* renderer)
{
	SDL_Rect dst = { rect_.x, rect_.y, grassSprite_->GetArea().w, grassSprite_->GetArea().h };
	SDL_RenderCopy(renderer, grassSprite_->GetTexture(), &grassSprite_->GetArea(), &dst);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
	SDL_RenderDrawRect(renderer, &rect_);
}

void Grass::Sense()
{
	//std::cout << "Grass on tile #" << tileIndex_ << " sensing" << std::endl;
	if (health_ >= Config::GRASS_MAX_HEALTH && !mature_)
	{
		mature_ = true;
	}

	if (!grid_->tiles_[tileIndex_]->wolves_.empty() && grid_->tiles_[tileIndex_]->sheep_.empty())
	{
		trampled_ = true;
		eaten_ = false;
		return;
	}

	if (!grid_->tiles_[tileIndex_]->sheep_.empty())
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
	}

	if (eaten_)
	{
		action_ = EATEN;
	}
	//std::cout << "Grass on tile #" << tileIndex_ << " decided to " << action_ << std::endl;
}

void Grass::Act()
{
	//std::cout << "Grass on tile #" << tileIndex_ << " did " << action_ << std::endl;
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

	default:
		break;
	}

	if (mature_)
	{
		Wither();
	}
}

void Grass::Grow()
{
	if (!mature_)
	{
		health_++;

		if (!mature_ && health_ >= 10)
			mature_ = true;
	}
}

void Grass::Wither()
{
	if (mature_)
		health_ -= 1;
}

void Grass::Spread()
{
	int startHealth = rand() % 12 + 2;

	if (grid_->tiles_[tileIndex_ - grid_->horizontalTiles_]->grass_ == nullptr) //check if tile above is empty
	{
		Grass* newGrass = new Grass(spriteFP_, grid_, grassVector_, tileIndex_ - grid_->horizontalTiles_, startHealth);
		grassVector_->push_back(newGrass);
		std::cout << "Grass on tile #" << tileIndex_ << " spread to tile #" << tileIndex_ - grid_->horizontalTiles_ << std::endl;
		return;
	}

	else if (grid_->tiles_[tileIndex_ - 1]->grass_ == nullptr) //check if tile to the left is empty
	{
		Grass* newGrass = new Grass(spriteFP_, grid_, grassVector_, tileIndex_ - 1, startHealth);
		grassVector_->push_back(newGrass);
		std::cout << "Grass on tile #" << tileIndex_ << " spread to tile #" << tileIndex_ - 1 << std::endl;
		return;
	}

	else if (grid_->tiles_[tileIndex_ + 1]->grass_ == nullptr) //check if tile to the right is empty
	{
		Grass* newGrass = new Grass(spriteFP_, grid_, grassVector_, tileIndex_ + 1, startHealth);
		grassVector_->push_back(newGrass);
		std::cout << "Grass on tile #" << tileIndex_ << " spread to tile #" << tileIndex_ + 1 << std::endl;
		return;
	}

	else if (grid_->tiles_[tileIndex_ + grid_->horizontalTiles_]->grass_ == nullptr) //check if tile below is empty
	{
		Grass* newGrass = new Grass(spriteFP_, grid_, grassVector_, tileIndex_ + grid_->horizontalTiles_, startHealth);
		grassVector_->push_back(newGrass);
		std::cout << "Grass on tile #" << tileIndex_ << " spread to tile #" << tileIndex_ + grid_->horizontalTiles_ << std::endl;
		return;
	}

}

void Grass::Eaten()
{
}

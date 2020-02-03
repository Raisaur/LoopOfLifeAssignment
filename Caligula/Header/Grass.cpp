#include "Grass.h"

#include "Service.h"
#include "SpriteHandler.h"

#include "Grid.h"

#include <iostream>

Grass::Grass(const char* filepath, Grid* grid, int tileIndex, int health, int startTime)
{
	grid_ = grid;
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

	nextActTime_ = startTime;
}

void Grass::Render(SDL_Renderer* renderer)
{
	SDL_Rect dst = { rect_.x, rect_.y, grassSprite_->GetArea().w, grassSprite_->GetArea().h };
	SDL_RenderCopy(renderer, grassSprite_->GetTexture(), &grassSprite_->GetArea(), &dst);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
	SDL_RenderDrawRect(renderer, &rect_);
}

void Grass::Act(int timer)
{
	if (timer >= nextActTime_)
	{
		nextActTime_ = timer + 50;

		Grow();
		Wither();
		Spread();

		std::cout << "Grass on tile #" << tileIndex_ << " has " << health_ << " hp" << std::endl;
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
	if (mature_)
	{
		int startHealth = rand() % 10;

		if (!grid_->tiles_[tileIndex_ - grid_->horizontalTiles_]->grass_) //check if tile above is empty
		{
			Grass* newGrass = new Grass(spriteFP_, grid_, tileIndex_ - grid_->horizontalTiles_, startHealth, nextActTime_);
			grid_->grass_.push_back(newGrass);
			return;
		}

		else if (!grid_->tiles_[tileIndex_ - 1]->grass_) //check if tile to the left is empty
		{
			Grass* newGrass = new Grass(spriteFP_, grid_, tileIndex_ - 1, startHealth, nextActTime_);
			grid_->grass_.push_back(newGrass);
			return;
		}

		else if (!grid_->tiles_[tileIndex_ + 1]->grass_) //check if tile to the right is empty
		{
			Grass* newGrass = new Grass(spriteFP_, grid_, tileIndex_ + 1, startHealth, nextActTime_);
			grid_->grass_.push_back(newGrass);
			return;
		}

		else if (!grid_->tiles_[tileIndex_ + grid_->horizontalTiles_]->grass_) //check if tile below is empty
		{
			Grass* newGrass = new Grass(spriteFP_, grid_, tileIndex_ + grid_->horizontalTiles_, startHealth, nextActTime_);
			grid_->grass_.push_back(newGrass);
			return;
		}
	}
}

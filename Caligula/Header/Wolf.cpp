#include "Wolf.h"

#include "Service.h"
#include "SpriteHandler.h"
#include "Config.h"
#include "EntityManager.h"
#include "Sheep.h"
#include "Grid.h"
#include "Tile.h"

Wolf::Wolf(const char* filepath, EntityManager* em, int xPos, int yPos, int health)
{
	em_ = em;

	health_ = health;
	movespeed_ = em_->grid_->tiles_[0]->rect_.w;
	detectionRange_ = movespeed_ * 3;

	pos_.x_ = xPos;//grid_->tiles_[tileIndex]->rect_.x + grid_->tiles_[tileIndex]->rect_.w / 2;
	pos_.y_ = yPos;//grid_->tiles_[tileIndex]->rect_.y + grid_->tiles_[tileIndex]->rect_.h / 2;

	wolfSprite_ = Service<SpriteHandler>::Get()->CreateSprite(filepath, 0, 0,
															  em_->grid_->tiles_[0]->rect_.w - em_->grid_->tiles_[0]->rect_.w / 5,
															  em_->grid_->tiles_[0]->rect_.h - em_->grid_->tiles_[0]->rect_.h / 5);
	spriteFP_ = filepath;
}

void Wolf::Render(SDL_Renderer* renderer)
{
	SDL_Rect dst = { pos_.x_, pos_.y_, wolfSprite_->GetArea().w, wolfSprite_->GetArea().h };
	SDL_RenderCopy(renderer, wolfSprite_->GetTexture(), &wolfSprite_->GetArea(), &dst);
}

void Wolf::Sense()
{
	float distance;
	float shortestDistance;
	closestSheepIndex_ = 0;

	for (int i = 0; i < em_->sheep_.size(); i++)
	{
		distance = 0.0f;
		Sheep* tempSheep = em_->sheep_.at(i);

		distance += abs(pos_.x_ - tempSheep->pos_.x_);
		distance += abs(pos_.y_ - tempSheep->pos_.y_);

		if (i == 0)
			shortestDistance = distance;

		else
		{
			if (distance < shortestDistance)
			{
				shortestDistance = distance;
				closestSheep_ = tempSheep;
			}
		}
	}
}

void Wolf::Decide()
{
}

void Wolf::Act()
{
}

//void Wolf::Roam()
//{
//}
//
//void Wolf::Seek()
//{
//}

void Wolf::Eat()
{
}

void Wolf::Breed()
{
}

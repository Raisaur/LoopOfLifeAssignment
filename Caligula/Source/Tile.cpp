#include "Tile.h"
#include "Service.h"
#include "SpriteHandler.h"

Tile::Tile(int x, int y, int w, int h, const char* filepath, int index)
{
	rect_.x = x;
	rect_.y = y;
	rect_.w = w;
	rect_.h = h;

	dirtSprite_ = Service<SpriteHandler>::Get()->CreateSprite(filepath, 0, 0, rect_.w, rect_.h);
	grass_ = nullptr;

	tileIndex_ = index;
}

void Tile::Render(SDL_Renderer* renderer)
{
	SDL_Rect dst = { rect_.x, rect_.y, dirtSprite_->GetArea().w, dirtSprite_->GetArea().h };
	SDL_RenderCopy(renderer, dirtSprite_->GetTexture(), &dirtSprite_->GetArea(), &dst);


	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
	//SDL_RenderDrawRect(renderer, &rect_);
}

#pragma once 

enum EntityType
{
	BALL,
	PADDLE
};

//  Base Class for all entity types
class Sprite;
class Collider;
struct SDL_Renderer;

class Entity
{
protected:
	int m_x;
	int m_y;
	float m_scale;
	bool m_active; // If inactive, do not update
	bool m_visible; // If inactive, do not render
	Sprite* m_sprite;
	Collider* m_collider;
	EntityType m_type;

public:
	EntityType GetType() { return m_type; };
	bool IsActive() { return m_active; }
	bool IsVisible() { return m_visible; }
	virtual ~Entity() {};
	Collider* GetCollider() { return m_collider; };
	int GetPositionX() { return m_x; };
	int GetPositionY() { return m_y; };
	virtual void Render(SDL_Renderer* p_renderer) {};
	virtual void Update() = 0;
	virtual void OnCollision(Entity* p_other) {};
};
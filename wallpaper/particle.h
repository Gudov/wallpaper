#pragma once

struct Vector2f
{
	float x, y;
};

struct Vector3f
{
	float x, y, z;
};

namespace PS
{
	struct Particle
	{
		float life;
		Vector2f pos;
		Vector2f ppos;
		Vector2f speed;

		Vector3f color;
	};

	void init(unsigned int limit);
	void update( float delta );
	void add(Vector2f pos, Vector2f impulse, Vector3f color, float lifeTime);
}
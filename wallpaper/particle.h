#pragma once

struct Vector2f
{
	float x, y;
};

struct Vector4f
{
	float x, y, z, a;
};

namespace PS
{
	struct Particle
	{
		float life;
		Vector2f pos;
		Vector2f ppos;
		Vector2f speed;

		Vector4f color;
	};

	void init(unsigned int limit);
	void update( float delta );
	void add(Vector2f pos, Vector2f impulse, Vector4f color, float lifeTime);
}
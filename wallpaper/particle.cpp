#include "particle.h"
#include "graphic.h"

#include <math.h>
#include <Windows.h> //only for "NULL" lol

#include <gl.h>
#include <glu.h>
#include <glut.h>

namespace PS
{
	Particle *allParticle = 0;
	unsigned int particleLimit = 0;
	float lifeTime = 1000;

	float distN = 400;
	float F = 0.1;
}


void PS::init(unsigned int limit)
{
	particleLimit = limit;

	allParticle = (Particle *)malloc( sizeof(Particle) * limit );
	ZeroMemory( allParticle, sizeof(Particle) * limit );
}

void PS::update(float delta)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);

	for ( int i = 0; i < PS::particleLimit; i++ )
	{
		if ( PS::allParticle[i].life > 0 )
		{
			Vector2f toCenterN = PS::allParticle[i].pos;
			float dist = sqrt( (toCenterN.x*toCenterN.x) + (toCenterN.y*toCenterN.y));
			toCenterN.x /= dist;
			toCenterN.y /= dist;

			int NDist = PS::distN - dist;

			PS::allParticle[i].speed.x += NDist * toCenterN.x * F;
			PS::allParticle[i].speed.y += NDist * toCenterN.y * F;

			glColor4f(	PS::allParticle[i].color.x,
						PS::allParticle[i].color.y,
						PS::allParticle[i].color.z,
						PS::allParticle[i].color.a);

			glVertex2f(	PS::allParticle[i].pos.x,
						PS::allParticle[i].pos.y);
			glVertex2f(	PS::allParticle[i].ppos.x,
						PS::allParticle[i].ppos.y);

			PS::allParticle[i].ppos.x = PS::allParticle[i].pos.x;
			PS::allParticle[i].ppos.y = PS::allParticle[i].pos.y;

			PS::allParticle[i].pos.x += PS::allParticle[i].speed.x;
			PS::allParticle[i].pos.y += PS::allParticle[i].speed.y;

			PS::allParticle[i].life -= delta;
		}
	}

	glEnd();

	glAccum(GL_ACCUM, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glAccum(GL_RETURN, 1);
	glAccum(GL_MULT, 0.90);
	//glAccum(GL_ACCUM, 0.75);
	//glClear(GL_ACCUM_BUFFER_BIT);
	//glAccum(GL_ACCUM, 1);

	SwapBuffers(context);
}

void PS::add(Vector2f pos, Vector2f impulse, Vector4f color, float lifeTime = 0)
{
	for (int i = 0; i < PS::particleLimit; i++)
	{
		if (PS::allParticle[i].life <= 0)
		{
			if (lifeTime > 0)
			{
				PS::allParticle[i].life = lifeTime;
			}
			else
			{
				PS::allParticle[i].life = PS::lifeTime;
			}

			PS::allParticle[i].pos = pos;
			PS::allParticle[i].ppos = pos;
			PS::allParticle[i].speed = impulse;
			PS::allParticle[i].color = color;

			break;
		}
	}
}

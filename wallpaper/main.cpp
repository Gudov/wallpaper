#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <Windows.h>

#include "graphic.h"
#include "particle.h"

int main()
{
	initGL();
	PS::init(1000000);

	while (true)
	{
		PS::update(20);

		Sleep(20);

		for (int i = 0; i < 3; i++)
		{
			int r = rand() % 200 + 1;

			Vector2f pos = { 250,0 };
			pos.x += ((float)(100 - r) / 100.f) * 15;
			pos.y += ((float)(100 - (rand() % 200 + 1)) / 100.f) * 5;

			Vector2f impulse = { 0,10 };
			impulse.x += ((float)(100 - r) / 100.f) * -2;

			//float colorM = (((float)(200 - r)) / 400) + 0.5;
			float colorM = 1;
			Vector3f color = { 0.15 * colorM,0.25 * colorM,1 * colorM };

			if (r > 180)
			{
				//color = { 1,0,0 };
				//impulse.y *= -1;
			}

			PS::add(pos,
				impulse,
				color,
				20000);
		}
	}

	return 0;
}
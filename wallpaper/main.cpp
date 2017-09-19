#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <Windows.h>

#include "graphic.h"
#include "particle.h"

int main()
{
	initGL();
	PS::init(50000);

	while (true)
	{
		PS::update(20);

		Sleep(20);

		for (int i = 0; i < 3; i++)
		{
			int r = rand() % 200 + 1;

			Vector2f pos = { 400,0 };

			Vector2f impulse = { 0,15 };
			r = rand() % 200 + 1;
			impulse.y += ((float)(100 - r) / 100.f) * 10;
			r = rand() % 200 + 1;
			impulse.x += ((float)(100 - r) / 100.f) * 15;

			float colorM = ((float)(100 - r) / 100.f);
			colorM = (colorM > 0) ? (1 - colorM) : (colorM + 1);
			colorM = colorM * colorM;
			Vector4f color = { 0.15, 0.25, 1, 1 * colorM };

			PS::add(pos,
				impulse,
				color,
				20000);
		}
	}

	return 0;
}
#include "graphic.h"

#include <gl.h>
#include <glu.h>
#include <glut.h>

static PIXELFORMATDESCRIPTOR pfd =
{
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW |
	PFD_SUPPORT_OPENGL |
	PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	16,
	0, 0, 0, 0, 0, 0,
	0,
	0,
	1,
	1, 1, 1, 1,
	16,
	0,
	0,
	PFD_MAIN_PLANE,
	0,
	0, 0, 0 
};

HDC context = NULL;
HWND background = NULL;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	HWND shelldll = FindWindowExA(hwnd, NULL, "SHELLDLL_DefView", NULL);

	if (shelldll != NULL)
	{
		HWND listview = FindWindowExA(NULL, hwnd, "WorkerW", NULL);
		background = listview;
	}
	return true;
}

void initGL()
{ 
	PDWORD_PTR res = 0;
	HWND progman = FindWindow("Progman", NULL);
	SendMessageTimeout(progman,
		0x52C,
		NULL,
		NULL,
		SMTO_NORMAL,
		1000,
		res);

	EnumWindows(&EnumWindowsProc, NULL);

	context = GetDC(background);

	GLint  iPixelFormat;
	iPixelFormat = ChoosePixelFormat(context, &pfd);
	SetPixelFormat(context, iPixelFormat, &pfd);

	wglMakeCurrent(context, NULL);
	HGLRC cont = wglCreateContext(context);
	wglMakeCurrent(context, cont);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int totalX, totalY;
	int mainX, mainY;

	totalX = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	totalY = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	mainX = GetSystemMetrics(SM_CXSCREEN);
	mainY = GetSystemMetrics(SM_CYSCREEN);

	gluOrtho2D(-(mainX/2), totalX - (mainX / 2), -(mainY/2), totalY - (mainY/2));
	//glViewport(0, 0, GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN));

	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
	glRectf(-25, -25, 25, 25);
	glPointSize(2);
	glLineWidth(1.5);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POINTS);
	glVertex2f(0, 0);
	glEnd();
	SwapBuffers(context);
}
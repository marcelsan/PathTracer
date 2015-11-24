#ifndef __RENDERING_MANAGER_H__
#define __RENDERING_MANAGER_H__

#include "Scene.h"
#include "Image.h"

#define GL_MAX_NUM_LIGHTS 8

namespace RenderingManager
{
	int width;
	int height;

	const int GLlights[GL_MAX_NUM_LIGHTS] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

	GLfloat modelview[16];
	GLfloat projection[16];

	void init(int w, int h)
	{
		width = w;
		height = h;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, (float)width / height, 1, 100000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void render(
		const Scene& scene, 
		const GLSmoothCamera& camera, 
		const Image<>& background)
	{
		width = background.getWidth();
		height = background.getHeight();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, (float)width / height, 1, 10000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		camera.apply();

		glEnable(GL_DEPTH_TEST);
		//renderBackground(background);
		glColor3f(0.f, 1.f, 0.f);
		renderAxis();
		plot(scene);
	}
};

#endif
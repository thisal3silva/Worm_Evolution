
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "Draw.h"
#include "Worm.h"
#include "CircleOfLife.h"

#define Evolution_Speed 500
#define Screen_gran 1000
#define Population_Size 50

using namespace std;

CircleOfLife God(50);

void changeViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Screen_gran, 0, Screen_gran, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	God.showPopulation();
	glutSwapBuffers();
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/Evolution_Speed , timer , 0);
}

void init()
{
	glClearColor(0, 0, 0, 1);
}

int main(int argc, char* argv[]) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA| GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Worm Evolution");
	glutReshapeFunc(changeViewPort);


	glutDisplayFunc(update);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	glutTimerFunc(0, timer, 0);
	init();

	glutMainLoop();
	return 0;
}
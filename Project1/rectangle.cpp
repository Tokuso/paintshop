/*
#ifndef WIN32 //if using windows then do windows specific stuff.
#define WIN32_LEAN_AND_MEAN //remove MFC overhead from windows.h which can cause slowness
#define WIN32_EXTRA_LEAN

#include <windows.h>
#endif

#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <math.h>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::end;

int left_mouse_down = 0;
vector <GLfloat> rectangle_position(4, 0.0f);
vector <vector<GLfloat>> rectangles;

void draw_rectangles() {
	glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
	//glBegin(GL_QUADS);
	glRectf(
		rectangle_position[0],
		rectangle_position[1],
		rectangle_position[2],
		rectangle_position[3]
	);
	//glEnd();
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	//glBegin(GL_QUADS);
	for (vector<GLfloat> coords : rectangles) {
		glRectf(
			coords[0], 
			coords[1], 
			coords[2], 
			coords[3]
		);
	}
	//glEnd();
	
}

void OnMouseClick(int button, int state, int x, int y) {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	GLfloat x_pos = (float(x) - width / 2) / (width / 2);
	GLfloat y_pos = (0 - 1) * (float(y) - height / 2) / (height / 2);
	cout << x_pos << "\t" << y_pos << "\t" << state << "\t" << button << endl;
	if (state == 0) {
		left_mouse_down = 1;
		rectangle_position[0] = x_pos;
		rectangle_position[1] = y_pos;
	}
	else {
		left_mouse_down = 0;
		
		rectangles.push_back({
			rectangle_position[0],
			rectangle_position[1],
			rectangle_position[2],
			rectangle_position[3]
		});
		glutPostRedisplay();
		for (vector<GLfloat> coords : rectangles) {
			GLfloat x1 = coords[0];
			GLfloat y1 = coords[1];
			GLfloat x2 = coords[2];
			GLfloat y2 = coords[3];
			cout << x1 << "\t" << y1 << "\t" << x2 << "\t" << y2 << endl;;
		}
	}
}

void motion(int x, int y) {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	GLfloat x_pos = (float(x) - width / 2) / (width / 2);
	GLfloat y_pos = (0 - 1) * (float(y) - height / 2) / (height / 2);
	if (left_mouse_down) {
		rectangle_position[2] = x_pos;
		rectangle_position[3] = y_pos;
		glutPostRedisplay();
	}
}

// Handler for window-repaint event. Call back when the window first appears and
// whenever the window needs to be re-painted.
void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	draw_rectangles();

	glFlush();  // Render now
}

// Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(800, 800);   // Set the window's initial width & height
	glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
										   //glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutMouseFunc(OnMouseClick);
	glutMotionFunc(motion);
	glutMainLoop();           // Enter the infinitely event-processing loop
	return 0;
}
*/
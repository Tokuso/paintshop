#ifndef WIN32 //if using windows then do windows specific stuff.
#define WIN32_LEAN_AND_MEAN //remove MFC overhead from windows.h which can cause slowness
#define WIN32_EXTRA_LEAN

#include <windows.h>
#endif

//I sincerely do not understand why intellisense suddently works now
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
vector <GLfloat> point_position = { 0.0f, 0.0f };
vector <vector<GLfloat>> points;
vector <vector<vector<GLfloat>>> scribbles;

void draw_points() {
	glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	for (vector <GLfloat> coords : points) {
		float x = coords[0];
		float y = coords[1];
		glVertex2f(x, y);
	}
	glEnd();
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	for (vector <vector<GLfloat>> stored_points : scribbles) {
		glBegin(GL_LINE_STRIP);
		for (vector <GLfloat> coords : stored_points) {
			float x = coords[0];
			float y = coords[1];
			glVertex2f(x, y);
		}
		glEnd();
	}
	glutPostRedisplay();
}

void OnMouseClick(int button, int state, int x, int y) {
	cout << x << "\t" << y << "\t" << state << "\t" << button << endl;
	if (state == 0) {
		left_mouse_down = 1;
	}
	else {
		left_mouse_down = 0;
		scribbles.push_back(points);
		points.clear();
	}
}

void motion(int x, int y) {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	GLfloat x_pos = (float(x) - width / 2) / (width / 2);
	GLfloat y_pos = (0 - 1) * (float(y) - height / 2) / (height / 2);
	if (left_mouse_down) {
		point_position[0] = x_pos;
		point_position[1] = y_pos;
		points.push_back({ x_pos, y_pos });
		glutPostRedisplay();
	}
}

// Handler for window-repaint event. Call back when the window first appears and
// whenever the window needs to be re-painted.
void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

	draw_points();

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
	glLineWidth(1);
	glutMainLoop();           // Enter the infinitely event-processing loop
	return 0;
}

#ifndef WIN32
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#endif

#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <math.h>
#include <vector>
#include <tuple>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::end;
using std::tuple;
using std::make_tuple;
using std::tie;

int left_mouse_down = 0;
int mode = 0;
vector <GLfloat> line_position(4, 0.0f);
vector <vector<GLfloat>> lines;
vector <GLfloat> rectangle_position(4, 0.0f);
vector <vector<GLfloat>> rectangles;
vector <GLfloat> point_position = { 0.0f, 0.0f };
vector <vector<GLfloat>> points;
vector <vector<vector<GLfloat>>> scribbles;

// Just a function to clear the CLI during debugging.
void clrscr() {
	system("cls");
}

// Tells GL to draw line segments based on the captured and current coordinates.
void draw_lines() {
	glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(
		line_position[0],
		line_position[1]
	);
	glVertex2f(
		line_position[2],
		line_position[3]
	);
	glEnd();
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	for (vector<GLfloat> coords : lines) {
		glVertex2f(
			coords[0],
			coords[1]
		);
		glVertex2f(
			coords[2],
			coords[3]
		);
	}
	glEnd();
}

// Tells GL to draw rectangles based on the captured and current coordinates.
void draw_rectangles() {
	glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
	glRectf(
		rectangle_position[0],
		rectangle_position[1],
		rectangle_position[2],
		rectangle_position[3]
	);
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	for (vector<GLfloat> coords : rectangles) {
		glRectf(
			coords[0], 
			coords[1], 
			coords[2], 
			coords[3]
		);
	}
	
}

// Tells GL to draw points (scribbles) based on the captured and current coordinates.
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

// Capturing mouse keys and cursor position when a key is pressed or depressed.
void OnMouseClick(int button, int state, int x, int y) {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	GLfloat x_pos = (float(x) - width / 2) / (width / 2);
	GLfloat y_pos = (0 - 1) * (float(y) - height / 2) / (height / 2);
	if (state == 0) {
		clrscr();
		cout << "Mouse button PRESSED" << endl;
		cout << "x1\ty1\tstate\tbutton" << endl;
		cout << x_pos << "\t" << y_pos << "\t" << state << "\t" << button << endl;
		left_mouse_down = 1;
		switch (mode) {
			case 0:
				line_position[0] = x_pos;
				line_position[1] = y_pos;
				line_position[2] = x_pos;
				line_position[3] = y_pos;
				break;
			case 1:
				rectangle_position[0] = x_pos;
				rectangle_position[1] = y_pos;
				rectangle_position[2] = x_pos;
				rectangle_position[3] = y_pos;
				break;
			case 2:
				break;
			default:
				break;
		}
		
	}
	else {
		cout << "Mouse button DEPRESSED" << endl;
		cout << "x2\ty2\tstate\tbutton" << endl;
		cout << x_pos << "\t" << y_pos << "\t" << state << "\t" << button << endl;
		left_mouse_down = 0;
		switch (mode) {
			case 0:
				lines.push_back({
					line_position[0],
					line_position[1],
					line_position[2],
					line_position[3]
				});
				cout << "Points stored in the vectors: " << endl;
				cout << "x1\ty1\tx2\ty2" << endl;
				for (vector<GLfloat> coords : lines) {
					GLfloat x1 = coords[0];
					GLfloat y1 = coords[1];
					GLfloat x2 = coords[2];
					GLfloat y2 = coords[3];
					cout << x1 << "\t" << y1 << "\t" << x2 << "\t" << y2 << endl;;
				}
				break;
			case 1: 
				rectangles.push_back({
					rectangle_position[0],
					rectangle_position[1],
					rectangle_position[2],
					rectangle_position[3]
				});
				for (vector<GLfloat> coords : rectangles) {
					GLfloat x1 = coords[0];
					GLfloat y1 = coords[1];
					GLfloat x2 = coords[2];
					GLfloat y2 = coords[3];
					cout << x1 << "\t" << y1 << "\t" << x2 << "\t" << y2 << endl;;
				}
				break;
			case 2:
				scribbles.push_back(points);
				points.clear();
				break;
			default:
				break;
		}
		glutPostRedisplay();
	}
}

// Capturing the current location of the cursor when it moves.
void motion(int x, int y) {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	GLfloat x_pos = (float(x) - width / 2) / (width / 2);
	GLfloat y_pos = (0 - 1) * (float(y) - height / 2) / (height / 2);
	if (left_mouse_down) {
        // Maybe we can cut this switch tree down a bit by using unified position globals?
		switch (mode) {
			case 0:
				line_position[2] = x_pos;
				line_position[3] = y_pos;
				glutPostRedisplay();
				break;
			case 1:
				rectangle_position[2] = x_pos;
				rectangle_position[3] = y_pos;
				glutPostRedisplay();
				break;
			case 2:
				point_position[0] = x_pos;
				point_position[1] = y_pos;
				points.push_back({ x_pos, y_pos });
				glutPostRedisplay();
				break;
			default:
				break;
		}
	}
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
	
	draw_lines();
	draw_rectangles();
	draw_points();

	glFlush();  // Render now
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case '0':
			mode = 0;
			break;
		case '1':
			mode = 1;
			break;
		case '2':
			mode = 2;
			break;
		default:
			break;
	}
}


// GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("PaintShop");
										   //glutInitWindowPosition(50, 50); // Top left corner is reference
	glutDisplayFunc(display);
	glutMouseFunc(OnMouseClick);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glLineWidth(3);
	glutMainLoop();
	return 0;
}

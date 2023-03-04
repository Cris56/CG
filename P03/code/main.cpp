#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// Compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// Return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawCylinder(float radius, float height, int slices) {
	glPolygonMode(GL_FRONT, GL_LINE);
	int n = slices;

	glBegin(GL_TRIANGLES);

	// Cima
	glColor3f(1.0f, 0.0f, 1.0f);
	float x = 0, z = radius;
	for (int i = 0; i < n; i++) {
		float a = (i+1) * ((2 * M_PI) / n);
		float b = radius * sin(a);
		float c = radius * cos(a);

		glVertex3f(0.0f, height / 2, 0.0f);
		glVertex3f(x, height / 2, z);
		glVertex3f(b, height / 2, c);
		
		x = b;
		z = c;
	}

	// Baixo
	glColor3f(0.0f, 0.0f, 1.0f);
	x = 0, z = radius;
	float ainit = 0;
	for (int i = 0; i < n; i++) {
		float a = (i + 1) * ((2 * M_PI) / n); 
		if (i == 0) {
			ainit = a/2;
			x = radius * sin(ainit);
			z = radius * cos(ainit);
		}
		a += ainit;
		float b = radius * sin(a);
		float c = radius * cos(a);

		glVertex3f(0.0f, -height / 2, 0.0f);
		glVertex3f(b, -height / 2, c);
		glVertex3f(x, -height / 2, z);

		x = b;
		z = c;
	}

	// Lados V
	glColor3f(0.0f, 1.0f, 0.0f);
	x = 0, z = radius;
	for (int i = 0; i < n; i++) {
		float a = (i + 1) * ((2 * M_PI) / n);
		float b = radius * sin(a);
		float c = radius * cos(a);
		if (i == 0) {
			ainit = a / 2;
		}
		glVertex3f(radius * sin(a-ainit), -height / 2, radius * cos(a-ainit));
		glVertex3f(b, height / 2, c);
		glVertex3f(x, height / 2, z);

		x = b;
		z = c;
	}
	// Lados ^
	x = 0, z = radius;
	for (int i = 0; i < n; i++) {
		float a = (i + 1) * ((2 * M_PI) / n);
		if (i == 0) {
			ainit = a / 2;
			x = radius * sin(ainit);
			z = radius * cos(ainit);
		}
		glVertex3f(radius * sin(a), height / 2, radius * cos(a));
		a += ainit;
		float b = radius * sin(a);
		float c = radius * cos(a);
		glVertex3f(x, -height / 2, z);
		glVertex3f(b, -height / 2, c);

		x = b;
		z = c;
	}

	glEnd();	
}

float verangle = 0;
float horangle = 0;
float rad = 5;

void renderScene(void) {

	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float x = rad * cosf(verangle) * sinf(horangle);
	float y = rad * sinf(verangle);
	float z = rad * cosf(verangle) * cosf(horangle);

	// Set the camera
	glLoadIdentity();
	gluLookAt(x,y,z, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawCylinder(1,2,10);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
	switch (c) {
		case 'a':
			horangle -= 0.1;
			break;
		case 'w':
			if (verangle + 0.1 <= 1.5) verangle += 0.1;
			break;
		case 's':
			if (verangle - 0.1 >= -1.5) verangle -= 0.1;
			break;
		case 'd':
			horangle += 0.1;
			break;
	}
	glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {
	if (key == GLUT_KEY_UP) {
		if (rad >= 2) rad -= 0.1;
	}
	else if (key == GLUT_KEY_DOWN) {
		if (rad <= 8) rad += 0.1;
	}
	glutPostRedisplay();
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// Enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// Return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

float ang = 0, xt = 0, yt = 1, zt = 0;

void renderScene(void) {

	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	// Axis drawing
	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

	// Geometric transformations
	glTranslatef(xt, 0, zt);
	glRotatef(ang, 0, 1, 0);
	glScalef(1, yt, 1);

	// Pyramid drawing instructions
	glBegin(GL_TRIANGLES);
		// front
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		// left
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		// back
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		// right
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		// bottom 1
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		// bottom 2
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
	glEnd();

	// End of frame
	glutSwapBuffers();
}



// Functions to process keyboard events
void letterkeys(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':
			zt += -0.1;
			break;
		case 'a':
			xt += -0.1;
			break;
		case 's':
			zt += 0.1;
			break;
		case 'd':
			xt += 0.1;
			break;
		case 'q':
			// rotate CCW
			ang += 5;
			break;
		case 'e':
			// rotate CW
			ang += -5;
			break;
		case 'f':
			// FILL mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case 'l':
			// LINE mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 'p':
			// POINT mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
	}
	glutPostRedisplay();
}

void specialkeys(int key_code, int x, int y) {
	if (key_code == GLUT_KEY_UP) {
		yt += 0.1;
	}
	else if (key_code == GLUT_KEY_DOWN) {
		yt -= 0.1;
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
	
// Registration of the keyboard callbacks
	glutKeyboardFunc(letterkeys);
	glutSpecialFunc(specialkeys);

// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// Enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}

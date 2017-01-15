#include "GL/freeglut.h"

// Window Parameters
int width = 1280;
int height = 800;

/************************************************************************/
/* App Render Function                                                                     */
/************************************************************************/
void renderApp() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
		glVertex3f(0.0, 0.5, 0.0);
	glEnd();

	glutSwapBuffers();
}

/************************************************************************/
/* App Main Function : Entry Point                                                                     */
/************************************************************************/
int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Shader Framework");

	glutDisplayFunc(renderApp);
	glutMainLoop();
	return 1;
}
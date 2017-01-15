#include "GL/freeglut.h"
#include "app/manager/ShaderAppManager.hpp"

// Window Parameters
int width = 1280;
int height = 800;

// Shader App Manager
ShaderAppManager* m_appManager;

/************************************************************************/
/* 
	This function handles window resize
*/
/************************************************************************/
void resizeWindow(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio = 1.0f * (w / h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

/************************************************************************/
/* App Main Function : Entry Point                                                                     */
/************************************************************************/
int main(int argc, char** argv) {

	glutInit(&argc, argv); // initialize glut

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // set display mode
	glutInitWindowPosition(100, 100); // set window position on screen
	glutInitWindowSize(width, height); // set window size
	glutCreateWindow("Shader Framework"); // set window title

	// Initialize App Manager
	m_appManager = new ShaderAppManager();
	m_appManager->init();

	// register window resize function
	glutReshapeFunc(resizeWindow);

	// register rendering function
	glutDisplayFunc(m_appManager->update);

	// register rendering function to call in app's idle condition
	glutIdleFunc(m_appManager->update);

	// register function for keyboard inputs
	glutKeyboardFunc(m_appManager->onNormalKeyboardKeyPressed);
	glutSpecialFunc(m_appManager->onSpecialKeyboardKeyPressed);

	// register function for mouse inputs
	glutMouseFunc(m_appManager->onMouseButtonDown);
	glutMotionFunc(m_appManager->onMouseMoved);

	glutMainLoop();
	return 1;
}
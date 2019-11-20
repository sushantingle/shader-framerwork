#include "app/manager/ShaderAppManager.hpp"
#include <memory>
// Window Parameters
int width = 800;
int height = 600;

// Shader App Manager
std::unique_ptr<ShaderAppManager> m_appManager;

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

void displayFunc() {
	m_appManager->update();
}

void onNormalKeyboardKeyPressed(unsigned char key, int x, int y) {
	m_appManager->onNormalKeyboardKeyPressed(key, x, y);
}

void onSpecialKeyboardKeyPressed(int key, int x, int y) {
	m_appManager->onSpecialKeyboardKeyPressed(key, x, y);
}

void onMouseButtonDown(int button, int state, int x, int y) {
	m_appManager->onMouseButtonDown(button, state, x, y);
}

void onMouseMoved(int x, int y) {
	m_appManager->onMouseMoved(x, y);
}

void processGlutMenuEvents(int menuId) {
	m_appManager->onMenuItemClicked(menuId);
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
	m_appManager = std::make_unique<ShaderAppManager>();
	m_appManager->init(width, height);

	// register window resize function
	glutReshapeFunc(resizeWindow);

	// register rendering function
	glutDisplayFunc(displayFunc);

	// register rendering function to call in app's idle condition
	glutIdleFunc(displayFunc);

	// register function for keyboard inputs
	glutKeyboardFunc(onNormalKeyboardKeyPressed);
	glutSpecialFunc(onSpecialKeyboardKeyPressed);

	// register function for mouse inputs
	glutMouseFunc(onMouseButtonDown);
	glutMotionFunc(onMouseMoved);

	glutMainLoop();
	return 1;
}
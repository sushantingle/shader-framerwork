#include "ShaderDiffuse.hpp"

extern void processGlutMenuEvents(int option);

void ShaderDiffuse::init() {
	
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 50.0f };
	GLfloat light0_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat light1_position[] = { 0.0f, 1.0f, 1.0f, 0.0f };
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// Set shader parameters
	setShader("diffuse/diffuse.vert", "diffuse/diffuse.frag");
}

void ShaderDiffuse::uninit() {
	glDisable(GL_DEPTH_TEST);
}

void ShaderDiffuse::update() {
	m_rotationAngle += 0.1f;
}

void ShaderDiffuse::render() {

	glLoadIdentity();

	gluLookAt(m_cameraPosition.x, 1.0f, m_cameraPosition.z,
		m_cameraPosition.x + m_cameraRotation.x, 1.0f, m_cameraPosition.z + m_cameraRotation.z,
		0.0f, 1.0f, 0.0f);

	glRotatef(m_cameraAngle, 0.0f, 1.0f, 0.0f);
	
	glPushMatrix();
		glRotatef(m_rotationAngle, 0.0f, 1.0f, 0.0f);
		glutSolidTeapot(2.0f);
	glPopMatrix();

}

int ShaderDiffuse::createSpecialMenu() {

	int customMenu = -1;

	// Implement custom special menus here

	return customMenu;
}

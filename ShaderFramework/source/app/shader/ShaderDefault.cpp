#include "ShaderDefault.hpp"


void ShaderDefault::init() {
	glEnable(GL_DEPTH_TEST);

	setShader("toon.vert", "toon.frag");
}

void ShaderDefault::uninit() {

}

void ShaderDefault::update() {

}

void ShaderDefault::render() {

	glLoadIdentity();

	gluLookAt(m_cameraPosition.x, 1.0f, m_cameraPosition.z,
		m_cameraPosition.x + m_cameraRotation.x, 1.0f, m_cameraPosition.z + m_cameraRotation.z,
		0.0f, 1.0f, 0.0f);

	glRotatef(m_cameraAngle, 0.0f, 1.0f, 0.0f);

	glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	// Draw 36 SnowMen
	for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0f, 0, j * 10.0f);
			renderSnowMan();
			glPopMatrix();
		}
}

void ShaderDefault::renderSnowMan() {
	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}
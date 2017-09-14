#include "TextureTest.hpp"

void TextureTest::init() {
	glEnable(GL_DEPTH_TEST);
	setShader("diffuse/diffuse.vert", "diffuse/diffuse.frag");
}

void TextureTest::uninit() {
	glDisable(GL_DEPTH_TEST);
}

void TextureTest::update() {

}

void TextureTest::render() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluLookAt(m_cameraPosition.x, 1.0f, m_cameraPosition.z,
		m_cameraPosition.x + m_cameraRotation.x, 1.0f, m_cameraPosition.z + m_cameraRotation.z,
		0.0f, 1.0f, 0.0f);

	glRotatef(m_cameraAngle, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glutSolidTeapot(2.0f);
	glPopMatrix();
}
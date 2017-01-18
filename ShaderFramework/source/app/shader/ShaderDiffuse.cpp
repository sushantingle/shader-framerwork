#include "ShaderDiffuse.hpp"

void ShaderDiffuse::init() {
	glEnable(GL_DEPTH_TEST);

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
		glTranslated(0.0f, 0.0f, -50.0f);
		glutSolidSphere(10.0f, 100, 100);
	glPopMatrix();

}

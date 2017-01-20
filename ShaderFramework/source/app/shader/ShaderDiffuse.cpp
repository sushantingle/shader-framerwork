#include "ShaderDiffuse.hpp"

void ShaderDiffuse::init() {
	m_time = 0.0f;
	glEnable(GL_DEPTH_TEST);

	// Set shader parameters
	setShader("diffuse/diffuse.vert", "diffuse/diffuse.frag");

	loc = glGetUniformLocation(getProgramId(), "time");
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

	//glRotatef(m_cameraAngle, 0.0f, 1.0f, 0.0f);

	//glPushMatrix();
		glUniform1f(loc, m_time);
		//glTranslated(0.0f, 0.0f, -50.0f);
		glutSolidSphere(10.0f, 100, 100);
		m_time += 0.1f;
	//glPopMatrix();

}

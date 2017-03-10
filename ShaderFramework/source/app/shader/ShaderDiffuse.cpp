#include "ShaderDiffuse.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#define MENU_ID_DIFFUSE_SHADER				1
#define MENU_ID_DIFFUSE_PER_PIXEL_SHADER	2
#define MENU_ID_DIFFUSE_POINT_LIGHT			3
#define MENU_ID_DIFFUSE_SPOT_LIGHT			4

extern void processGlutMenuEvents(int option);

GLfloat light0_position[] = { 1.0f, 1.0f, 0.0f, 0.0f };

void ShaderDiffuse::init() {

	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 50.0f };
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Set shader parameters
	setShader(m_defaultShaderData, "diffuse/diffuse.vert", "diffuse/diffuse.frag");
}

void ShaderDiffuse::uninit() {
	glDisable(GL_DEPTH_TEST);
}

void ShaderDiffuse::update() {
	m_rotationAngle += 0.1f;
}

void ShaderDiffuse::render() {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	gluLookAt(m_cameraPosition.x, 1.0f, m_cameraPosition.z,
		m_cameraPosition.x + m_cameraRotation.x, 1.0f, m_cameraPosition.z + m_cameraRotation.z,
		0.0f, 1.0f, 0.0f);

	m_projectionMatrix = glm::perspective(45.0f, (float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.0f);
	m_viewMatrix = glm::lookAt(glm::vec3(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z), 
		glm::vec3(m_cameraPosition.x + m_cameraRotation.x, 1.0f, m_cameraPosition.z + m_cameraRotation.z), 
		glm::vec3(0, 1, 0));
	
	glUniformMatrix4fv(glGetUniformLocation(m_defaultShaderData.programId, "projection"), 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_defaultShaderData.programId, "view"), 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
	
	glm::mat4 model;
	glRotatef(m_cameraAngle, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
			//glPushMatrix();
			glTranslatef(i*10.0f, 0, j * 10.0f);
			//glRotatef(m_rotationAngle, 0.0f, 1.0f, 0.0f);
			model = glm::mat4();
			model = glm::translate(model, glm::vec3(i*10.0f, 0, j * 10.0f));
			glUniformMatrix4fv(glGetUniformLocation(m_defaultShaderData.programId, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glutSolidTeapot(2.0f);
			//glPopMatrix();
		}

}

int ShaderDiffuse::createSpecialMenu() {

	int customMenu = glutCreateMenu(processGlutMenuEvents);

	// Implement custom special menus here
	addMenuEntry("Diffuse", MENU_ID_DIFFUSE_SHADER);
	addMenuEntry("Diffuse Per Pixel", MENU_ID_DIFFUSE_PER_PIXEL_SHADER);
	addMenuEntry("Diffuse Point Light", MENU_ID_DIFFUSE_POINT_LIGHT);
	addMenuEntry("Diffuse Spot Light", MENU_ID_DIFFUSE_SPOT_LIGHT);

	return customMenu;
}

void ShaderDiffuse::processSpecialMenuEvents(int menuId) {
	switch (menuId)
	{
	case MENU_ID_DIFFUSE_SHADER:
		switchToShader("diffuse/diffuse.vert", "diffuse/diffuse.frag");
		break;
	case MENU_ID_DIFFUSE_PER_PIXEL_SHADER:
		switchToShader("diffuse/diffuseperpixel.vert", "diffuse/diffuseperpixel.frag");
		break;
	case MENU_ID_DIFFUSE_POINT_LIGHT:
		switchToShader("diffuse/diffuseperpixelpointlight.vert", "diffuse/diffuseperpixelpointlight.frag");
		break;
	case MENU_ID_DIFFUSE_SPOT_LIGHT:
		switchToShader("diffuse/diffuseperpixelspotlight.vert", "diffuse/diffuseperpixelspotlight.frag");
		break;
	}
}

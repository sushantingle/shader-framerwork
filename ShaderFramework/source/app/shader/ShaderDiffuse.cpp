#include "ShaderDiffuse.hpp"

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
	addShader(0, "diffuse/diffuse.vert", "diffuse/diffuse.frag","");
	addShader(1, "diffuse/diffuseperpixel.vert", "diffuse/diffuseperpixel.frag", "");
	addShader(2, "diffuse/diffuseperpixelpointlight.vert", "diffuse/diffuseperpixelpointlight.frag", "");
	addShader(3, "diffuse/diffuseperpixelspotlight.vert", "diffuse/diffuseperpixelspotlight.frag", "");

	m_shaders[0]->useProgram();
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

	glRotatef(m_cameraAngle, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
		glRotatef(m_rotationAngle, 0.0f, 1.0f, 0.0f);
		glutSolidTeapot(2.0f);
	glPopMatrix();

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
		m_shaders[0]->useProgram();
		break;
	case MENU_ID_DIFFUSE_PER_PIXEL_SHADER:
		m_shaders[1]->useProgram();
		break;
	case MENU_ID_DIFFUSE_POINT_LIGHT:
		m_shaders[2]->useProgram();
		break;
	case MENU_ID_DIFFUSE_SPOT_LIGHT:
		m_shaders[3]->useProgram();
		break;
	}
}

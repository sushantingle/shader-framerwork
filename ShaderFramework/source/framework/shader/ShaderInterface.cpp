#include "ShaderInterface.hpp"
#include <fstream>
#include "../framework/datatype/fsVector.hpp"
#include <string>

extern void processGlutMenuEvents(int option);
namespace sf {

	#define SHADER_ABSOLUTE_PATH "../source/app/resource/shader/"

	// Menu Defines
	#define MENU_ID_WIREFRAME_VIEW	1001
	#define MENU_ID_SOLID_VIEW		1002

	

	ShaderInterface::ShaderInterface() {
		m_programId = 0;
		m_vertexShaderId = 0;
		m_fragmentShaderId = 0;
		m_geometryShaderId = 0;
	}

	ShaderInterface::~ShaderInterface() {
		for (std::map<int, Shader*>::iterator it = m_shaders.begin(); it != m_shaders.end(); it++)
			delete it->second;
		m_shaders.clear();
	}

	//////////////////////////////////////////////////////////////////////////
	// Basic Initialisation
	//////////////////////////////////////////////////////////////////////////
	/*!
	\callgraph
	*/
	void ShaderInterface::baseInit(int _width, int _height) {
		// Do common implementation here
		m_windowWidth	= _width;
		m_windowHeight	= _height;

		m_cameraPosition = Vector3<float>(0.0f, 0.0f, 15.0f);
		m_cameraRotation = Vector3<float>(0.0f, 0.0f, -1.0f);
		m_cameraSpeed	= 0.5f;
		m_cameraAngle	= 0.0f;
		m_deltaAngle	= 0.0f;
		m_xOrigin		= -1;

		createDefaultMenu();

		glewInit();
		// call init of derived class
		init(); // derived->init();
	}

	void ShaderInterface::baseUninit() {
		// Do common implementation here
		
		destroyMenu();
		// call uninit of derived class
		uninit();  // derived->uninit();
	}

	void ShaderInterface::baseUpdate() {
		// Do common implementation here

		// call update of derived class
		update();  // derived->update();
	}

	void ShaderInterface::baseRender() {
		// do common implementation here
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		// call render of derived class
		render();  // derived->render();

		glutSwapBuffers();
	}

	//////////////////////////////////////////////////////////////////////////
	// Menu Initialization
	//////////////////////////////////////////////////////////////////////////

	void ShaderInterface::createDefaultMenu() {

		int defaultMenu = glutCreateMenu(processGlutMenuEvents);
		addMenuEntry("Wireframe", MENU_ID_WIREFRAME_VIEW);
		addMenuEntry("Solid", MENU_ID_SOLID_VIEW);

		int customMenu = createSpecialMenu();

		int menu = glutCreateMenu(processGlutMenuEvents);
		glutAddSubMenu("default", defaultMenu);
		if (customMenu != -1)
			glutAddSubMenu("Custom Menu", customMenu);

		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}

	void ShaderInterface::addMenuEntry(const char* menuName, int menuId) {
		glutAddMenuEntry(menuName, menuId);
		m_menuIds.push_back(menuId);
	}

	void ShaderInterface::processMenuEvents(int menuId) {
		switch (menuId)
		{
		case MENU_ID_WIREFRAME_VIEW:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case MENU_ID_SOLID_VIEW:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		}

		processSpecialMenuEvents(menuId);
	}

	void ShaderInterface::destroyMenu() {
		for (int id : m_menuIds) {
			glutRemoveMenuItem(id);
		}

		m_menuIds.clear();
		glutDetachMenu(GLUT_RIGHT_BUTTON);
	}

	void ShaderInterface::addShader(int id, const char* vert, const char* frag, const char* geom)
	{
		Shader* shader = new Shader(vert, frag, geom);
		m_shaders.insert(std::pair<int, Shader*>(id, shader));
	}
	//////////////////////////////////////////////////////////////////////////
	// Camera Projection
	//////////////////////////////////////////////////////////////////////////
	void ShaderInterface::setOrthographicProjection() {
		glMatrixMode(GL_PROJECTION);

		glPushMatrix();
		glLoadIdentity();

		gluOrtho2D(0, m_windowWidth, m_windowHeight, 0);

		glScalef(1, -1, 1);

		glTranslatef(0, -static_cast<float>(m_windowHeight), 0);

		glMatrixMode(GL_MODELVIEW);
	}

	void ShaderInterface::restorePerspectiveProjection() {
		glMatrixMode(GL_PROJECTION);

		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
	}

	//////////////////////////////////////////////////////////////////////////
	// Processing Inputs
	//////////////////////////////////////////////////////////////////////////

	void ShaderInterface::processNormalKeyInputs(unsigned char key, int x, int y) {
		if (key == 29)
			exit(0);
	}

	void ShaderInterface::processSpecialKeyInputs(int key, int x, int y) {
		switch (key) {

		case GLUT_KEY_LEFT:
			m_cameraAngle -= 0.01f;
			m_cameraRotation.x = sin(m_cameraAngle);
			m_cameraRotation.z = -cos(m_cameraAngle);
			break;
		case GLUT_KEY_RIGHT:
			m_cameraAngle += 0.01f;
			m_cameraRotation.x = sin(m_cameraAngle);
			m_cameraRotation.z = -cos(m_cameraAngle);
			break;
		case GLUT_KEY_UP:
			m_cameraPosition.x += m_cameraRotation.x * m_cameraSpeed;
			m_cameraPosition.z += m_cameraRotation.z * m_cameraSpeed;
			break;
		case GLUT_KEY_DOWN:
			m_cameraPosition.x -= m_cameraRotation.x * m_cameraSpeed;
			m_cameraPosition.z -= m_cameraRotation.z * m_cameraSpeed;
			break;
		}
	}

	void ShaderInterface::processMouseInputs(int button, int state, int x, int y) {
		// only start motion if the left button is pressed
		if (button == GLUT_LEFT_BUTTON) {

			// when the button is released
			if (state == GLUT_UP) {
				m_cameraAngle += m_deltaAngle;
				m_xOrigin = -1;
			}
			else  {// state = GLUT_DOWN
				m_xOrigin = static_cast<float>(x);
			}
		}
	}

	void ShaderInterface::processMouseMovement(int x, int y) {
		// this will only be true when the left button is down
		if (m_xOrigin >= 0) {

			// update deltaAngle
			m_deltaAngle = (x - m_xOrigin) * 0.001f;

			// update camera's direction
			m_cameraRotation.x = sin(m_cameraAngle + m_deltaAngle);
			m_cameraRotation.z = -cos(m_cameraAngle + m_deltaAngle);
		}
	}
}
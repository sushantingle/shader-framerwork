#include "ShaderInterface.hpp"
#include <fstream>
#include "../framework/datatype/fsVector.hpp"
#include <string>

extern void processGlutMenuEvents(int option);
namespace sf {

	#define SHADER_ABSOLUTE_PATH "../source/app/resource/shader/"

	// Menu Defines
	#define MENU_ID_WIREFRAME_VIEW	1
	#define MENU_ID_SOLID_VIEW		2

	

	ShaderInterface::ShaderInterface() {

	}

	ShaderInterface::~ShaderInterface() {

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
		
		removeShader();// remove current active shader

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

	//////////////////////////////////////////////////////////////////////////
	// Shader Setup
	//////////////////////////////////////////////////////////////////////////

	const char* ShaderInterface::readShaderFile(const char* fileName) {
		
		int strLength = strlen(SHADER_ABSOLUTE_PATH) + strlen(fileName);
		char* filePath = (char*) malloc(strLength + 1);
		std::sprintf(filePath, "%s%s", SHADER_ABSOLUTE_PATH, fileName);
		filePath[strLength] = '\0';
		FILE* fp = fopen(filePath, "r");
		char* buf;
		long size;

		if (fp == NULL)
		{
			printf("File Not Found : %s", filePath);
			return NULL;
		}
		free(filePath);

		fseek(fp, 0L, SEEK_END);//go to end
		size = ftell(fp);       //get size
		fseek(fp, 0L, SEEK_SET);//go to beginning

		buf = (char*)malloc((size + 1) * sizeof(char));
		fread(buf, 1, size, fp);
		buf[size] = NULL;
		fclose(fp);
		return buf;
	}

	bool ShaderInterface::setShader(const char* vertexShader, const char* fragmentShader) {
		m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		const char* vs = readShaderFile(vertexShader);
		const char* fs = readShaderFile(fragmentShader);

		glShaderSource(m_vertexShaderId, 1, &vs, NULL);
		glShaderSource(m_fragmentShaderId, 1, &fs, NULL);

		glCompileShader(m_vertexShaderId);
		if (printShaderInfoLog(m_vertexShaderId))
			return false; // SHADER COMPILATION FAILED

		glCompileShader(m_fragmentShaderId);
		if (printShaderInfoLog(m_fragmentShaderId))
			return false; // SHADER COMPILATION FAILED

		m_programId = glCreateProgram();

		glAttachShader(m_programId, m_vertexShaderId);
		if (printProgramInfoLog(m_programId))
			return false; // SHADER ATTACHMENT TO PROGRAM FAILED

		glAttachShader(m_programId, m_fragmentShaderId);
		if (printProgramInfoLog(m_programId))
			return false; // SHADER ATTACHMENT TO PROGRAM FAILED

		glLinkProgram(m_programId);
		glUseProgram(m_programId);
		return true;
	}

	bool ShaderInterface::removeShader() {
		glDetachShader(m_programId, m_vertexShaderId);		// detach vertex shader
		glDetachShader(m_programId, m_fragmentShaderId);	// detach fragment shader

		glDeleteShader(m_vertexShaderId);
		glDeleteShader(m_fragmentShaderId);

		return true;
	}

	bool ShaderInterface::printShaderInfoLog(GLuint obj) {
		int infologLength = 0;
		int charsWritten = 0;
		char *infoLog;
		
		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
			printf("%s\n", infoLog);
			free(infoLog);	
		}
		// If success the infoLogLength is 1 which means empty.. no error
		return (infologLength > 1);
	}

	bool ShaderInterface::printProgramInfoLog(GLuint obj) {
		int infologLength = 0;
		int charsWritten = 0;
		char *infoLog;

		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
			printf("%s\n", infoLog);
			free(infoLog);
		}
		// If success the infoLogLength is 1 which means empty.. no error
		return (infologLength > 1);
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

		glTranslatef(0, -m_windowHeight, 0);

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
				m_xOrigin = x;
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
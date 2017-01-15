#include "ShaderInterface.hpp"
#include <fstream>
#include "../framework/datatype/fsVector.hpp"
namespace sf {

	ShaderInterface::ShaderInterface() {

	}

	ShaderInterface::~ShaderInterface() {

	}

	//////////////////////////////////////////////////////////////////////////
	// Basic Initialisation
	//////////////////////////////////////////////////////////////////////////

	void ShaderInterface::baseInit(int _width, int _height) {
		// Do common implementation here
		m_windowWidth	= _width;
		m_windowHeight	= _height;

		m_cameraPosition = Vector3<float>(0.0f, 0.0f, 5.0f);
		m_cameraRotation = Vector3<float>(0.0f, 0.0f, -1.0f);
		m_cameraSpeed	= 0.5f;
		m_cameraAngle	= 0.0f;
		m_deltaAngle	= 0.0f;
		m_xOrigin		= -1;

		// call init of derived class
		init(); // derived->init();
	}

	void ShaderInterface::baseUninit() {
		// Do common implementation here

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
	// Shader Setup
	//////////////////////////////////////////////////////////////////////////

	const char* ShaderInterface::readShaderFile(const char* fileName) {
		FILE* fp = fopen(fileName, "r");
		char* buf;
		long size;

		if (fp == NULL)
		{
			printf("File Not Found : %s", fileName);
			return NULL;
		}
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

		return true;
	}

	bool ShaderInterface::removeShader(GLuint obj) {
		
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
			return true; // COMPILATION FAILED
		}
		return false; // NO ERROR
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
			return true; // PROGRAM ATTACHMENT FAILED
		}
		return false; // NO ERROR
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
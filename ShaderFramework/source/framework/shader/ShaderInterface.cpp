#include "ShaderInterface.hpp"

namespace sf {

	ShaderInterface::ShaderInterface() {

	}

	ShaderInterface::~ShaderInterface() {

	}

	//////////////////////////////////////////////////////////////////////////
	// Basic Initialisation
	//////////////////////////////////////////////////////////////////////////

	void ShaderInterface::baseInit() {
		// Do common implementation here

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

		// call update of derived class
		render();  // derived->render();
	}

	//////////////////////////////////////////////////////////////////////////
	// Shader Setup
	//////////////////////////////////////////////////////////////////////////

	const char* ShaderInterface::readShaderFile(const char* fileName) {

	}

	bool ShaderInterface::setShader(const char* vertexShader, const char* fragmentShader) {

		return true;
	}

	void ShaderInterface::printShaderInfoLog(GLuint obj) {

	}

	void ShaderInterface::printProgramInfoLog(GLuint obj) {

	}

	//////////////////////////////////////////////////////////////////////////
	// Processing Inputs
	//////////////////////////////////////////////////////////////////////////

	void ShaderInterface::processNormalKeyInputs(unsigned char key, int x, int y) {

	}

	void ShaderInterface::processSpecialKeyInputs(int key, int x, int y) {
	
	}

	void ShaderInterface::processMouseInputs(int button, int State, int x, int y) {
	
	}

	void ShaderInterface::processMouseMovement(int x, int y) {
	
	}
}
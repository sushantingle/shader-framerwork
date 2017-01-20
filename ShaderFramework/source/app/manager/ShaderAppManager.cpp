#include "ShaderAppManager.hpp"
#include "../app/shader/ShaderDefault.hpp"
#include "../app/shader/ShaderDiffuse.hpp"
#include <assert.h>

ShaderAppManager::ShaderAppManager() {
	
}

ShaderAppManager::~ShaderAppManager() {
	if (m_shaderBase)
		delete m_shaderBase;
}

//////////////////////////////////////////////////////////////////////////
// Initialization
//////////////////////////////////////////////////////////////////////////

void ShaderAppManager::init(int _width, int _height) {
	// call shader base init
	m_windowWidth = _width;
	m_windowHeight = _height;
	m_shaderType = ShaderType::SHADER_DEFAULT;
	createShader(m_shaderType);
}

//////////////////////////////////////////////////////////////////////////
// Update
//////////////////////////////////////////////////////////////////////////

void ShaderAppManager::update() {
	// call shader base update
	m_shaderBase->baseUpdate();

	// call shader base render
	m_shaderBase->baseRender();
}

//////////////////////////////////////////////////////////////////////////
// Shader initialization
//////////////////////////////////////////////////////////////////////////

void ShaderAppManager::createShader(ShaderType _shaderType) {
	createObjectOfShaderType(_shaderType);						// create shader object
	assert(m_shaderBase);
	
	m_shaderBase->baseInit(m_windowWidth, m_windowHeight);		// initialize shader base class with window width and height
}

void ShaderAppManager::createObjectOfShaderType(ShaderType _shaderType) {
	switch (_shaderType) {
	case ShaderType::SHADER_DEFAULT:
		// Allocate shader object of type SHADER_DEFAULT
		m_shaderBase = new ShaderDefault();
		break;
	case ShaderType::SHADER_DIFFUSE:
		m_shaderBase = new ShaderDiffuse();
		break;
	}
}

void ShaderAppManager::deleteShader() {
	m_shaderBase->baseUninit();									// Uninit base shader.
	
	delete m_shaderBase;										// deletes shader base object
}

void ShaderAppManager::activateNextShader(bool _next) {
	ShaderType lastShader = m_shaderType;

	int indexDx = _next ? 1 : -1;								// determine which shader to select (next / previous)

	m_shaderType = m_shaderType + indexDx;

	if (m_shaderType < ShaderType::SHADER_DEFAULT)				// check if less than first shader then set shader type to first shader
		m_shaderType = ShaderType::SHADER_DEFAULT;

	if (m_shaderType >= ShaderType::SHADER_COUNT)				// check if greater than max shader count then set shader type to last shader.
		m_shaderType = (ShaderType::SHADER_COUNT - 1);

	if (lastShader != m_shaderType) {							// if last shader and newly selected shader are different 
		deleteShader();											// then delete previous shader
		createShader(m_shaderType);								// and create new shader of selected type.
	}
}

void ShaderAppManager::reloadShader() {
	deleteShader();
	createShader(m_shaderType);
}
//////////////////////////////////////////////////////////////////////////
// Process Inputs
//////////////////////////////////////////////////////////////////////////

void ShaderAppManager::onNormalKeyboardKeyPressed(unsigned char key, int x, int y) {
	
	
		switch (key)
		{
		case 'd':
			// activate next shader
			activateNextShader(true);							// 'd' button to select next shader
			break;
		case 'a':
			// activate previous shader
			activateNextShader(false);							// 'a' button to select previous shader
			break;
		}
	
	m_shaderBase->processNormalKeyInputs(key, x, y);			// delegate call to shader base class
}

void ShaderAppManager::onSpecialKeyboardKeyPressed(int key, int x, int y) {
	m_shaderBase->processSpecialKeyInputs(key, x, y);			// delegate call to shader base class
}

// changes shader on mouse clicks
void ShaderAppManager::onMouseButtonDown(int button, int state, int x, int y) {

	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_UP) {
			reloadShader();
		}
	}
	m_shaderBase->processMouseInputs(button, state, x, y);      // delegate call to shader base class
}

void ShaderAppManager::onMouseMoved(int x, int y) {
	m_shaderBase->processMouseMovement(x, y);					// delegate call to shader base class to handle camera movement
}
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
	createObjectOfShaderType(_shaderType);
	assert(m_shaderBase);
	
	m_shaderBase->baseInit(m_windowWidth, m_windowHeight);
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
	m_shaderBase->baseUninit();

	delete m_shaderBase;
}

void ShaderAppManager::activateNextShader(bool _next) {
	ShaderType lastShader = m_shaderType;

	int indexDx = _next ? 1 : -1;

	m_shaderType = m_shaderType + indexDx;

	if (m_shaderType < ShaderType::SHADER_DEFAULT)
		m_shaderType = ShaderType::SHADER_DEFAULT;

	if (m_shaderType >= ShaderType::SHADER_COUNT)
		m_shaderType = (ShaderType::SHADER_COUNT - 1);

	if (lastShader != m_shaderType) {
		deleteShader();
		createShader(m_shaderType);
	}
}
//////////////////////////////////////////////////////////////////////////
// Process Inputs
//////////////////////////////////////////////////////////////////////////

void ShaderAppManager::onNormalKeyboardKeyPressed(unsigned char key, int x, int y) {
	m_shaderBase->processNormalKeyInputs(key, x, y);
}

void ShaderAppManager::onSpecialKeyboardKeyPressed(int key, int x, int y) {
	m_shaderBase->processSpecialKeyInputs(key, x, y);
}

void ShaderAppManager::onMouseButtonDown(int button, int state, int x, int y) {

	if (state == GLUT_UP)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			// activate next shader
			activateNextShader(true);
			break;
		case GLUT_RIGHT_BUTTON:
			// activate previous shader
			activateNextShader(false);
			break;
		}
	}
	m_shaderBase->processMouseInputs(button, state, x, y);
}

void ShaderAppManager::onMouseMoved(int x, int y) {
	m_shaderBase->processMouseMovement(x, y);
}
#include "ShaderAppManager.hpp"
#include "../app/shader/ShaderDefault.hpp"
#include <assert.h>

ShaderAppManager::ShaderAppManager() {

}

ShaderAppManager::~ShaderAppManager() {

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
	}
}

void ShaderAppManager::deleteShader() {
	m_shaderBase->baseUninit();

	delete m_shaderBase;
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

}

void ShaderAppManager::onMouseMoved(int x, int y) {

}
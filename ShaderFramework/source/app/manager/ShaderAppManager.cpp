#include "ShaderAppManager.hpp"
#include "../app/shader/ShaderDefault.hpp"
#include "../app/shader/ShaderDiffuse.hpp"
#include "../app/shader/GeometryShader.hpp"
#include "../app/shader/Texture/TextureTest.hpp"
#include "../app/shader/Light/LightTest.hpp"
#include "../app/shader/Light/LightMapTest.hpp"
#include "../app/shader/Light/LightCasterTest.hpp"
#include "../app/shader/Model/ModelTest.hpp"
#include "../app/shader/Buffer/FramebufferTest.hpp"
#include <assert.h>

ShaderAppManager::ShaderAppManager() {
	createShaderLibrary();
}

ShaderAppManager::~ShaderAppManager() {
	for (auto it = m_shaderLibrary.begin(); it != m_shaderLibrary.end(); it++) {
        if (it->second != nullptr) {
            delete it->second;
            it->second = nullptr;
        }
	}
	m_shaderLibrary.clear();
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
    assert(m_shaderLibrary.count(_shaderType) > 0);
    m_shaderBase = m_shaderLibrary[_shaderType];
	assert(m_shaderBase);
	m_shaderBase->baseInit(m_windowWidth, m_windowHeight);		// initialize shader base class with window width and height
}

void ShaderAppManager::createShaderLibrary()
{
	m_shaderLibrary.insert(std::pair<ShaderType, sf::ShaderInterface*>(ShaderType::SHADER_DEFAULT, new ShaderDefault()));
	m_shaderLibrary.insert(std::pair<ShaderType, sf::ShaderInterface*>(ShaderType::SHADER_DIFFUSE, new ShaderDiffuse()));
	m_shaderLibrary.insert(std::pair<ShaderType, sf::ShaderInterface*>(ShaderType::SHADER_GEOMTRY_BASIC, new GeometryShader()));
	m_shaderLibrary.insert(std::pair<ShaderType, sf::ShaderInterface*>(ShaderType::SHADER_TEXTURE_TEST, new TextureTest()));
	m_shaderLibrary.insert(std::pair<ShaderType, sf::ShaderInterface*>(ShaderType::SHADER_LIGHT_TEST, new LightTest()));
	m_shaderLibrary.insert(std::pair<ShaderType, sf::ShaderInterface*>(ShaderType::SHADER_LIGHTMAP_TEST, new LightMapTest()));
	m_shaderLibrary.insert(std::pair<ShaderType, sf::ShaderInterface*>(ShaderType::SHADER_CASTER_TEST, new LightCasterTest()));
	m_shaderLibrary.insert(std::pair<ShaderType, sf::ShaderInterface*>(ShaderType::SHADER_MODEL_TEST, new ModelTest()));
	m_shaderLibrary.insert(std::pair<ShaderType, sf::ShaderInterface*>(ShaderType::SHADER_FRAMEBUFFER_TEST, new FramebufferTest()));
}

void ShaderAppManager::deleteShader() {
	m_shaderBase->baseUninit();									// Uninit base shader.
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

void ShaderAppManager::onMenuItemClicked(int menuId) {
	m_shaderBase->processMenuEvents(menuId);
}
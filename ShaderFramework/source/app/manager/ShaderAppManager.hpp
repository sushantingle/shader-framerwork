#ifndef __SHADERAPPMANAGER_HPP__
#define __SHADERAPPMANAGER_HPP__

#include "../framework/shader/ShaderInterface.hpp"

class ShaderAppManager {
private:

	// Enumeration
	enum class ShaderType {
	SHADER_DEFAULT,
	};

	// Member Function

	/************************************************************************/
	/* 
		Initializes shader base object with object of _shaderType
	*/
	/************************************************************************/
	void createShader(ShaderType _shaderType);

	/************************************************************************/
	/* 
		Deletes the shader base object
	*/
	/************************************************************************/
	void deleteShader();

	/************************************************************************/
	/* 
		Allocates passed shader type object.
	*/
	/************************************************************************/
	void createObjectOfShaderType(ShaderType _shaderType);

	// Memeber Variables
	sf::ShaderInterface* m_shaderBase;
	ShaderType			 m_shaderType;
	int					 m_windowWidth;
	int					 m_windowHeight;
public:
	ShaderAppManager();
	~ShaderAppManager();

	/************************************************************************/
	/* 
		Initializes manager in main function
	*/
	/************************************************************************/
	void init(int _width, int _height);

	/************************************************************************/
	/* 
		Updates app manager in render thread
	*/
	/************************************************************************/
	void update();

	/************************************************************************/
	/* 
		Process Keyboard inputs and mouse inputs
	*/
	/************************************************************************/
	void onNormalKeyboardKeyPressed(unsigned char key, int x, int y);
	void onSpecialKeyboardKeyPressed(int key, int x, int y);
	void onMouseButtonDown(int button, int state, int x, int y);
	void onMouseMoved(int x, int y);

};

#endif //__SHADERAPPMANAGER_HPP__
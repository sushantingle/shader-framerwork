#ifndef __SHADERAPPMANAGER_HPP__
#define __SHADERAPPMANAGER_HPP__

#include "../framework/shader/ShaderInterface.hpp"


/*!
	\class ShaderAppManager
	\brief This is a ShaderAppManager.

	It deals with managing shader...

*/
class ShaderAppManager {

public:


private:

	// Enumeration
	/*!
		\enum ShaderType
		This is an enum
	*/
		enum class ShaderType {
			SHADER_DEFAULT,		//!< This is the default.
			SHADER_DIFFUSE,
			SHADER_COUNT,
		};

		friend ShaderType& operator+(ShaderType _a, int value);
		friend ShaderType& operator-(ShaderType _a, int value);

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

	/************************************************************************/
	/* 
		activate next/previous shader
	*/
	/************************************************************************/
	void activateNextShader(bool _nextShader);

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

inline ShaderAppManager::ShaderType& operator+ (ShaderAppManager::ShaderType _shaderType, int value)
{
	const int i = static_cast<int> (_shaderType) + value;
	_shaderType = static_cast<ShaderAppManager::ShaderType> ((i) % static_cast<int> (ShaderAppManager::ShaderType::SHADER_COUNT));
	return _shaderType;
}

inline ShaderAppManager::ShaderType& operator- (ShaderAppManager::ShaderType _shaderType, int value)
{
	const int i = static_cast<int> (_shaderType) - value;
	_shaderType = static_cast<ShaderAppManager::ShaderType> ((i) % static_cast<int> (ShaderAppManager::ShaderType::SHADER_COUNT));
	return _shaderType;
}


#endif //__SHADERAPPMANAGER_HPP__
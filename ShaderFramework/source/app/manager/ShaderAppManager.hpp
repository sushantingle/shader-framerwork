/*!
 
*/

#ifndef __SHADERAPPMANAGER_HPP__
#define __SHADERAPPMANAGER_HPP__

#include "../framework/shader/ShaderInterface.hpp"


/*!
	\class ShaderAppManager
	\brief This class passes appropriate calls to shader interface to update and render properly.
	
	Basic user interaction is implemented in this class.
*/
class ShaderAppManager {

public:

	ShaderAppManager();
	~ShaderAppManager();

	/*!
		\brief Initializes manager
		\param _width is window width
		\param _height is window height
	*/
	void init(int _width, int _height);

	/************************************************************************/
	/*
		\brief Updates app manager in render thread
	*/
	/************************************************************************/
	void update();

	/*!
		\brief Process normal Keyboard inputs

		Keypad buttons are considered as normal buttons. e.g. 'W','A','S','D'

		\param key is keycode
		\param x,y are mouse co-ordinates
	*/
	void onNormalKeyboardKeyPressed(unsigned char key, int x, int y);

	/*! 
		\brief processes special keyboard inputs

		special keyboard inputs for ex. shift, ctrl, arrow keys

		\param key is keycode
		\param x,y are mouse co-ordinates
	*/
	void onSpecialKeyboardKeyPressed(int key, int x, int y);

	/*!
		\brief processes mouse inputs

		\param button is mouse butto key code 
		ex: GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON
		\param state is mouse button state e.g. GLUT_UP, GLUT_DOWN
		\param x,y are mouse co-ordinates
	*/
	void onMouseButtonDown(int button, int state, int x, int y);

	/*! 
		\brief handles mouse movement event, We have implemented camera movement 
		feature in this function

		\param x,y are mouse co-ordinates.
	*/
	void onMouseMoved(int x, int y);

private:

	// Enumeration
	/*!
		\enum This enum defines different shader types in app
	*/
		enum class ShaderType {
			SHADER_DEFAULT,		//!< This is the default shader.
			SHADER_DIFFUSE,		//!< This defines diffuse shader
			SHADER_COUNT,		//!< This defines number shaders app has.
		};

		/*!
			\brief implemented + operator to do addition operation on enum.
			\param _a is like this pointer of enum
		*/
		friend ShaderType& operator+(ShaderType _a, int value);

		/*!
			\brief implemented - operator to do substraction operation on enum
			\param _a is like this pointer of enum
		*/
		friend ShaderType& operator-(ShaderType _a, int value);


	// Member Function
	/*!
		\brief Initializes shader base object with object of _shaderType and initializes shader
		\param _shaderType is Shader type of object
	*/
	void createShader(ShaderType _shaderType);

	/*!
		\brief Deletes the shader base object and invokes uninit of shader base class
	*/
	void deleteShader();

	/*! 
		\brief Allocates shader interface object of shader type.
		\param _shaderType is shader type.
	*/
	void createObjectOfShaderType(ShaderType _shaderType);

	/*! 
		\brief this function invokes in mouse button up callback. 

		This function basically deletes current shader and activates next or previous shader based on the parameter value.

		\param _nextShader is boolean decides which shader to select ( next or previous). 
				If TRUE then selects next one if current selected is not last.
				if FALSE then selects previous one if current selected is not first.
	*/
	void activateNextShader(bool _nextShader);

	// Memeber Variables
	sf::ShaderInterface* m_shaderBase;  //! \var This is base class object of shader types. This variable allocates on the basis of current shader type
	ShaderType			 m_shaderType;  //! \var This variable maintains active shader type.
	int					 m_windowWidth; //! \var This denotes window width
	int					 m_windowHeight;//! \var This denotes window height


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
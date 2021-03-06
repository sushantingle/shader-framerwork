#ifndef __SHADERINTERFACE_HPP__
#define __SHADERINTERFACE_HPP__

#include "GLEW/glew.h"
#include "GL/glut.h"
#include "../datatype/fsVector.hpp"
#include <vector>
#include "stbi\stb_image.h"
#include "glm\glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <map>
#include "Shader.hpp"

namespace sf {
	/*!
		\class ShaderInterface
		\brief This class is base class for all shader types.

		We have used non-virtual interface to implement this base class.
		This class has base function which calls pure virtual function implemented by child class

		This class has implemented common things in shader such as reading shader, shader compilation, displaying error info, linking.
	*/
	class ShaderInterface {

	public:

		ShaderInterface();
		~ShaderInterface();

		/*!
			\brief Init Function available from other classes

			Function basically does the common initialization and calls child class's init function.

			\param _width is window width.
			\param _height is window height
			*/
		void baseInit(int _width, int _height);

		/*!
			\brief Uninit function available to call from other classes.

			Function uninit the base class and calls child class's uninit function
			*/
		void baseUninit();

		/*!
			\brief function is available to call from other classes.

			Function updates the common parameters and calls child class's update function.
			*/
		void baseUpdate();

		/*!
			\brief function is available to call from other classes.

			Function does the initial setup to render the scene.
			*/
		void baseRender();

		/*!

			\brief Processes normal Keyboard Inputs

			Process Normal Keyboard keys.
			Normal Key	: 'W', 'A','S','D', etc.

			\param key: pressed key ASCII code
			\param x, y	: Mouse pointer position
			*/
		/************************************************************************/
		virtual void processNormalKeyInputs(unsigned char key, int x, int y);

		/*!
			\brief processes special keyboard inputs

			Special Key : Control, Shift Key, Arrow Keys, F1, F2, etc.

			\param key: pressed key ASCII code
			\param x, y	: Mouse pointer position
			*/
		virtual void processSpecialKeyInputs(int key, int x, int y);

		/*!
			\brief Processes Mouse inputs
			Process button down, up and scroll operation

			\param button: pressed mouse button code => GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON
			\param state: Button state => GLUT_DOWN, GLUT_UP
			\param x, y	: Mouse pointer position
			*/
		virtual void processMouseInputs(int button, int State, int x, int y);

		/*!
			\brief Processes Mouse Movements if mouse is in scene
			\param x,y : mouse pixel position in scene
			*/
		virtual void processMouseMovement(int x, int y);

		/*!

			\brief creates default Menu

		*/
		void createDefaultMenu();

		/*!
			\brief process menu clicks
		*/
		void processMenuEvents(int menuId);

		/*!
			\brief destroys All Menu created in shader
		*/
		void destroyMenu();

	protected:
		
		void addShader(int id, const char* vert, const char* frag, const char* geom);
		/*!
			\brief Adds Menu entry
			\param menuName is Menu Name
			\param menuId is Menu Unique Id
		*/
		void addMenuEntry(const char* menuName, int menuId);

		// Window Parameters
		int		m_windowWidth;	//! \var holds window width
		int		m_windowHeight;	//! \var holds window height

		// Camera Parameters
		sf::Vector3<float> m_cameraPosition;	//! \var holds camera position in scene
		sf::Vector3<float> m_cameraRotation;	//! \var holds camera rotation in scene
		float m_cameraAngle;					//! \var holds camera angle in scene
		float m_cameraSpeed;					//! \var holds camera speed in scene
		float m_deltaAngle;						//! \var holds camera rotation speed
		float m_xOrigin;

		std::map<int, Shader*> m_shaders;
	private:
		
		/*!
			/brief init function which child needs to implement

			This function does the shader specific initialization.
		*/
		virtual void init() = 0;		
		
		/*!
			/brief uninit function which child needs to implement

			This function remove shader specific parameters and uninits active shader
		*/
		virtual void uninit() = 0;

		/*!
			/brief update function which child needs to implement

			This function does shader specific update functionality
		*/
		virtual void update() = 0;

		/*!
			/brief render function which child needs to implement

			This function does the shader specific render functionality
		*/
		virtual void render() = 0;

		/*!
			\brief Create special menu

			App can have Default Options and custom options only. If custom option are getting bit complicated,
			then hirarchy should be created inside custom options only.

			\warning we can not have more than one custom menu under main menu. We have to add sections in custom menu to 
			achieve it.

			\return -1 if not created special menu
		*/
		virtual int createSpecialMenu() { return -1; }

		/*!
			\brief Process special menu events
		*/
		virtual void processSpecialMenuEvents(int option) {}

		/*!
			\brief To render text or 2d objects using pixel co-ordinate, this function
				sets projection to orthographic.
				Set orthographic projection and then render required graphics and then
				restore back to perspective projection.
		*/
		void setOrthographicProjection();

		/*!
				\brief This function restores projection to perspective if user has switched to
						orthographic before.
		*/
		void restorePerspectiveProjection();

		// Shader Parameters
		GLuint	m_programId;		//! \var holds active shader's program id
		GLuint	m_vertexShaderId;	//! \var holds active vertex shader id.
		GLuint	m_fragmentShaderId; //! \var holds active fragment shader id.
		GLuint	m_geometryShaderId; //! \var holds active geometry shader id.
		std::vector<int> m_menuIds;
	};
}
#endif //__SHADERINTERFACE_HPP__
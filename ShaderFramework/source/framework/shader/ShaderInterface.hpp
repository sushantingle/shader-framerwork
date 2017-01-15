#ifndef __SHADERINTERFACE_HPP__
#define __SHADERINTERFACE_HPP__

#include "GLEW/glew.h"
#include "GL/glut.h"
#include "../datatype/fsVector.hpp"

namespace sf {
	class ShaderInterface {
	private:
		/************************************************************************/
		/* 
			actual override functions
		*/
		/************************************************************************/
		virtual void init()		= 0;
		virtual void uninit()	= 0;

		virtual void update()	= 0;
		virtual void render()	= 0;

		/************************************************************************/
		/* 
			This function reads the shader file and returns char buffer.
			@param: 
				fileName : shader file name or absolute path
		*/
		/************************************************************************/
		const char* readShaderFile(const char* fileName);
		
		/************************************************************************/
		/*
			This function invokes the function to read shader, compiles it and then attach to the program.
			IF shader compilation fails, this function invokes function to print error info.
			@param: 
				vertex and fragment shader names.
		*/
		/************************************************************************/
		bool setShader(const char* vertexShader, const char* fragmentShader);

		/************************************************************************/
		/* 
			This function removes active shader.
			@param:
				obj : shader id.
		*/
		/************************************************************************/
		bool removeShader(GLuint obj);

		/************************************************************************/
		/* 
			This function prints error log if shader compilation fails and returns true.			
			@param:
				obj : shader id
		*/
		/************************************************************************/
		bool printShaderInfoLog(GLuint obj);

		/************************************************************************/
		/* 
			This function prints error log if program attachment fails and returns true.
			@param:
				obj : program id
		*/
		/************************************************************************/
		bool printProgramInfoLog(GLuint obj);

		/************************************************************************/
		/* 
			To render text or 2d objects using pixel co-ordinate, this function
			sets projection to orthographic. 
			Set orthographic projection and then render required graphics and then
			restore back to perspective projection.
		*/
		/************************************************************************/
		void setOrthographicProjection();

		/************************************************************************/
		/* 
			This function restores projection to perspective if user has switched to 
			orthographic before.
		*/
		/************************************************************************/
		void restorePerspectiveProjection();

		// Window Parameters
		int		m_windowWidth;
		int		m_windowHeight;

		// Shader Parameters
		GLuint	m_programId;
		GLuint	m_vertexShaderId;
		GLuint	m_fragmentShaderId;

	protected:

		// Camera Parameters
		sf::Vector3<float> m_cameraPosition;
		sf::Vector3<float> m_cameraRotation;
		float m_cameraAngle;
		float m_cameraSpeed;
		float m_deltaAngle;
		float m_xOrigin;

	public:

		ShaderInterface();
		~ShaderInterface();

		/************************************************************************/
		/*  
			Global Init Functions
			Functions basically does the common implementation and calls derived class's appropriate function.
		*/
		/************************************************************************/
		void baseInit(int _width, int _height);
		void baseUninit();
		void baseUpdate();
		void baseRender();

		/************************************************************************/
		/* 
			Processes Keyboard Inputs
			Process Normal Keyboard keys and special keyboard keys.
			Normal Key	: 'W', 'A','S','D', etc.
			Special Key : Control, Shift Key, Arrow Keys, F1, F2, etc. 
			@param: 
				key		: pressed key ASCII code
				x, y	: Mouse pointer position
		*/
		/************************************************************************/
		virtual void processNormalKeyInputs(unsigned char key, int x, int y);
		virtual void processSpecialKeyInputs(int key, int x, int y);

		/************************************************************************/
		/* 
			Processes Mouse inputs
			Process button down, up and scroll operation
			@param:
				button	: pressed mouse button code => GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON
				state	: Button state => GLUT_DOWN, GLUT_UP
		*/
		/************************************************************************/
		virtual void processMouseInputs(int button, int State, int x, int y);

		/************************************************************************/
		/*
			Processes Mouse Movements if mouse is in scene
			@param:
				x,y : mouse pixel position in scene
		*/
		/************************************************************************/
		virtual void processMouseMovement(int x, int y);
		
	};
}
#endif //__SHADERINTERFACE_HPP__
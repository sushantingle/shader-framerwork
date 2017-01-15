#ifndef __SHADERINTERFACE_HPP__
#define __SHADERINTERFACE_HPP__

#include "GL/glut.h"
#include "GLEW/glew.h"

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
			This function prints error log if shader compilation fails.			
			@param:
				obj : shader id
		*/
		/************************************************************************/
		void printShaderInfoLog(GLuint obj);

		/************************************************************************/
		/* 
			This function prints error log if program attachment fails.
			@param:
				obj : program id
		*/
		/************************************************************************/
		void printProgramInfoLog(GLuint obj);

	public:

		ShaderInterface();
		~ShaderInterface();

		/************************************************************************/
		/*  
			Global Init Functions
			Functions basically does the common implementation and calls derived class's appropriate function.
		*/
		/************************************************************************/
		void baseInit();
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
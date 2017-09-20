#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include "GLEW/glew.h"
#include "GL/glut.h"

class Shader {

public:
	Shader() {}
	/*!
	\brief This function invokes the function to read shader, compiles it and then attach to the program.
	IF shader compilation fails, this function invokes function to print error info.
	empty default Geomtry shader name makes geometry shader optional.

	\param	vertex, geometry and fragment shader names
	*/
	Shader(const char* vert, const char* frag, const char* geom);
	
	/*!
	\brief This function removes active shader.
	*/
	~Shader();

	/*!
	\brief returns program id

	\return GLuint programId
	*/
	GLuint getProgramId() { return m_programId; }

	void useProgram();
private:
	/*!
	\brief This function reads the shader file and returns char buffer.
	\param fileName : shader file name or absolute path
	*/
	const char* readShaderFile(const char* fileName);

	/*!
	\brief creates vertex shader
	\param vertex shader name
	*/
	void createVertexShader(const char* filename);

	/*!
	\brief creates fragment shader
	\param fragment shader name
	*/
	void createFragmentShader(const char* filename);

	/*!
	\brief creates geometry shader
	\param geometry shader name
	*/
	void createGeometryShader(const char* filename);

	/*!
	\brief This function prints error log if shader compilation fails and returns true.
	\param obj : shader id
	*/
	bool printShaderInfoLog(GLuint obj);

	/*!
	\brief This function prints error log if program attachment fails and returns true.
	\param obj : program id
	*/
	bool printProgramInfoLog(GLuint obj);

	GLuint m_programId;
	GLuint m_vertId;
	GLuint m_fragId;
	GLuint m_geomId;
};

#endif //__SHADER_HPP__

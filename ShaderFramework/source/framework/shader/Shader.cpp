#include "Shader.hpp"
#include <fstream>
#include "../framework/datatype/fsVector.hpp"
#include <string>

#define SHADER_ABSOLUTE_PATH "../source/app/resource/shader/"

Shader::Shader(const char * vert, const char * frag, const char * geom)
{
	m_programId = glCreateProgram();
	//printf("shader : %s", vertexShader);
	createVertexShader(vert);
	//printf("shader : %s", fragmentShader);
	createFragmentShader(frag);
	//printf("shader : %s", geometryShader);
	createGeometryShader(geom);

	glLinkProgram(m_programId);
}

void Shader::useProgram()
{
	glUseProgram(m_programId);
}

Shader::~Shader()
{
	glDetachShader(m_programId, m_vertId);		// detach vertex shader
	glDetachShader(m_programId, m_fragId);	// detach fragment shader

	glDeleteShader(m_vertId);
	glDeleteShader(m_fragId);
	glUseProgram(0);
}

const char* Shader::readShaderFile(const char* fileName) {

	int strLength = strlen(SHADER_ABSOLUTE_PATH) + strlen(fileName);
	char* filePath = (char*)malloc(strLength + 1);
	std::sprintf(filePath, "%s%s", SHADER_ABSOLUTE_PATH, fileName);
	filePath[strLength] = '\0';
	FILE* fp = fopen(filePath, "r");
	char* buf;
	long size;

	if (fp == NULL)
	{
		printf("File Not Found : %s", filePath);
		return NULL;
	}
	free(filePath);

	fseek(fp, 0L, SEEK_END);//go to end
	size = ftell(fp);       //get size
	fseek(fp, 0L, SEEK_SET);//go to beginning

	buf = (char*)malloc((size + 1) * sizeof(char));
	fread(buf, 1, size, fp);
	buf[size] = '\0';
	fclose(fp);
	return buf;
}

void Shader::createVertexShader(const char * filename)
{
	if (std::strcmp(filename, "") == 0) // Does not have vertex shader
		return;

	// Create vertex shader
	m_vertId = glCreateShader(GL_VERTEX_SHADER);

	// read vertex shader
	const char* vs = readShaderFile(filename);

	// add vertex shader source for compilation
	glShaderSource(m_vertId, 1, &vs, NULL);

	// compile vertex shader
	glCompileShader(m_vertId);
	printShaderInfoLog(m_vertId);

	glAttachShader(m_programId, m_vertId);
	printProgramInfoLog(m_programId);
}

void Shader::createFragmentShader(const char * filename)
{
	if (std::strcmp(filename, "") == 0) // Does not have fragment shader
		return;

	m_fragId = glCreateShader(GL_FRAGMENT_SHADER);

	const char* fs = readShaderFile(filename);

	glShaderSource(m_fragId, 1, &fs, NULL);

	glCompileShader(m_fragId);
	printShaderInfoLog(m_fragId);

	glAttachShader(m_programId, m_fragId);
	printProgramInfoLog(m_programId);
}

void Shader::createGeometryShader(const char * filename)
{
	if (std::strcmp(filename, "") == 0) // Does not have geometry shader
		return;

	m_geomId = glCreateShader(GL_GEOMETRY_SHADER);

	const char* fs = readShaderFile(filename);

	glShaderSource(m_geomId, 1, &fs, NULL);

	glCompileShader(m_geomId);
	printShaderInfoLog(m_geomId);

	glAttachShader(m_programId, m_geomId);
	printProgramInfoLog(m_programId);
}

bool Shader::printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("Shader info: %s\n", infoLog);
		free(infoLog);
	}
	// If success the infoLogLength is 1 which means empty.. no error
	return (infologLength > 1);
}

bool Shader::printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("program info: %s\n", infoLog);
		free(infoLog);
	}
	// If success the infoLogLength is 1 which means empty.. no error
	return (infologLength > 1);
}

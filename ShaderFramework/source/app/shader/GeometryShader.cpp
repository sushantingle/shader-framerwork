#include "GeometryShader.hpp"

void GeometryShader::init() {
	
	setShader(m_defaultShaderData, "geometry_shader/basic.vert", "geometry_shader/basic.frag", "geometry_shader/basic.geom");

	glGenBuffers(1, &m_vbo);

	float points[] = {
		-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 4.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 10.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 15.0f, 
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 32.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// create VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// specify layout of point data
	GLint posAttrib = glGetAttribLocation(m_defaultShaderData.programId, "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	
	// specify color of point data
	GLint colorAttrib = glGetAttribLocation(m_defaultShaderData.programId, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (2 * sizeof(float)));

	// specify sides of object
	GLint sidesAttrib = glGetAttribLocation(m_defaultShaderData.programId, "sides");
	glEnableVertexAttribArray(sidesAttrib);
	glVertexAttribPointer(sidesAttrib, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));

}

void GeometryShader::uninit() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);

	m_vao = 0;
	m_vbo = 0;
}

void GeometryShader::update() {

}

void GeometryShader::render() {
	glDrawArrays(GL_POINTS, 0, 4);
}

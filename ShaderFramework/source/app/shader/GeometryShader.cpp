#include "GeometryShader.hpp"

void GeometryShader::init() {

	addShader(0, "geometry_shader/basic.vert", "geometry_shader/basic.frag","geometry_shader/basic.geom");

	glGenBuffers(1, &m_vbo);

	float points[] = {
		-0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// create VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// specify layout of point data
	GLint posAttrib = glGetAttribLocation(m_shaders[0]->getProgramId(), "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	GLint colorAttrib = glGetAttribLocation(m_shaders[0]->getProgramId(), "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (2 * sizeof(float)));
}

void GeometryShader::uninit() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void GeometryShader::update() {

}

void GeometryShader::render() {
	m_shaders[0]->useProgram();
	glDrawArrays(GL_POINTS, 0, 4);
}

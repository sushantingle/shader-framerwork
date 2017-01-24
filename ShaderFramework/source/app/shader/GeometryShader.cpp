#include "GeometryShader.hpp"

void GeometryShader::init() {

	setShader("geometry_shader/basic.vert", "geometry_shader/basic.frag","geometry_shader/basic.geom");

	GLuint vbo;
	glGenBuffers(1, &vbo);

	float points[] = {
		-0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// create VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// specify layout of point data
	GLint posAttrib = glGetAttribLocation(getProgramId(), "pos");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	GLint colorAttrib = glGetAttribLocation(getProgramId(), "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (2 * sizeof(float)));
}

void GeometryShader::uninit() {

}

void GeometryShader::update() {

}

void GeometryShader::render() {
	glDrawArrays(GL_POINTS, 0, 4);
}

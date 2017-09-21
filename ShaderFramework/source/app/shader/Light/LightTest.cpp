#include "LightTest.hpp"
#include <string>

void LightTest::init()
{
	glEnable(GL_DEPTH_TEST);
	m_rotationAngle = 0.0f;

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	// Cube
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(cubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Light
	glGenVertexArrays(1, &lightVao);
	glBindVertexArray(lightVao);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	addShader(0, "light/lightest.vert", "light/lightest.frag", "");
	
}

void LightTest::uninit()
{
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVao);
	glDeleteBuffers(1, &VBO);
	glDisable(GL_DEPTH_TEST);
}

void LightTest::update()
{
	m_rotationAngle += 1.0f;
}

void LightTest::render()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	// render cube
	m_shaders[0]->useProgram();

	m_shaders[0]->setVec3("lightPos", glm::vec3(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z));
	m_shaders[0]->setVec3("lightColor", glm::vec3(0.0f, 0.3f, 1.0f));
	m_shaders[0]->setVec3("objectColor", glm::vec3(1.0f, 0.8f, 0.8f));
	m_shaders[0]->setVec3("viewPos", glm::vec3(m_cameraPosition.x + m_cameraRotation.x, m_cameraPosition.y + m_cameraRotation.y, m_cameraPosition.z + m_cameraRotation.z));
	m_shaders[0]->setFloat("ambientStrength", 0.5f);
	m_shaders[0]->setInt("shininess", 32);

	glm::mat4 view;
	glm::vec3 target = glm::vec3(m_cameraPosition.x + m_cameraRotation.x, m_cameraPosition.y + m_cameraRotation.y, m_cameraPosition.z + m_cameraRotation.z);
	view = glm::lookAt(glm::vec3(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z), target, glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int viewLoc = glGetUniformLocation(m_shaders[0]->getProgramId(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(1.0f, 0.0f, -5.0f));
	model = glm::rotate(glm::radians(m_rotationAngle), glm::vec3(0.3f, 0.5f, 0.8f));
	unsigned int modelLoc = glGetUniformLocation(m_shaders[0]->getProgramId(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.0f);
	unsigned int projectionLoc = glGetUniformLocation(m_shaders[0]->getProgramId(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// render lamp
/*	m_shaders[1]->useProgram();

	viewLoc = glGetUniformLocation(m_shaders[1]->getProgramId(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(1.0f, 0.0f, -8.0f));
	model = glm::rotate(glm::radians(30.0f), glm::vec3(0.5f, 0.1f, 0.5f));
	modelLoc = glGetUniformLocation(m_shaders[1]->getProgramId(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	projectionLoc = glGetUniformLocation(m_shaders[1]->getProgramId(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindTexture(GL_TEXTURE0, 0);

	glBindVertexArray(lightVao);
	glDrawArrays(GL_TRIANGLES, 0, 36);*/
}

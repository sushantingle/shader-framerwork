#include "ModelTest.hpp"

void ModelTest::init()
{
	glEnable(GL_DEPTH_TEST);
	addShader(0, "model/modeltest.vert", "model/modeltest.frag", "");
	m_model = new Model("../source/app/resource/model/nanosuit/nanosuit.obj");
}

void ModelTest::uninit()
{
	delete m_model;
	glDisable(GL_DEPTH_TEST);
}

void ModelTest::update()
{
	m_rotationAngle += 0.1f;
}

void ModelTest::render()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_shaders[0]->useProgram();

	glm::mat4 view;
	glm::vec3 target = glm::vec3(m_cameraPosition.x + m_cameraRotation.x, m_cameraPosition.y + m_cameraRotation.y, m_cameraPosition.z + m_cameraRotation.z);
	view = glm::lookAt(glm::vec3(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z), target, glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int viewLoc = glGetUniformLocation(m_shaders[0]->getProgramId(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
	model = glm::rotate(glm::radians(m_rotationAngle), glm::vec3(0.3f, 0.5f, 0.8f));
	unsigned int modelLoc = glGetUniformLocation(m_shaders[0]->getProgramId(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.0f);
	unsigned int projectionLoc = glGetUniformLocation(m_shaders[0]->getProgramId(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	m_model->Draw(*m_shaders[0]);
}

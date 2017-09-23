#include "LightCasterTest.hpp"
#include <string>
// TODO: implement light caster
void LightCasterTest::init()
{
	glEnable(GL_DEPTH_TEST);
	m_rotationAngle = 0.0f;

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	std::string fileName[] = {
		"../source/app/resource/textures/container2.png",
		"../source/app/resource/textures/container2_specular.png"
	};

	for (int i = 0; i < 2; i++)
	{
		glGenTextures(2, &textures[i]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[i]);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char *data = stbi_load(fileName[i].c_str(), &width, &height, &nrChannels, STBI_rgb);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			printf("Texture loading failed");
		}
		stbi_set_flip_vertically_on_load(true);
		stbi_image_free(data);
	}

	// Cube
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(cubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	addShader(0, "light/lightmaptest.vert", "light/lightmaptest.frag", "");
	m_shaders[0]->useProgram();
	glUniform1i(glGetUniformLocation(m_shaders[0]->getProgramId(), "diffuseMap"), 0); // set it manually // TODO: No idea what does this line do or how is it working
	glUniform1i(glGetUniformLocation(m_shaders[0]->getProgramId(), "specularMap"), 1); // set it manually

}

void LightCasterTest::uninit()
{
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &VBO);
	glDisable(GL_DEPTH_TEST);
}

void LightCasterTest::update()
{
	m_rotationAngle += 1.0f;
}

void LightCasterTest::render()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// render cube
	m_shaders[0]->useProgram();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);

	m_shaders[0]->setVec3("lightPos", glm::vec3(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z));
	m_shaders[0]->setVec3("viewPos", glm::vec3(m_cameraPosition.x + m_cameraRotation.x, m_cameraPosition.y + m_cameraRotation.y, m_cameraPosition.z + m_cameraRotation.z));
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
}


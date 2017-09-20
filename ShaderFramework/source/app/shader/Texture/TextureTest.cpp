#include "TextureTest.hpp"
#include <string>

void TextureTest::init() {
	glEnable(GL_DEPTH_TEST);
	m_rotationAngle = 0.0f;
std::string fileName[] = {
	"../source/app/resource/textures/container.jpg",
//	"../source/app/resource/shader/diffuse/mouse_fall.PNG",
	"../source/app/resource/textures/awesomeface.png"
};

for (int i = 0; i < 2; i++)
{
	glGenTextures(1, &texture[i]);
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, texture[i]);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(fileName[i].c_str(), &width, &height, &nrChannels, STBI_rgb);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Texture loading failed");
	}
	stbi_set_flip_vertically_on_load(true);
	stbi_image_free(data);
}
	
float vertices[] = {
	// positions          // colors           // texture coords
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
glEnableVertexAttribArray(0);

glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);

glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);

setShader("texture/texturetest.vert", "texture/texturetest.frag");
glUniform1i(glGetUniformLocation(getProgramId(), "inTexture1"), 0); // set it manually
glUniform1i(glGetUniformLocation(getProgramId(), "inTexture2"), 1); // set it manually
	
glm::mat4 projection;
projection = glm::perspective(glm::radians(45.0f), (float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.0f);
unsigned int projectionLoc = glGetUniformLocation(getProgramId(), "projection");
glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void TextureTest::uninit() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDisable(GL_DEPTH_TEST);
}

void TextureTest::update() {
	m_rotationAngle += 0.1f;
}

void TextureTest::render() {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(m_cameraPosition.x, 1.0f, m_cameraPosition.z,
		m_cameraPosition.x + m_cameraRotation.x, 1.0f, m_cameraPosition.z + m_cameraRotation.z,
		0.0f, 1.0f, 0.0f);

	glm::mat4 view;
	glm::vec3 target = glm::vec3(m_cameraPosition.x + m_cameraRotation.x, m_cameraPosition.y + m_cameraRotation.y, m_cameraPosition.z + m_cameraRotation.z);
	view = glm::lookAt(glm::vec3(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z), target, glm::vec3(0.0f, 1.0f, 0.0f));
	unsigned int viewLoc = glGetUniformLocation(getProgramId(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	
	renderFrame(glm::vec3(1.0f, 0.0f, -5.0f), glm::vec3(0.3f, 0.5f, 0.0f), m_rotationAngle / 2.0f);
	renderFrame(glm::vec3(-1.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.5f, 0.0f), -m_rotationAngle / 2.0f);
}

void TextureTest::renderFrame(glm::vec3 pos, glm::vec3 axis, float angle)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glm::mat4 model;
	model = glm::translate(model, pos);
	model = glm::rotate(model, angle, axis);
	
	// retrieve the matrix uniform locations
	unsigned int modelLoc = glGetUniformLocation(getProgramId(), "model");
	// pass them to the shaders (3 different ways)
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
#pragma once

#include "../framework/shader/ShaderInterface.hpp"

class TextureTest : public sf::ShaderInterface {

private:
	void init() override;
	void uninit() override;

	void update() override;
	void render() override;

	void renderFrame(glm::vec3 pos, glm::vec3 axis, float angle);

	unsigned int VBO, VAO, EBO;
	GLuint texture[2];
	float m_rotationAngle;
public :
	TextureTest() {	}
	~TextureTest() { }
};
#pragma once

#include "../framework/shader/ShaderInterface.hpp"

class TextureTest : public sf::ShaderInterface {

private:
	void init() override;
	void uninit() override;

	void update() override;
	void render() override;

	unsigned int VBO, VAO, EBO;
	GLuint texture[2];

public :
	TextureTest() {	}
	~TextureTest() { }
};
#ifndef __FRAMEBUFFEERTEST_HPP__
#define __FRAMEBUFFEERTEST_HPP__

#include "../framework/shader/ShaderInterface.hpp"
#include "../framework/shader/Shader.hpp"

class FramebufferTest : public sf::ShaderInterface {
private:
	void init() override;
	void uninit() override;

	void update() override;
	void render() override;

	unsigned int VBO, cubeVAO;
	GLuint textures[2];
	float m_rotationAngle;

	unsigned int FBO, FBOTexture,RBO, quadVBO, quadVAO;

public:
	FramebufferTest() {	}
	~FramebufferTest() { }
};
#endif //__FRAMEBUFFEERTEST_HPP__
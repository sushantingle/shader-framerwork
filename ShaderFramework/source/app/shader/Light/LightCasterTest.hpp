#ifndef __HPP_LIGHTCASTERTEST__
#define __HPP_LIGHTCASTERTEST__
#include "../framework/shader/ShaderInterface.hpp"

class LightCasterTest : public sf::ShaderInterface {

public:
	LightCasterTest() { }
	~LightCasterTest() { }


private:

	void init() override;
	void uninit() override;

	void update() override;
	void render() override;

	unsigned int VBO, cubeVAO;
	GLuint textures[2];
	float m_rotationAngle;
};

#endif //__HPP_LIGHTCASTERTEST__

#ifndef __HPP_LIGHTMAPTEST__
#define __HPP_LIGHTMAPTEST__
#include "../framework/shader/ShaderInterface.hpp"

class LightMapTest : public sf::ShaderInterface {

public:
	LightMapTest() { }
	~LightMapTest() { }


private:

	void init() override;
	void uninit() override;

	void update() override;
	void render() override;

	unsigned int VBO, cubeVAO;
	GLuint textures[2];
	float m_rotationAngle;
};

#endif //__HPP_LIGHTMAPTEST__

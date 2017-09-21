#ifndef __HPP_LIGHTTEST__
#define __HPP_LIGHTTEST__
#include "../framework/shader/ShaderInterface.hpp"

class LightTest : public sf::ShaderInterface{

public:
	LightTest() { }
	~LightTest() { }


private:

	void init() override;
	void uninit() override;

	void update() override;
	void render() override;

	unsigned int VBO, cubeVAO, lightVao;
	float m_rotationAngle;
};

#endif //__HPP_LIGHTTEST__

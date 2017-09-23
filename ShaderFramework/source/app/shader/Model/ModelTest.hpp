#ifndef __MODELTEST_HPP__
#define __MODELTEST_HPP__

#include "../framework/shader/ShaderInterface.hpp"
#include "../framework/mesh/Model.hpp"

class ModelTest : public sf::ShaderInterface {

private:
	void init() override;
	void uninit() override;

	void update() override;
	void render() override;

	float m_rotationAngle;
	Model* m_model;
public:
	ModelTest() {	}
	~ModelTest() { }
};
#endif //__MODELTEST_HPP__

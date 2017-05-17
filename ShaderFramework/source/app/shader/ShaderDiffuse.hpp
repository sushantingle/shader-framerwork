#ifndef __SHADERDIFFUSE_HPP__
#define __SHADERDIFFUSE_HPP__

#include "../framework/shader/ShaderInterface.hpp"

class ShaderDiffuse : public sf::ShaderInterface {

private:
	void init() override;
	void uninit() override;

	void update() override;
	void render() override;

	int createSpecialMenu() override;
	void processSpecialMenuEvents(int menuId) override;
	// Member Variables
	float m_rotationAngle;

public:
	ShaderDiffuse():m_rotationAngle(0) {}
	~ShaderDiffuse() {}
};
#endif
#ifndef __SHADERDEFAULT_HPP__
#define __SHADERDEFAULT_HPP__

#include "../framework/shader/ShaderInterface.hpp"

class ShaderDefault : public sf::ShaderInterface {
private :
	void init() override;
	void uninit() override;
	
	void update() override; 
	void render() override;
	
	void renderSnowMan();


public:
	ShaderDefault() {}
	~ShaderDefault() {}
};
#endif //__SHADERDEFAULT_HPP__
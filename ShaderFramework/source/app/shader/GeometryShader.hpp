#ifndef __GEOMETRYSHADER_HPP__
#define __GEOMETRYSHADER_HPP__

#include "../framework/shader/ShaderInterface.hpp"

class GeometryShader : public sf::ShaderInterface {
public : 
	GeometryShader() {}
	~GeometryShader() {}

private:
	void init() override;
	void uninit() override;

	void update() override;
	void render() override;
};
#endif //__GEOMETRYSHADER_HPP__
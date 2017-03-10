#ifndef __DEFERREDRENDERING_HPP__
#define __DEFERREDRENDERING_HPP__

#include "../framework/shader/ShaderInterface.hpp"

class DeferredShader : public sf::ShaderInterface {

public:
	DeferredShader() {}
	~DeferredShader() {}

private:
	void init() override;
	void uninit() override;

	void update() override;
	void render() override;

	GLuint m_gBuffer;
	GLuint m_gPosition, m_gNormal, m_gAlbedoSpec;
	GLuint m_rboDepth;
	ShaderData m_gBufferShaderData;
};

#endif //__DEFERREDRENDERING_HPP__
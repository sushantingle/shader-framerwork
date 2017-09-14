#pragma once

#include "../framework/shader/ShaderInterface.hpp"

class TextureTest : public sf::ShaderInterface {

private:
	void init() override;
	void uninit() override;

	void update() override;
	void render() override;

public :
	TextureTest() {	}
	~TextureTest() { }
};
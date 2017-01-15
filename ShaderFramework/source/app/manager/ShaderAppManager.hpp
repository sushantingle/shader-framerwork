#ifndef __SHADERAPPMANAGER_HPP__
#define __SHADERAPPMANAGER_HPP__


class ShaderAppManager {
private:

	enum class ShaderType {
	SHADER_DEFAULT,
	};

public:
	ShaderAppManager();
	~ShaderAppManager();

	/************************************************************************/
	/* 
		Initializes manager in main function
	*/
	/************************************************************************/
	void init();

	/************************************************************************/
	/* 
		Updates app manager in render thread
	*/
	/************************************************************************/
	void update();

	/************************************************************************/
	/* 
		Process Keyboard inputs and mouse inputs
	*/
	/************************************************************************/
	void onNormalKeyboardKeyPressed(unsigned char key, int x, int y);
	void onSpecialKeyboardKeyPressed(int key, int x, int y);
	void onMouseButtonDown(int button, int state, int x, int y);
	void onMouseMoved(int x, int y);

};

#endif //__SHADERAPPMANAGER_HPP__
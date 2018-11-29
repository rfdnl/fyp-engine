#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

#ifndef GLFW_INCLUDE_GLU
#define GLFW_INCLUDE_GLU
#endif // GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>

class IDrawable{
	int type;
	unsigned int width;
	unsigned int height;
	bool visible;
protected:
	IDrawable(int type):type(type), visible(true){}
	static const unsigned int TEXTURE = 1;
	static const unsigned int SHAPE = 2;
public:
	virtual void Draw() = 0;
	int Type() { return type; }
	bool IsVisible() { return visible; }
	void Visible(bool visible){ this->visible = visible;}
};

#endif // IDRAWABLE_HPP

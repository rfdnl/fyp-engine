#ifndef INCLUDE_GL_HPP
#define INCLUDE_GL_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// /usr/bin/gcc test.c external/glew/src/glew.o external/glfw/lib/x11/libglfw.a -lXrandr -lX11 -pthread -lm -lGLU -lGL -o test

// trim file path
#include <string.h>
#include <iostream>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

// stop the program upon error
#define ASSERT(x) if (!(x)) __builtin_trap();

// print error
#define glCall(x)  glClearError();\
x;\
ASSERT(glLog(#x, __FILENAME__, __LINE__));

static inline bool glLog(const char* function, const char* file, int line){
	while (GLenum error = glGetError()){
		std::cout << "[OpenGL error] " << function << " - " << file << ":" << line << " - " << gluErrorString(error) << std::endl;
		return false;
	}
	return true;
}

static inline void glClearError(){
	if (glGetError() != GL_NO_ERROR);
}

#endif // INCLUDE_GLU_HPP

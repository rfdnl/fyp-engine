#include "Graphics.hpp"

bool Graphics::isOpen = false;

bool Graphics::InitWindow(){
    if (glfwInit() != GL_TRUE){
        ERROR("Cannot initialize GLFW");
        return false;
    }
    INFO("GLFW ready");
    return true;
    {
        // default configuration
        // GLFW_TRUE or GLFW_FALSE
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
        glfwWindowHint(GLFW_DECORATED, GL_TRUE);
        glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
        glfwWindowHint(GLFW_AUTO_ICONIFY, GL_TRUE);
        glfwWindowHint(GLFW_FLOATING, GL_FALSE);
        glfwWindowHint(GLFW_MAXIMIZED, GL_FALSE);
        glfwWindowHint(GLFW_STEREO, GL_FALSE);
        glfwWindowHint(GLFW_SRGB_CAPABLE, GL_FALSE);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE );
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT ,GLFW_FALSE );
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT ,GLFW_FALSE );

        // 0 to INT_MAX or GLFW_DONT_CARE
        glfwWindowHint(GLFW_RED_BITS , 8);
        glfwWindowHint(GLFW_GREEN_BITS, 8);
        glfwWindowHint(GLFW_BLUE_BITS, 8);
        glfwWindowHint(GLFW_ALPHA_BITS, 8);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);
        glfwWindowHint(GLFW_ACCUM_RED_BITS, 0);
        glfwWindowHint(GLFW_ACCUM_GREEN_BITS, 0);
        glfwWindowHint(GLFW_ACCUM_BLUE_BITS, 0);
        glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, 0);
        glfwWindowHint(GLFW_AUX_BUFFERS, 0);
        glfwWindowHint(GLFW_SAMPLES, 0);
        glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);

        // GLFW_OPENGL_API, GLFW_OPENGL_ES_API or GLFW_NO_API
        glfwWindowHint(GLFW_CLIENT_API ,GLFW_OPENGL_API );

        // GLFW_NATIVE_CONTEXT_API or GLFW_EGL_CONTEXT_API
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

        // Client Version {Major, Minor}, OpenGL 3.1 (Thinkpad T430)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        // GLFW_NO_ROBUSTNESS, GLFW_NO_RESET_NOTIFICATION or GLFW_LOSE_CONTEXT_ON_RESET
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS);

        // GLFW_ANY_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH or GLFW_RELEASE_BEHAVIOR_NONE
        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR,GLFW_ANY_RELEASE_BEHAVIOR );

        // GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_COMPAT_PROFILE or GLFW_OPENGL_CORE_PROFILE
        glfwWindowHint(GLFW_OPENGL_PROFILE ,GLFW_OPENGL_ANY_PROFILE );
    }
}

bool Graphics::Initialize(){
    return InitWindow();
}

bool Graphics::Create(const char* title, int width, int height, int x, int y){
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window){
        ERROR("Cannot create window");
        glfwTerminate();
        return false;
    }
    isOpen = true;
    INFO("Window created");
    glfwSetWindowPos(window, x, y);
    glfwMakeContextCurrent(window);
    glfwShowWindow(window);
    glfwSetWindowCloseCallback(window, WindowClosing);
    INFO("Window close callback set");
    return InitGraphics(width, height, x, y);
}

bool Graphics::IsOpen(){
    return isOpen;
}

bool Graphics::InitGraphics(int width, int height, int x, int y){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// The official code for "Setting Your Raster Position to a Pixel Location" (i.e. set up a camera for 2D screen)
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Make some OpenGL properties better for 2D and enable alpha channel.
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	if (CheckError("InitGraphics")) return false;
	INFO("OpenGL ready");
	return true;
}

void Graphics::PollEvents(){
    glfwPollEvents();
    //glfwWaitEvents();
}

void Graphics::WindowClosing(GLFWwindow* window){
    isOpen = false;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Graphics::Close(){
    if (isOpen) WindowClosing(window);
}

bool Graphics::CheckError(std::string functionName, int line, std::string comment){
	GLenum errorCode = glGetError();
	bool error = errorCode != GL_NO_ERROR;
    if (error){
        ERROR(ss << functionName << " -- OpenGL (" << errorCode << "), msg: " << gluErrorString(errorCode));
    }
    return error;
}

void Graphics::Draw(){
    glClear( GL_COLOR_BUFFER_BIT );

    /*
    glBegin( GL_QUADS );
        glVertex2f( -0.5f, -0.5f );
        glVertex2f(  0.5f, -0.5f );
        glVertex2f(  0.5f,  0.5f );
        glVertex2f( -0.5f,  0.5f );
    glEnd();
	*/
	for(unsigned int i = 0; i < onFrame.size(); i++){
		std::shared_ptr<Texture> texture = onFrame[i];
		texture->Draw();
		CheckError("Draw");
	}

	std::vector<std::shared_ptr<Texture>> emptyFrame;
	onFrame.clear();
	onFrame.swap(emptyFrame);

    glFlush();
    glfwSwapBuffers(window);
}

std::shared_ptr<Texture> Graphics::NewTexture(const char* filename){
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(filename);
	std::cout << "<" << texture.get()->Filename() << "> type: " << texture.get()->Type() << std::endl;
	return texture;
}

void Graphics::Draw(std::shared_ptr<Texture> texture){
	onFrame.push_back(texture);
}

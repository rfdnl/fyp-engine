#include "Graphics.hpp"

bool Graphics::isOpen = false;

Graphics::Graphics(std::shared_ptr<Logger> logPtr):
	ILoggable(logPtr, "Grfx")
{
	std::cout << "Graphics()" << std::endl;
}

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

    // CALLBACKS
    glfwSetWindowCloseCallback(window, WindowClosing);
    glfwSetWindowSizeCallback(window, Global::WindowResize);
    glfwSetKeyCallback(window, Input::KeyboardCallback);
    glfwSetMouseButtonCallback(window, Input::MouseButtonCallback);
    glfwSetCursorPosCallback(window, Input::MousePositionCallback);


    INFO("Window close callback set");
    return InitGraphics(width, height, x, y);
}

bool Graphics::IsOpen(){
    return isOpen;
}

bool Graphics::InitGraphics(int width, int height, int x, int y){
	// test start
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK){
		ERROR(ss << "GLEW init failed - " << glewGetErrorString(err));
		return false;
	}

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark();
	// test end

    SetClearColor(0.0f, 0.0f, 0.0f, 255.0f);

	// The official code for "Setting Your Raster Position to a Pixel Location" (i.e. set up a camera for 2D screen)
	glCall(glViewport(0, 0, width, height));
	glCall(glMatrixMode(GL_PROJECTION));
	glCall(glLoadIdentity());
	glCall(glOrtho(0, width, height, 0, -1, 1));
	glCall(glMatrixMode(GL_MODELVIEW));
	glCall(glLoadIdentity());

	// Make some OpenGL properties better for 2D and enable alpha channel.
	glCall(glDisable(GL_CULL_FACE));
	glCall(glDisable(GL_DEPTH_TEST));
	glCall(glEnable(GL_BLEND));
	glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	glCall(glDisable(GL_ALPHA_TEST));
	//wireframe
	//glCall(glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ));
	//glCall(glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ));

	//if (CheckError("InitGraphics")) return false;
	INFO(ss << "OpenGL v" << glGetString(GL_VERSION));

	return true;
}

void Graphics::PollEvents(){
    glfwPollEvents();
    //glfwWaitEvents();
}

void Graphics::WindowClosing(GLFWwindow* window){
    isOpen = false;
    //glCall(glDeleteProgram(shaderBuffer));
    //glfwDestroyWindow(window);
    //glfwTerminate();
}

void Graphics::Close(){
    if (isOpen){
		WindowClosing(window);
    }
}

bool Graphics::CheckError(std::string functionName, int line){
	GLenum errorCode = glGetError();
	bool error = errorCode != GL_NO_ERROR;
    if (error){
        ERROR(ss << functionName << " (" << errorCode << "), msg: " << gluErrorString(errorCode) << ", ln: " << line);
    }
    return error;
}

void Graphics::SetClearColor(float red, float green, float blue, float alpha){
	glCall(glClearColor(red, green, blue, alpha));
}

void Graphics::ClearColor(){
	glCall(glClear( GL_COLOR_BUFFER_BIT ));
}

void Graphics::ImGui_NewFrame(){
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Graphics::ImGui_Draw(){
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Graphics::Flush(){
	glCall(glFlush());
	glfwSwapBuffers(window);
}

void Graphics::SetWindowSize(int width, int height){
	glfwSetWindowSize(window, width, height);
}

Graphics::~Graphics(){
	std::cout << "~Graphics()" << std::endl;
	// test start
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
	// test end

	glfwDestroyWindow(window);
	glfwTerminate();
}

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
    return InitGraphics();
}

bool Graphics::IsOpen(){
    return isOpen;
}

bool Graphics::InitGraphics(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR){
        ERROR(ss << "OpenGL (" << gluErrorString(error) << "), code " << error);
        return false;
    }
    INFO("OpenGL ready");
    return true;
}

void Graphics::PollEvents(){
    glfwPollEvents();
    //glfwWaitEvents();
}

void Graphics::Draw(){
    glClear( GL_COLOR_BUFFER_BIT );

    glBegin( GL_QUADS );
        glVertex2f( -0.5f, -0.5f );
        glVertex2f(  0.5f, -0.5f );
        glVertex2f(  0.5f,  0.5f );
        glVertex2f( -0.5f,  0.5f );
    glEnd();

    glFlush();
    glfwSwapBuffers(window);
}

void Graphics::WindowClosing(GLFWwindow* window){
    isOpen = false;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Graphics::Close(){
    if (isOpen) WindowClosing(window);
}

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
	// test start
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK){
		ERROR(ss << "GLEW init failed - " << glewGetErrorString(err));
		return false;
	}
	// test end


    glCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));

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
	glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	glCall(glEnable(GL_BLEND));
	glCall(glDisable(GL_ALPHA_TEST));
	//if (CheckError("InitGraphics")) return false;
	INFO(ss << "OpenGL v" << glGetString(GL_VERSION));

	// test start
	float position[] = {
		-0.5f, -0.5f,	// 0
		0.5f, -0.5f, 	// 1
		0.5f, 0.5f, 	// 2
		-0.5f, 0.5f		// 3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	va = std::make_shared<VertexArray>();
	vb = std::make_shared<VertexBuffer>(position, 4 * 2 * sizeof(float));
	layout->Push<float>(2);
	va->AddBuffer(*vb, *layout);
	ib = std::make_shared<IndexBuffer>(indices, 3 * 2);
	shader = std::make_shared<Shader>("shader/Basic.shader");
	shader->Bind();
	shader->SetUniform4f("myColor", red, 0.3f, 0.8f, 1.0f);
	va->Unbind();
	vb->Unbind();
	ib->Unbind();
	shader->Unbind();

	// test end

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

	// clear memory here
    va.reset();
    vb.reset();
    ib.reset();
    layout.reset();
    shader.reset();
}

bool Graphics::CheckError(std::string functionName, int line){
	GLenum errorCode = glGetError();
	bool error = errorCode != GL_NO_ERROR;
    if (error){
        ERROR(ss << functionName << " (" << errorCode << "), msg: " << gluErrorString(errorCode) << ", ln: " << line);
    }
    return error;
}

void Graphics::Draw(){
	if (isOpen){
		glCall(glClear( GL_COLOR_BUFFER_BIT ));

		/*
		for(unsigned int i = 0; i < onFrame.size(); i++){
			std::shared_ptr<Texture> texture = onFrame[i];
			texture->Draw();
			//CheckError("Draw");
		}

		std::vector<std::shared_ptr<Texture>> emptyFrame;
		onFrame.clear();
		onFrame.swap(emptyFrame);
		*/

		// test start
		shader->Bind();
		shader->SetUniform4f("myColor", red, 0.3f, 0.8f, 1.0f);

		Draw(*va, *ib, *shader);

		if (red > 1.0f) increment = -0.05f;
		else if (red < 0.0f) increment = 0.05f;

		red += increment;
		// test end
		glCall(glFlush());
		glfwSwapBuffers(window);
	}
}

std::shared_ptr<Texture> Graphics::NewTexture(const char* filename){
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(filename);
	std::cout << "<" << texture.get()->Filename() << "> type: " << texture.get()->Type() << std::endl;
	return texture;
}

void Graphics::Draw(std::shared_ptr<Texture> texture){
	onFrame.push_back(texture);
}

void Graphics::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	/*
		shader.Bind();
		shader.SetUniform4f();
	*/
	shader.Bind();
	va.Bind();
	ib.Bind();
	glCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

Graphics::~Graphics(){
	std::cout << "~Graphics()" << std::endl;
	glfwDestroyWindow(window);
	glfwTerminate();
}

#include "Headers/Window.h"
#include <iostream>
#include "Headers/Shader.h"
#include "Headers/Input.h"

Window* Window::instance = nullptr;

Window* Window::Get()
{
	return instance;
}




#ifdef __clang__
	#define SET_KEY(key) case GLFW_KEY_##key: Input::SetKey(Key::key, (KeyState)action); break
#else
	#define SET_KEY(key) case GLFW_KEY_##key: Input::SetKey(Key::##key, (KeyState)action); break
#endif

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
		SET_KEY(W);
		SET_KEY(A);
		SET_KEY(S);
		SET_KEY(D);
		SET_KEY(E);
		SET_KEY(SPACE);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
		Input::SetKey(Key::RightMB, (KeyState)action);
	else if (button == GLFW_MOUSE_BUTTON_LEFT)
		Input::SetKey(Key::LeftMB, (KeyState)action);
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
		Input::SetKey(Key::MiddleMB, (KeyState)action);

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Input::SetMousePos(xpos,Window::GetResolution().y - ypos);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,width,height);
	Window::SetResolution(width, height);
	for (auto shader : Window::Get()->shaders)
	{
		shader->Bind();
		shader->SetProjectionMatrix();
	}
}

float Window::GetAspectRatio()
{
	return static_cast<float>(Get()->resolution.x) / static_cast<float>(Get()->resolution.y);
}

const glm::vec2& Window::GetResolution()
{
	return static_cast<glm::vec2>(Get()->resolution);
}

void Window::ViewportUpdate()
{
	Get()->viewportUpdated = true;
}

void Window::ClearShaders()
{
	Get()->shaders.clear();
}

void Window::AddShader(Shader* shader)
{
	Get()->shaders.push_back(shader);
}

void Window::SetResolution(uint32_t width, uint32_t height)
{
	Get()->resolution = {width,height};
	Get()->viewportUpdated = false;
}

Window::Window(std::string_view name)

	:monitor(glfwGetPrimaryMonitor()),
	isRunning(true)
{
	if (!monitor)
	{
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		monitor = monitors[0];
	}
	const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
	resolution.x = vidMode->width;
	resolution.y = vidMode->height;
	window = glfwCreateWindow(vidMode->width, vidMode->height, name.data(), monitor, nullptr);
	glfwMakeContextCurrent(window);

}

Window::Window(std::string_view name, const glm::uvec2& res)

	:monitor(nullptr),
	window(glfwCreateWindow(res.x, res.y, name.data(), nullptr, nullptr)),
	resolution(res),
	isRunning(true)
{
	glfwMakeContextCurrent(window);
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

void Window::Init(std::string_view name)
{
	if (instance)
		delete instance;
	if (!glfwInit())
	{
		throw - 1;
	}
	instance = new Window(std::move(name));
	glfwSetWindowSizeCallback(Get()->window, window_size_callback);
}

void Window::Init(std::string_view name, const glm::vec2& res)
{
	if (instance)
		delete instance;
	if (!glfwInit())
	{
		throw - 1;
	}
	instance = new Window(std::move(name), res);
	glfwSetWindowSizeCallback(Get()->window, window_size_callback);
	glfwSetKeyCallback(Get()->window, key_callback);
	glfwSetMouseButtonCallback(Get()->window, mouse_button_callback);
	glfwSetCursorPosCallback(Get()->window, mouse_callback);
}

void Window::Close()
{
	glfwSetWindowShouldClose(Get()->window, true);
}

void Window::Shutdown()
{
	if (instance)
		delete instance;
	instance = nullptr;
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(Get()->window);
	glfwPollEvents();
	Get()->isRunning = !glfwWindowShouldClose(Get()->window);
}

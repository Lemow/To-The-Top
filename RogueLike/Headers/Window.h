#pragma once
#include <string>
#include <string_view>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
class Shader;

class Window
{
public:

	static void Init(std::string_view name);
	static void Init(std::string_view name, const glm::vec2& res);
	// Closes Window
	static void Close(); 
	// Frees Memory
	static void Shutdown();

	static void SwapBuffers();

	static inline bool IsRunning()
	{
		return Get()->isRunning;
	}

	static Window* Get();

	static float GetAspectRatio();
	static const glm::vec2& GetResolution();
	static void ViewportUpdate();

	static void AddShader(Shader* shader);
	static void ClearShaders();

private:
	static Window* instance;
	static void SetResolution(uint32_t width, uint32_t height);

	friend void window_size_callback(GLFWwindow* window, int width, int height);

private:
	Window(std::string_view name);
	Window(std::string_view name, const glm::uvec2& res);
	~Window();
	std::vector<Shader*> shaders;
	GLFWmonitor* monitor;
	GLFWwindow* window;
	glm::uvec2 resolution;
	bool isRunning;
	bool viewportUpdated;
};
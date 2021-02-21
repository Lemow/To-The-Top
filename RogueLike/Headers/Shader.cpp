#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string_view>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"

Shader::Shader()
	:m_programID(0)
{
}

Shader::Shader(const std::string_view vPath, const std::string_view fPath)
{
	char infoLog[512];
	std::fstream vFile(vPath.data(), std::ios::in | std::ios::ate);
	std::fstream fFile(fPath.data(), std::ios::in | std::ios::ate);

	std::string vSource;
	std::string fSource;

	size_t vSize = vFile.tellg();
	size_t fSize = fFile.tellg();

	vFile.seekg(0);
	fFile.seekg(0);

	vSource.resize(vSize);
	vFile.read(vSource.data(), vSize);
	vFile.close();


	fSource.resize(fSize);
	fFile.read(fSource.data(), fSize);
	fFile.close();


	uint32_t vShader = glCreateShader(GL_VERTEX_SHADER);
	uint32_t fShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vCode = vSource.c_str();
	const char* fCode = fSource.c_str();

	glShaderSource(vShader,1, &vCode, NULL);
	glCompileShader(vShader);
	int success;
	glGetShaderiv(vShader,GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glShaderSource(fShader, 1, &fCode, NULL);
	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	m_programID = glCreateProgram();
	glAttachShader(m_programID, vShader);
	glAttachShader(m_programID, fShader);

	glLinkProgram(m_programID);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	glUseProgram(m_programID);

	uint32_t tLocation = glGetUniformLocation(m_programID, "u_textures");

	int samplers[32];

	for (int i = 0; i < 32; i++)
		samplers[i] = i;

	glUniform1iv(tLocation, 32, samplers);
	Window::AddShader(this);
	Bind();
	SetProjectionMatrix();
	m_cameraLocation = glGetUniformLocation(m_programID, "u_camera");
	Unbind();
}

Shader::~Shader()
{
	glDeleteProgram(m_programID);
}

Shader& Shader::operator=(Shader&& other)
{
	m_programID = other.m_programID;
	m_cameraLocation = other.m_cameraLocation;
	other.m_programID = 0;
	return *this;
}

void Shader::Bind() const
{
	glUseProgram(m_programID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

uint32_t Shader::GetUniformLocation(std::string_view uniformName) const
{
	return glGetUniformLocation(m_programID,uniformName.data());
}

void Shader::SetProjectionMatrix() const
{
	auto mat = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f/Window::GetResolution(), 1.0f));
	SetProjectionMatrix(mat);
}

void Shader::SetCameraUniform(float x, float y, float zoom) const
{
	glUniform3f(m_cameraLocation, x, y, zoom);
}

void Shader::SetProjectionMatrix(const glm::mat4& matrix) const
{
	uint32_t loc = GetUniformLocation("ortho");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
}

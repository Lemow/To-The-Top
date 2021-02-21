#pragma once
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader();
	Shader(const std::string_view vPath, const std::string_view fPath);
	~Shader();

	Shader& operator=(Shader&& other);

	void Bind()const;
	void Unbind()const;

	uint32_t GetUniformLocation(std::string_view uniformName) const;
	void SetProjectionMatrix(const glm::mat4& matrix) const;
	void SetProjectionMatrix() const;
	void SetCameraUniform(float x, float y,float zoom) const;

private:
	uint32_t m_programID;
	uint32_t m_cameraLocation;
};
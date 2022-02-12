#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/shader.h"
/*
	All the rendering stuff. Firstly move it here from the main.cpp
	and then implementing all in this file
*/

class Renderer
{
private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	float* m_Renderable;
	float m_Fov;
	float m_Aspect;
	glm::mat4 m_Projection;
	glm::mat4 m_View;
	glm::mat4 m_Model;
public:
	Renderer(float& renderable);
	~Renderer();

	void init(float& renderable);
	void bind();
	void draw(Shader& shader);
	void setProjection(const Shader& shader, const float& fov, const float& aspect);
	void setView(const Shader& shader, const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp);
	void setModel();
};
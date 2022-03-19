#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/shader.h"
/*
	Rendering everything here, including window.
	Gotta think of some good structure and opengl states modifications
*/

class GLFWwindow;

namespace graphics
{
	class Renderer
	{
	private:
		GLFWwindow* m_Window;
		unsigned int m_Width;
		unsigned int m_Height;
		const char* m_Title;

		unsigned int m_VAO;
		unsigned int m_VBO;
		float* m_Renderable;
		float m_Fov;
		float m_Aspect;
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_Model;
	public:
		Renderer() = default;
		~Renderer();

		void init(GLFWwindow* window);
		void bind();
		void draw(Shader& shader, glm::vec3 positions[]);
		void setProjection(const Shader& shader, const float& fov, const float& aspect);
		void setView(const Shader& shader, const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp);
		//void setModel(const Shader& shader, glm::vec3 positions[]);
	};
}

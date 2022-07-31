#ifndef WINDOW_H
#define WINDOW_H

/*
	NOT IMPLEMENTED YET
*/

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

/*
TBD: Function checking if the widnow is closed
	 Structure similar to this:
		 private:
			 const char* m_Title;
			 int m_Width, m_Height;
			 GLFWwindow* m_Window;
			 bool m_Closed;
		 public:
			Window(const char* title, int width, int height); 
			~Window();
			bool closed() const; glfwWindowShouldClose
			void update(); // swapbuffers, pollevents
			void clear() const; (?)

		void framebuffer_size_callback(GLFWwindow* window, int width, int height); // (???)
*/
namespace graphics
{
	class Window
	{
	private:
		bool m_Closed;
		const char* m_Title;
		int m_Width, m_Height;
	public:
		GLFWwindow* m_Window;
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		bool firstMouse = true;
		float yaw = -90.0f;
		float pitch = 0.0f;
		float lastX = 800.0f / 2.0f;
		float lastY = 600.0f / 2.0f;
		float fov = 45.0f;

		Window(const char* title, int width, int height);
		~Window();

		bool closed() const;
		bool init();
		void clear(float red, float green, float blue, float alpha) const;
		void update();
		void processInput();

		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void mause_callback(GLFWwindow* window, double xposIn, double yposIn);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}
#endif

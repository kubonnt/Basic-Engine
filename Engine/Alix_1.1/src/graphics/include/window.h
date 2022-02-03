#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
*/

class Window
{
private:
	float m_mixValue = 0.2f; // stores how much we're seeing of either textures 
public:
	Window(unsigned int width, unsigned int height, const char* title);
	~Window();

	void init();
	void processInput(GLFWwindow* window);

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
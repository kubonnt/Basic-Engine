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

		void framebuffer_size_callback(GLFWwindow* window, int width, int height); // (???)
*/

class Window
{
private:
	bool m_Closed; 
	const char* m_Title;
	int m_Width, m_Height;
	GLFWwindow* m_Window;
public:
	Window(const char* title, int width, int height);
	~Window();
	
	bool closed();
	
	bool init();
	void clear(float red, float green, float blue, float alpha);
	void update();

	
};
#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace alix
{
	namespace graphics
	{
		class Window
		{
		private:
			const char* m_Title;
			int m_Width;
			int m_Height;
			GLFWwindow* m_Window;
		public:
			Window(const char* title, int width, int height);
			~Window();

			// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
			// void processInput(GLFWwindow* window)
		};
	}
}
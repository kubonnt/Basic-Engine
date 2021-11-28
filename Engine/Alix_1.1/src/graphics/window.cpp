#include "window.h"

namespace alix
{
	namespace graphics
	{
		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void processInput(GLFWwindow* window)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
		}

		Window::Window(const char* title, int width, int height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;

			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
			if (m_Window == NULL)
			{
				std::cout << "Failed to create GLFW window!" << std::endl;
				glfwTerminate();
			}
			glfwMakeContextCurrent(m_Window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
			}

			glViewport(0, 0, m_Width, m_Height);
			glfwSetFramebufferSizeCallback(m_Window, (GLFWframebuffersizefun)framebuffer_size_callback);
		}

		Window::~Window()
		{
			glfwTerminate();
		}
	}
}
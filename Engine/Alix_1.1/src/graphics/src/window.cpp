#include "../include/window.h"

namespace graphics
{
	Window::Window(const char* title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height), m_Closed(false)
	{
		if (!init())
			glfwTerminate();
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	bool Window::init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glEnable(GL_DEPTH_TEST);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

		if (m_Window == nullptr)
		{
			std::cout << "Failed to create GLFW window!" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(m_Window);
		//glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback); 
		//glfwSetCursorPosCallback(m_Window, mause_callback);	// TODO: Create those functions
		//glfwSetScrollCallback(m_Window, scroll_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		return true;
	}

	void Window::clear(float red, float green, float blue, float alpha) const
	{
		glClearColor(red, green, blue, alpha);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void Window::processInput()
	{
		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_Window, true);

		const float cameraSpeed = static_cast<float>(10.0f * deltaTime);
		if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	void Window::mause_callback(GLFWwindow* window, double xposIn, double yposIn)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.5f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when the pitch is out of bounds the screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}

	void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		fov -= (float)yoffset;
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 45.0f)
			fov - 45.0f;
	}
}

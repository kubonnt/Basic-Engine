#include "../include/window.h"

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

bool Window::closed()
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

	if (m_Window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	//glfwMakeContextCurrent(m_Window);
	//glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback); 
	//glfwSetCursorPosCallback(m_Window, mause_callback);	// TODO: Create those functions
	//glfwSetScrollCallback(m_Window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}

void Window::clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}
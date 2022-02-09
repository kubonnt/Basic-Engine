#include "../include/window.h"

Window::Window(const char* title, int width, int height)
{

}

Window::~Window()
{
	glfwTerminate();
}

bool Window::closed()
{
	return glfwWindowShouldClose(m_Window);
}

void Window::init()
{

}

void Window::clear()
{

}

void Window::update()
{

}
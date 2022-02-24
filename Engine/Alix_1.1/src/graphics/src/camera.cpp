#include "../include/camera.h"

namespace graphics
{
	Camera::Camera(float yaw, float pitch, float lastX, float lastY, float fov)
		: m_Yaw(yaw), m_Pitch(pitch), m_LastX(lastX), m_LastY(lastY), m_Fov(fov)
	{
		glm::vec3 m_CamPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_CamFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_CamUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void Camera::processInput(Window& window)
	{

	}

	void Camera::mouse_callback(Window& window, double xposIn, double yposIn)
	{

	}

	void Camera::scroll_callback(Window& window, double xoffset, double yoffset)
	{

	}
}
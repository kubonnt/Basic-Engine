#pragma once

#include <glm/glm.hpp>

#include "window.h"

namespace graphics
{
	class Camera
	{
	private:
		glm::vec3 m_CamPos;
		glm::vec3 m_CamFront;
		glm::vec3 m_CamUp;

		float m_Yaw;
		float m_Pitch;
		float m_LastX;
		float m_LastY;
		float m_Fov;

		bool firstMouse = true;
	public:
		Camera(float yaw, float pitch, float lastX, float lastY, float fov);
		~Camera();

		void processInput(Window& window);
		void mouse_callback(Window& window, double xposIn, double yposIn);
		void scroll_callback(Window& window, double xoffset, double yoffset);
	};
}

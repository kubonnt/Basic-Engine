#pragma once

#include <glm/glm.hpp>

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
public:
	Camera(float yaw, float pitch, float lastX, float lastY, float fov);
};

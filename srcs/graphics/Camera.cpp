//
// Created by Marc on 12/04/2018.
//

#include "Camera.hpp"
#include "Display.hpp"

Camera::Camera()
	: m_position(Vec3<float>(0.0f, 0.0f, 0.0f)), m_rotation(Vec3<float>(0.0f, 0.0f, 0.0f))
{

}

Camera::Camera(const Vec3<float> &position)
	: m_position(position), m_rotation(Vec3<float>(0.0f, 0.0f, 0.0f))
{

}

Camera::~Camera()
{

}

int i = 0;
void Camera::input(const Display &display)
{
	i++;

	m_rotation.setY(sin(i * 0.03f) * 20);
	m_rotation.setX(i * 0.3f);

	if (glfwGetKey(display.getWindow(), GLFW_KEY_W))
		m_position.setZ(m_position.getZ() - 0.1f);
	if (glfwGetKey(display.getWindow(), GLFW_KEY_S))
		m_position.setZ(m_position.getZ() + 0.1f);
	if (glfwGetKey(display.getWindow(), GLFW_KEY_A))
		m_position.setX(m_position.getX() + 0.1f);
	if (glfwGetKey(display.getWindow(), GLFW_KEY_D))
		m_position.setX(m_position.getX() - 0.1f);
	if (glfwGetKey(display.getWindow(), GLFW_KEY_SPACE))
		m_position.setY(m_position.getY() - 0.1f);
	if (glfwGetKey(display.getWindow(), GLFW_KEY_LEFT_SHIFT))
		m_position.setY(m_position.getY() + 0.1f);
}

void Camera::update()
{
}

Mat4<float> Camera::getTransformation() const
{
	Mat4<float> perspective = Mat4<float>::perspective(80.0f, 1280.0f / 720.0f, 0.1f, 500.0f);
	Mat4<float> translation = Mat4<float>::translate(m_position);
	Mat4<float> rotation_x = Mat4<float>::rotate(Vec3<float>(1, 0, 0), -m_rotation.getY());
	Mat4<float> rotation_y = Mat4<float>::rotate(Vec3<float>(0, 1, 0), m_rotation.getX());

	return perspective * rotation_x * rotation_y * translation;
}
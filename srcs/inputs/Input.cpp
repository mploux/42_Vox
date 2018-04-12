//
// Created by Marc on 12/04/2018.
//

#include <Core.hpp>
#include "Input.hpp"

Input::Input(const Display &display)
	: m_display(display)
{
}

Input::~Input()
{

}

void Input::setupCallbacks()
{
	glfwSetKeyCallback(m_display.getWindow(), &keyCallback);
	glfwSetCharCallback(m_display.getWindow(), &characterCallback);
	glfwSetCursorPosCallback(m_display.getWindow(), &cursorPositionCallback);
	glfwSetMouseButtonCallback(m_display.getWindow(), &mouseButtonCallback);
}

void Input::update()
{
	std::cout << m_mousePosition << std::endl;
}

void Input::keyCallback(int key, int scancode, int action, int mods)
{

}

void Input::characterCallback(unsigned int codepoint)
{
}

void Input::cursorPositionCallback(double xpos, double ypos)
{
	m_mousePosition.setX(xpos);
	m_mousePosition.setY(ypos);
}

void Input::mouseButtonCallback(int button, int action, int mods)
{
}

const Vec2<int> &Input::getMousePosition() const
{
	return m_mousePosition;
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void) window;
	Core::getInstance().getInput().keyCallback(key, scancode, action, mods);
}

void Input::characterCallback(GLFWwindow* window, unsigned int codepoint)
{
	(void) window;
	Core::getInstance().getInput().characterCallback(codepoint);
}

void Input::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	(void) window;
	Core::getInstance().getInput().cursorPositionCallback(xpos, ypos);
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	(void) window;
	Core::getInstance().getInput().mouseButtonCallback(button, action, mods);
}
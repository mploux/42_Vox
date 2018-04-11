//
// Created by Marc on 11/04/2018.
//

#include <iostream>

#include "Display.hpp"
#include "Core.hpp"

#include "exceptions/glfw/GlfwInitException.hpp"
#include "exceptions/glfw/GlfwWindowCreationException.hpp"
#include "exceptions/glew/GlewInitException.hpp"

Display::Display()
	: m_title(""), m_width(0), m_height(0)
{
}

Display::Display(const std::string &title, const int &width, const int &height)
	: m_title(title), m_width(width), m_height(height)
{
	try
	{
		if (!glfwInit())
			throw GlfwInitException();

		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
		if (!m_window)
			throw GlfwWindowCreationException();

		glfwMakeContextCurrent(m_window);
		glViewport(0, 0, m_width, m_height);

		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
			throw GlewInitException();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		Core::getInstance().terminate();
	}
}

Display::~Display()
{
	glfwTerminate();
}

bool Display::closeRequested()
{
	return glfwWindowShouldClose(m_window) ? true : false;
}

void Display::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}
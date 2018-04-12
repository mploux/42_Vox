//
// Created by Marc on 12/04/2018.
//

#pragma once


#include <graphics/Display.hpp>
#include <maths/Vec2.hpp>
#include <vector>

class Input
{
private:
	const Display		&m_display;
	Vec2<int>			m_mousePosition;
	std::vector<int>	m_keys;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void characterCallback(GLFWwindow* window, unsigned int codepoint);
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

public:
	Input(const Display &display);
	virtual ~Input();

	void setupCallbacks();
	void update();

	void keyCallback(int key, int scancode, int action, int mods);
	void characterCallback(unsigned int codepoint);
	void cursorPositionCallback(double xpos, double ypos);
	void mouseButtonCallback(int button, int action, int mods);

	const Vec2<int> &getMousePosition() const;
};


//
// Created by Marc on 10/04/2018.
//
#pragma once

#include <world/World.hpp>
#include <graphics/Camera.hpp>
#include <inputs/Input.hpp>
#include "graphics/Display.hpp"

class Core
{
private:
	static Core	m_instance;
	Display		m_display;
	bool		m_running;
	World		m_world;
	Shader		m_shader;
	Camera		m_camera;
	Input		m_input;

public:
	Core();
	virtual ~Core();

	void update();
	void render();

	void start();
	void stop();
	void terminate();
	void loop();

	Display &getDisplay();
	Input &getInput();
	Camera &getCamera();

	static Core &getInstance();
};



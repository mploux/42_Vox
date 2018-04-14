//
// Created by Marc on 10/04/2018.
//
#pragma once

#include <world/World.hpp>
#include <graphics/Camera.hpp>
#include <inputs/Input.hpp>
#include <graphics/textures/Texture.hpp>
#include "graphics/Display.hpp"

#define RENDER_G_24 0
#define RENDER_G_4  1

class Core
{
private:
	static Core	m_instance;
	Display		m_display;
	bool		m_running;
	World		m_world;
	Shader		m_shader24;
	Shader		m_shader4;
	Camera		m_camera;
	Input		m_input;
	Texture		m_texture;
	int			m_renderMode;

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

	int getRenderMode() const;

	void setRenderMode(int renderMode);
};



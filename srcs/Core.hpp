//
// Created by Marc on 10/04/2018.
//
#pragma once

#include <world/World.hpp>
#include <graphics/Camera.hpp>
#include <inputs/Input.hpp>
#include <graphics/textures/Texture.hpp>
#include <world/blocks/Blocks.hpp>
#include "graphics/Display.hpp"

#define GET_BLOCK(name) Core::getInstance().getBlocks().getBlock(name)

#define RENDER_G_24 0
#define RENDER_G_4  1

class Core
{
private:
	static Core	m_instance;
	Display		m_display;
	bool		m_running;
	Shader		m_shader24;
	Shader		m_shader4;
	Camera		m_camera;
	Input		m_input;
	Texture		m_texture;
	int			m_renderMode;
	Blocks		m_blocks;
	World		*m_world;

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

	Blocks &getBlocks();

	void setRenderMode(int renderMode);
};



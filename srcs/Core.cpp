//
// Created by Marc on 10/04/2018.
//

#include <cstdlib>
#include <chrono>
#include <string>
#include <sstream>
#include "Core.hpp"

Core Core::m_instance = Core();

Core::Core()
	: m_display(Display("ft_vox", 1280, 720)),
	  m_running(false),
	  m_world(World(1)),
	  m_shader24(Shader("../data/shaders/24.vert", "../data/shaders/24.frag")),
	  m_shader4(Shader("../data/shaders/main.vert", "../data/shaders/main.frag")),
	  m_camera(Camera(Vec3<float>(-16 * CHUNK_SIZE, -20, -16 * CHUNK_SIZE))),
	  m_input(Input(m_display)),
	  m_texture(Texture("../data/textures/terrain.dds")),
	  m_renderMode(RENDER_G_24)
{
	m_input.setupCallbacks();
}

Core::~Core()
{}

void Core::update()
{
	if (m_input.getButtonDown(GLFW_MOUSE_BUTTON_LEFT))
		m_input.setFocused(true);
	if (m_input.getKeyDown(GLFW_KEY_ESCAPE))
		m_input.setFocused(false);

	m_input.update();
	m_camera.input(m_display);
	m_camera.update();
	m_world.update();

	if (m_input.getKeyDown(GLFW_KEY_R))
		m_renderMode = (m_renderMode + 1) % 2;

	m_input.reset();
}

void Core::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_texture.bind();

	if (m_renderMode == RENDER_G_24)
	{
		m_shader24.bind();
		m_shader24.setUniform("projectionMatrix", m_camera.getTransformation());
		m_shader24.setUniform("cameraPosition", m_camera.getPosition());
		m_world.render(m_shader24);
	}
	if (m_renderMode == RENDER_G_4)
	{
		m_shader4.bind();
		m_shader4.setUniform("projectionMatrix", m_camera.getTransformation());
		m_shader4.setUniform("cameraPosition", m_camera.getPosition());
		m_world.render(m_shader4);
	}
}

void Core::start()
{
	m_running = true;

	loop();
}

void Core::stop()
{
	m_running = false;
}

void Core::terminate()
{
	stop();
	std::cerr << "Vox terminated cleanly..." << std::endl;
	exit(-1);
}

void Core::loop()
{
	double tickTime = 1.0 / 60.0;

	int frames = 0;
	int time = 0;
	auto beforeTimeTicks = std::chrono::high_resolution_clock::now();

	while (m_running)
	{
		auto currentTimeTicks = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTicks = currentTimeTicks - beforeTimeTicks;
		if (elapsedTicks.count() > tickTime)
		{
			if (time % 60 == 0)
			{
				std::cout << "fps: " << frames << "\n";
				std::ostringstream stm ;
				stm << frames;
				std::string title = std::string("fps: ") + stm.str();
				if (m_renderMode == RENDER_G_24)
					title += "  | render mode: GEOMETRY 24";
				if (m_renderMode == RENDER_G_4)
					title += "  | render mode: GEOMETRY 4";
				glfwSetWindowTitle(m_display.getWindow(), title.c_str());
				frames = 0;
			}
			update();
			beforeTimeTicks = std::chrono::high_resolution_clock::now();
			time++;
		}
//		else
		{
			if (m_display.closeRequested())
				stop();
			render();
			frames++;
			m_display.update();
		}
	}
}

Display &Core::getDisplay() { return m_display; }
Camera &Core::getCamera() { return m_camera; }
Input &Core::getInput() { return m_input; }

Core &Core::getInstance() { return m_instance; }

int Core::getRenderMode() const
{
	return m_renderMode;
}

void Core::setRenderMode(int renderMode)
{
	m_renderMode = renderMode;
}

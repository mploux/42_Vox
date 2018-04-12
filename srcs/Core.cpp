//
// Created by Marc on 10/04/2018.
//

#include <cstdlib>
#include <chrono>
#include "Core.hpp"

Core Core::m_instance = Core();

Core::Core()
	: m_display(Display("ft_vox", 1280, 720)),
	  m_world(World()),
	  m_shader(Shader("data/shaders/main.vert", "data/shaders/main.frag")),
	  m_camera(Camera(Vec3<float>(-8, -8, -8))),
	  m_input(Input(m_display)),
	  m_running(false)
{
	m_input.setupCallbacks();
}

Core::~Core()
{}

void Core::update()
{
	m_input.update();
	m_camera.input(m_display);
	m_camera.update();
	m_world.update();
}

void Core::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader.bind();
	m_shader.setUniform("projectionMatrix", m_camera.getTransformation());

	m_world.render(m_shader);
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
	int frames = 0;
	int time = 0;

	double tickTime = 1.0 / 60.0;

	auto beforeTimeTicks = std::chrono::high_resolution_clock::now();
	auto beforeTimeSeconds = std::chrono::high_resolution_clock::now();

	while (m_running)
	{
		auto currentTimeTicks = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTicks = currentTimeTicks - beforeTimeTicks;
		if (elapsedTicks.count() > tickTime)
		{
			update();
			time++;
			beforeTimeTicks = std::chrono::high_resolution_clock::now();
		}

		if (m_display.closeRequested())
			stop();
		render();
		m_display.update();
		frames++;

		auto currentTimeSeconds = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedSeconds = currentTimeSeconds - beforeTimeSeconds;
		if (elapsedSeconds.count() > 1.0)
		{
			std::cout << "ticks: " << time << " fps: " << frames << std::endl;
			frames = 0;
			time = 0;
			beforeTimeSeconds = std::chrono::high_resolution_clock::now();
		}
	}
}

Display &Core::getDisplay() { return m_display; }
Camera &Core::getCamera() { return m_camera; }
Input &Core::getInput() { return m_input; }

Core &Core::getInstance() { return m_instance; }

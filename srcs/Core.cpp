//
// Created by Marc on 10/04/2018.
//

#include <cstdlib>
#include "Core.hpp"

Core Core::m_instance = Core();

Core::Core()
	: m_display(Display("ft_vox", 1280, 720)), m_running(false)
{

}

Core::~Core()
{}

void Core::update()
{

}

void Core::render()
{

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
	while (m_running)
	{
		if (m_display.closeRequested())
			stop();
		update();
		render();
		m_display.update();
	}
}

const Display &Core::getDisplay() const { return m_display; }

Core &Core::getInstance() { return m_instance; }

//
// Created by Marc on 10/04/2018.
//
#pragma once

#include "graphics/Display.hpp"

class Core
{
private:
	static Core	m_instance;

	Display		m_display;

	bool		m_running;

public:
	Core();
	virtual ~Core();

	void update();
	void render();

	void start();
	void stop();
	void terminate();
	void loop();

	const Display &getDisplay() const;

	static Core &getInstance();
};



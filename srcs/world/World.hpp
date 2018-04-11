//
// Created by Marc on 11/04/2018.
//

#pragma once

#include "graphics/IRendereable.hpp"

class World : public IRenderable
{
private:

public:
	World();
	virtual ~World();

	void render(const Shader &shader);
};


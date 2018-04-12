//
// Created by Marc on 11/04/2018.
//

#pragma once

#include "graphics/IRendereable.hpp"
#include "Chunk.hpp"

class Chunk;

class World : public IRenderable
{
private:
	Chunk *m_chunks;

public:
	World();
	virtual ~World();

	void update();
	void render(const Shader &shader);
};


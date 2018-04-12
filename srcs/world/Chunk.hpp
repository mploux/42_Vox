//
// Created by Marc on 11/04/2018.
//

#pragma once

#include "graphics/IRendereable.hpp"
#include "world/blocks/Block.hpp"
#include "World.hpp"

#define CHUNK_SIZE 16

class World;

class Chunk : public IRenderable
{
private:
	World	&m_world;
	Block	*m_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	GLuint	m_vao, m_vbo;
	int		m_renderSize;

public:
	Chunk(World &world);
	virtual ~Chunk();

	void generateBlocks();
	void generateRenderData();
	void generateVertexBuffer(const int &dataSize, GLfloat *data);

	void render(const Shader &shader);

	Block *getBlock(const int &x, const int &y, const int &z);
};

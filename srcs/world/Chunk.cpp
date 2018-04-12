//
// Created by Marc on 11/04/2018.
//

#include <world/blocks/blocks.hpp>
#include <iostream>
#include "Chunk.hpp"

Chunk::Chunk(World &world)
	: m_world(world)
{
	generateBlocks();
	generateRenderData();
}

Chunk::~Chunk()
{

}

void Chunk::generateBlocks()
{
	m_renderSize = 0;
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				m_blocks[x][y][z] = &blocks::stone;
				m_renderSize++;
			}
		}
	}
}

void Chunk::generateRenderData()
{
	GLfloat vertexData[m_renderSize * 3];

	int index = 0;
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				if (m_blocks[x][y][z]->getType() != 0)
				{
					vertexData[index++] = static_cast<float>(x);
					vertexData[index++] = static_cast<float>(y);
					vertexData[index++] = static_cast<float>(z);
				}
			}
		}
	}

	generateVertexBuffer(sizeof(vertexData), vertexData);
}

void Chunk::generateVertexBuffer(const int &dataSize, GLfloat *data)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Chunk::render(const Shader &shader)
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, m_renderSize);
	glBindVertexArray(0);
}

Block *Chunk::getBlock(const int &x, const int &y, const int &z)
{
	return m_blocks[x][y][z];
}

//
// Created by Marc on 11/04/2018.
//

#include <world/blocks/blocks.hpp>
#include <iostream>
#include "Chunk.hpp"

Chunk::Chunk(World &world, const Vec3<int> &pos)
	: m_world(world), m_pos(pos)
{
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
				Block *block = &blocks::stone;
				m_blocks[x][y][z] = block;
				m_renderSize++;
			}
		}
	}
}

void Chunk::generateRenderData()
{
	GLfloat vertexData[m_renderSize * 3];

	int index = 0;
	m_renderSize = 0;
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				if (m_blocks[x][y][z]->getType() != 0 && isBlockVisible(x, y, z))
				{
					vertexData[index++] = m_pos.getX() + static_cast<float>(x);
					vertexData[index++] = m_pos.getY() + static_cast<float>(y);
					vertexData[index++] = m_pos.getZ() + static_cast<float>(z);
					m_renderSize++;
				}
			}
		}
	}

	generateVertexBuffer(sizeof(GLfloat) * index, vertexData);
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

bool Chunk::isBlockVisible(const int &x, const int &y, const int &z)
{
	bool top = m_world.getBlock(m_pos.getX() + x, m_pos.getY() + y - 1, m_pos.getZ() + z) != nullptr;
	bool bottom = m_world.getBlock(m_pos.getX() + x, m_pos.getY() + y + 1, m_pos.getZ() + z) != nullptr;
	bool left = m_world.getBlock(m_pos.getX() + x - 1, m_pos.getY() + y, m_pos.getZ() + z) != nullptr;
	bool right = m_world.getBlock(m_pos.getX() + x + 1, m_pos.getY() + y, m_pos.getZ() + z) != nullptr;
	bool front = m_world.getBlock(m_pos.getX() + x, m_pos.getY() + y, m_pos.getZ() + z - 1) != nullptr;
	bool back = m_world.getBlock(m_pos.getX() + x, m_pos.getY() + y, m_pos.getZ() + z + 1) != nullptr;

	if (top && bottom && left && right && front && back)
		return false;
	return true;
}

Block *Chunk::getBlock(const int &x, const int &y, const int &z)
{
	if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
		return nullptr;

	return m_blocks[x][y][z];
}

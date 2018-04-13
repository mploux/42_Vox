//
// Created by Marc on 11/04/2018.
//

#include <world/blocks/blocks.hpp>
#include <iostream>
#include <cstdlib>
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
	std::srand(0);
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				if (y < 10 + std::rand() % 4)
				{
					m_blocks[x][y][z] = &blocks::stone;
					m_renderSize++;
				}
				else
					m_blocks[x][y][z] = &blocks::empty;
			}
		}
	}
}

void Chunk::generateRenderData()
{
	GLfloat vertexData[m_renderSize * 3];
	GLubyte facesData[m_renderSize];

	m_renderSize = 0;
	int vertexSize = 0;
	int facesSize = 0;
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				unsigned char visibleFaces = getBlockVisibleFaces(x, y, z);
				if (m_blocks[x][y][z]->getType() != 0 && visibleFaces != 0)
				{
					facesData[facesSize++] = visibleFaces;
					vertexData[vertexSize++] = m_pos.getX() + static_cast<float>(x);
					vertexData[vertexSize++] = m_pos.getY() + static_cast<float>(y);
					vertexData[vertexSize++] = m_pos.getZ() + static_cast<float>(z);
					m_renderSize++;
				}
			}
		}
	}

	generateVertexBuffer(sizeof(GLfloat) * vertexSize, vertexData, sizeof(GLint) * facesSize, facesData);
}

void Chunk::generateVertexBuffer(const int &dataSize, GLfloat *data, const int &facesSize, GLubyte *faces)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_dbo);

	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_dbo);
	glBufferData(GL_ARRAY_BUFFER, facesSize, faces, GL_STATIC_DRAW);
	glVertexAttribIPointer(1, 1, GL_UNSIGNED_BYTE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Chunk::render(const Shader &shader)
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, m_renderSize);
	glBindVertexArray(0);
}

unsigned char Chunk::getBlockVisibleFaces(const int &x, const int &y, const int &z)
{
	unsigned char result = 0;
	bool top = m_world.getBlock(m_pos.getX() + x, m_pos.getY() + y + 1, m_pos.getZ() + z)->getType() != 0;
	bool bottom = m_world.getBlock(m_pos.getX() + x, m_pos.getY() + y - 1, m_pos.getZ() + z)->getType() != 0;
	bool left = m_world.getBlock(m_pos.getX() + x - 1, m_pos.getY() + y, m_pos.getZ() + z)->getType() != 0;
	bool right = m_world.getBlock(m_pos.getX() + x + 1, m_pos.getY() + y, m_pos.getZ() + z)->getType() != 0;
	bool front = m_world.getBlock(m_pos.getX() + x, m_pos.getY() + y, m_pos.getZ() + z - 1)->getType() != 0;
	bool back = m_world.getBlock(m_pos.getX() + x, m_pos.getY() + y, m_pos.getZ() + z + 1)->getType() != 0;

	result |= top 		? 0 : (1 << 0);
	result |= bottom	? 0 : (1 << 1);
	result |= left		? 0 : (1 << 2);
	result |= right		? 0 : (1 << 3);
	result |= front		? 0 : (1 << 4);
	result |= back		? 0 : (1 << 5);

	return result;
}

Block *Chunk::getBlock(const int &x, const int &y, const int &z)
{
	if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
		return &blocks::empty;

	return m_blocks[x][y][z];
}

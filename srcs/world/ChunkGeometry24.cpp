//
// Created by Marc on 14/04/2018.
//

#include "ChunkGeometry24.hpp"
#include <world/blocks/blocks.hpp>
#include <iostream>
#include <cstdlib>

ChunkGeometry24::ChunkGeometry24()
	: m_world(nullptr), m_pos(ZERO)
{
}

ChunkGeometry24::ChunkGeometry24(World *world, const Vec3<int> &pos)
	: m_world(world), m_pos(pos)
{
}

ChunkGeometry24::~ChunkGeometry24()
{

}

void ChunkGeometry24::generateBlocks()
{
	m_renderSize = 0;
	std::srand(0);
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
//				m_blocks[x][y][z] = &blocks::STONE;
//				m_renderSize++;

				if (y < 10 + std::rand() % 4)
				{
//					m_blocks[x][y][z] = &blocks::STONE;

					int rnd = std::rand() % 2;
					if (rnd == 0)
						m_blocks[x][y][z] = &blocks::STONE;
					else if (rnd == 1)
						m_blocks[x][y][z] = &blocks::TNT;

					m_renderSize++;
				}
				else
					m_blocks[x][y][z] = &blocks::EMPTY;
			}
		}
	}
}

void ChunkGeometry24::generateRenderData()
{
	GLfloat vertexData[m_renderSize * 3];
	GLubyte textureData[m_renderSize * 6];
	GLubyte facesData[m_renderSize];

	m_renderSize = 0;
	int vertexSize = 0;
	int textureSize = 0;
	int facesSize = 0;
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				Block *block = m_blocks[x][y][z];
				unsigned char visibleFaces = getBlockVisibleFaces(x, y, z);
				if (block->getType() != 0 && visibleFaces != 0)
				{
					vertexData[vertexSize++] = m_pos.getX() + static_cast<float>(x);
					vertexData[vertexSize++] = m_pos.getY() + static_cast<float>(y);
					vertexData[vertexSize++] = m_pos.getZ() + static_cast<float>(z);

					textureData[textureSize++] = block->getTextureData()[0];
					textureData[textureSize++] = block->getTextureData()[1];
					textureData[textureSize++] = block->getTextureData()[2];
					textureData[textureSize++] = block->getTextureData()[3];
					textureData[textureSize++] = block->getTextureData()[4];
					textureData[textureSize++] = block->getTextureData()[5];

					facesData[facesSize++] = visibleFaces;

					m_renderSize++;
				}
			}
		}
	}

	generateVertexBuffer(
			sizeof(GLfloat) * vertexSize, vertexData,
			sizeof(GLubyte) * textureSize, textureData,
			sizeof(GLubyte) * facesSize, facesData);
}

void ChunkGeometry24::generateVertexBuffer(const int &dataSize, GLfloat *data, const int &textureSize, GLubyte *texture, const int &facesSize, GLubyte *faces)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_tbo);
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

	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, m_tbo);
	glBufferData(GL_ARRAY_BUFFER, textureSize, texture, GL_STATIC_DRAW);
	glVertexAttribIPointer(2, 2, GL_UNSIGNED_BYTE, 6 * 1, (void *) 0);
	glVertexAttribIPointer(3, 2, GL_UNSIGNED_BYTE, 6 * 1, (void *) 2);
	glVertexAttribIPointer(4, 2, GL_UNSIGNED_BYTE, 6 * 1, (void *) 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void ChunkGeometry24::render(const Shader &shader)
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, m_renderSize);
	glBindVertexArray(0);
}

unsigned char ChunkGeometry24::getBlockVisibleFaces(const int &x, const int &y, const int &z)
{
	unsigned char result = 0;

	bool top = m_world->getBlock(m_pos.getX() + x, m_pos.getY() + y + 1, m_pos.getZ() + z)->isRendered();
	bool bottom = m_world->getBlock(m_pos.getX() + x, m_pos.getY() + y - 1, m_pos.getZ() + z)->isRendered();
	bool left = m_world->getBlock(m_pos.getX() + x - 1, m_pos.getY() + y, m_pos.getZ() + z)->isRendered();
	bool right = m_world->getBlock(m_pos.getX() + x + 1, m_pos.getY() + y, m_pos.getZ() + z)->isRendered();
	bool front = m_world->getBlock(m_pos.getX() + x, m_pos.getY() + y, m_pos.getZ() + z - 1)->isRendered();
	bool back = m_world->getBlock(m_pos.getX() + x, m_pos.getY() + y, m_pos.getZ() + z + 1)->isRendered();

	result |= top 		? 0 : (1 << 0);
	result |= bottom	? 0 : (1 << 1);
	result |= left		? 0 : (1 << 2);
	result |= right		? 0 : (1 << 3);
	result |= front		? 0 : (1 << 4);
	result |= back		? 0 : (1 << 5);

	return result;
}

Block *ChunkGeometry24::getBlock(const int &x, const int &y, const int &z)
{
	if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
		return &blocks::VOID;
	return m_blocks[x][y][z];
}

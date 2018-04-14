//
// Created by Marc on 11/04/2018.
//

#include <world/blocks/blocks.hpp>
#include <iostream>
#include <cstdlib>
#include "Chunk.hpp"

Chunk::Chunk()
	: m_pos(ZERO), m_world(nullptr)
{
}

Chunk::Chunk(World *world, const Vec3<int> &pos)
	: m_pos(pos), m_world(world)
{
}

Chunk::~Chunk()
{

}

void Chunk::generateBlocks()
{
	m_renderSizeG4 = 0;
	m_renderSizeG24 = 0;
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

					m_renderSizeG4++;
					m_renderSizeG24++;
				}
				else
					m_blocks[x][y][z] = &blocks::EMPTY;
			}
		}
	}
}

void Chunk::generateRenderDataG4()
{
	GLfloat vertexData[m_renderSizeG4 * 6 * 3];
	GLubyte textureData[m_renderSizeG4 * 6];
	GLubyte facesData[m_renderSizeG4 * 6];

	m_renderSizeG4 = 0;
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
					for (int i = 0; i < 6; i++)
					{
						if (visibleFaces & (1 << i))
						{
							vertexData[vertexSize++] = m_pos.getX() + static_cast<float>(x);
							vertexData[vertexSize++] = m_pos.getY() + static_cast<float>(y);
							vertexData[vertexSize++] = m_pos.getZ() + static_cast<float>(z);

							textureData[textureSize++] = block->getTextureData()[i];

							facesData[facesSize++] = static_cast<GLubyte >(i);

							m_renderSizeG4++;
						}
					}
				}
			}
		}
	}

	generateVertexBufferG4(
			sizeof(GLfloat) * vertexSize, vertexData,
			sizeof(GLubyte) * textureSize, textureData,
			sizeof(GLubyte) * facesSize, facesData);
}

void Chunk::generateVertexBufferG4(const int &dataSize, GLfloat *data, const int &textureSize, GLubyte *texture, const int &facesSize, GLubyte *faces)
{
	glGenVertexArrays(1, &m_vaoG4);
	glGenBuffers(1, &m_vboG4);
	glGenBuffers(1, &m_tboG4);
	glGenBuffers(1, &m_dboG4);

	glBindVertexArray(m_vaoG4);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboG4);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_dboG4);
	glBufferData(GL_ARRAY_BUFFER, facesSize, faces, GL_STATIC_DRAW);
	glVertexAttribIPointer(1, 1, GL_UNSIGNED_BYTE, 0, nullptr);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_tboG4);
	glBufferData(GL_ARRAY_BUFFER, textureSize, texture, GL_STATIC_DRAW);
	glVertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Chunk::renderG4(const Shader &shader)
{
	(void) shader;

	glBindVertexArray(m_vaoG4);
	glDrawArrays(GL_POINTS, 0, m_renderSizeG4);
	glBindVertexArray(0);
}

void Chunk::generateRenderDataG24()
{
	GLfloat vertexData[m_renderSizeG24 * 3];
	GLubyte textureData[m_renderSizeG24 * 6];
	GLubyte facesData[m_renderSizeG24];

	m_renderSizeG24 = 0;
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

					m_renderSizeG24++;
				}
			}
		}
	}

	generateVertexBufferG24(
			sizeof(GLfloat) * vertexSize, vertexData,
			sizeof(GLubyte) * textureSize, textureData,
			sizeof(GLubyte) * facesSize, facesData);
}

void Chunk::generateVertexBufferG24(const int &dataSize, GLfloat *data, const int &textureSize, GLubyte *texture, const int &facesSize, GLubyte *faces)
{
	glGenVertexArrays(1, &m_vaoG24);
	glGenBuffers(1, &m_vboG24);
	glGenBuffers(1, &m_tboG24);
	glGenBuffers(1, &m_dboG24);

	glBindVertexArray(m_vaoG24);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboG24);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_dboG24);
	glBufferData(GL_ARRAY_BUFFER, facesSize, faces, GL_STATIC_DRAW);
	glVertexAttribIPointer(1, 1, GL_UNSIGNED_BYTE, 0, nullptr);

	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, m_tboG24);
	glBufferData(GL_ARRAY_BUFFER, textureSize, texture, GL_STATIC_DRAW);
	glVertexAttribIPointer(2, 2, GL_UNSIGNED_BYTE, 6 * 1, (void *) 0);
	glVertexAttribIPointer(3, 2, GL_UNSIGNED_BYTE, 6 * 1, (void *) 2);
	glVertexAttribIPointer(4, 2, GL_UNSIGNED_BYTE, 6 * 1, (void *) 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Chunk::renderG24(const Shader &shader)
{
	(void) shader;

	glBindVertexArray(m_vaoG24);
	glDrawArrays(GL_POINTS, 0, m_renderSizeG24);
	glBindVertexArray(0);
}

void Chunk::render(const Shader &shader)
{
	(void) shader;
}

unsigned char Chunk::getBlockVisibleFaces(const int &x, const int &y, const int &z)
{
	unsigned char result = 0;
	std::cout << m_world->getBlock(0, 0, 0)->isOpaque() << std::endl;
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

Block *Chunk::getBlock(const int &x, const int &y, const int &z)
{
	if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
		return &blocks::VOID;
	return m_blocks[x][y][z];
}

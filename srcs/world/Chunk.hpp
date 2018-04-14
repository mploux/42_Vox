//
// Created by Marc on 11/04/2018.
//

#pragma once

#include "graphics/IRendereable.hpp"
#include "world/blocks/Block.hpp"
#include "World.hpp"

#define CHUNK_SIZE 1

class World;

class Chunk : public IRenderable
{
private:
	Vec3<int>	m_pos;
	World		*m_world;
	Block		*m_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

	GLuint		m_vaoG24, m_vboG24, m_tboG24, m_dboG24;
	int			m_renderSizeG24;

	GLuint		m_vaoG4, m_vboG4, m_tboG4, m_dboG4;
	int			m_renderSizeG4;

public:
	Chunk();
	Chunk(World *world, const Vec3<int> &pos);
	virtual ~Chunk();

	void generateBlocks();

	void generateRenderDataG24();
	void generateRenderDataG4();

	void generateVertexBufferG24(const int &dataSize, GLfloat *data, const int &textureSize, GLubyte *texture, const int &facesSize, GLubyte *faces);
	void generateVertexBufferG4(const int &dataSize, GLfloat *data, const int &textureSize, GLubyte *texture, const int &facesSize, GLubyte *faces);

	void renderG24(const Shader &shader);
	void renderG4(const Shader &shader);
	void render(const Shader &shader);

	unsigned char getBlockVisibleFaces(const int &x, const int &y, const int &z);
	Block *getBlock(const int &x, const int &y, const int &z);
};

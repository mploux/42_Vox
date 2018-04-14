#pragma once

#include "graphics/IRendereable.hpp"
#include "world/blocks/Block.hpp"
#include "World.hpp"

#define CHUNK_SIZE 16

class World;

class ChunkGeometry24 : public IRenderable
{
private:
	Vec3<int>	m_pos;
	World		*m_world;
	Block		*m_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	GLuint		m_vao, m_vbo, m_tbo, m_dbo;
	int			m_renderSize;

public:
	ChunkGeometry24();
	ChunkGeometry24(World *world, const Vec3<int> &pos);
	virtual ~ChunkGeometry24();

	void generateBlocks();
	void generateRenderData();
	void generateVertexBuffer(const int &dataSize, GLfloat *data, const int &textureSize, GLubyte *texture, const int &facesSize, GLubyte *faces);

	void render(const Shader &shader);

	unsigned char getBlockVisibleFaces(const int &x, const int &y, const int &z);
	Block *getBlock(const int &x, const int &y, const int &z);
};

//
// Created by Marc on 11/04/2018.
//

#include <iostream>
#include <cstdlib>
#include <Core.hpp>
#include "Chunk.hpp"

Chunk::Chunk()
	: m_pos(ZERO),
	  m_world(nullptr),
	  m_initalized(false),
	  m_generated(false),
	  m_rendered(false),
	  m_renderer(ChunkRenderer(*this)),
	  m_leftStatus(1),
	  m_rightStatus(1),
	  m_topStatus(1),
	  m_bottomStatus(1),
	  m_frontStatus(1),
	  m_backStatus(1),
	  m_visible(true)
{
}

Chunk::~Chunk()
{
}

void Chunk::init(World *world, const Vec3<int> &pos)
{
	m_pos = pos;
	m_world = world;
	m_initalized = true;
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
				if (y + m_pos.getY() < 8)
				{
					int rnd = std::rand() % 2;
					if (rnd == 0)
						m_blocks[getBlockIndex(x, y, z)] = GET_BLOCK("stone");
					else if (rnd == 1)
						m_blocks[getBlockIndex(x, y, z)] = GET_BLOCK("glass");
					m_renderSize++;
				}
				else
					m_blocks[getBlockIndex(x, y, z)] = GET_BLOCK("empty");

				ABlock *block = m_blocks[getBlockIndex(x, y, z)];

//				m_leftStatus = (x == 0 && block->isOpaque()) ? (char)0 : (char)1;
//				m_bottomStatus = (y == 0 && block->isOpaque()) ? (char)0 : (char)1;
//				m_frontStatus = (z == 0 && block->isOpaque()) ? (char)0 : (char)1;
//				m_rightStatus = (x == CHUNK_SIZE - 1 && block->isOpaque()) ? (char)0 : (char)1;
//				m_topStatus = (y == CHUNK_SIZE - 1 && block->isOpaque()) ? (char)0 : (char)1;
//				m_backStatus = (z == CHUNK_SIZE - 1 && block->isOpaque()) ? (char)0 : (char)1;
			}
		}
	}
	m_bottomStatus = 0;
	m_topStatus = 0;

	m_renderer.setRenderSize(m_renderSize);
	m_generated = true;
}

void Chunk::generateRenderData()
{
	m_renderer.generateRenderData();
}

void Chunk::update()
{
	if (!m_rendered)
	{
		if (isReadyToRender())
		{
			generateRenderData();
			m_rendered = true;
		}
	}
}

void Chunk::updateCulling()
{
	m_visible = isInViewFrustum(Core::getInstance().getCamera().getTransformation());
}

void Chunk::render(const Shader &shader)
{
	if (!m_visible)
		return;
	m_renderer.render(shader);
}

bool Chunk::isInViewFrustum(const Mat4<float> &projection)
{
	Vec4<float> bound[8];
	Mat4<float> mvp = projection;

	float size = CHUNK_SIZE;
	bound[0] = Mat4<float>::transform(mvp, Vec4<float>(m_pos.getX(), m_pos.getY(), m_pos.getZ(), 1));
	bound[1] = Mat4<float>::transform(mvp, Vec4<float>(m_pos.getX(), m_pos.getY(), m_pos.getZ() + size, 1));
	bound[2] = Mat4<float>::transform(mvp, Vec4<float>(m_pos.getX(), m_pos.getY() + size, m_pos.getZ(), 1));
	bound[3] = Mat4<float>::transform(mvp, Vec4<float>(m_pos.getX(), m_pos.getY() + size, m_pos.getZ() + size, 1));
	bound[4] = Mat4<float>::transform(mvp, Vec4<float>(m_pos.getX() + size, m_pos.getY(), m_pos.getZ(), 1));
	bound[5] = Mat4<float>::transform(mvp, Vec4<float>(m_pos.getX() + size, m_pos.getY(), m_pos.getZ() + size, 1));
	bound[6] = Mat4<float>::transform(mvp, Vec4<float>(m_pos.getX() + size, m_pos.getY() + size, m_pos.getZ(), 1));
	bound[7] = Mat4<float>::transform(mvp, Vec4<float>(m_pos.getX() + size, m_pos.getY() + size, m_pos.getZ() + size, 1));

	int c[6] = {0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 8; i++)
	{
		if (bound[i].getX() < -bound[i].getW())
			c[0]++;
		if (bound[i].getX() > bound[i].getW())
			c[1]++;
		if (bound[i].getY() < -bound[i].getW())
			c[2]++;
		if (bound[i].getY() > bound[i].getW())
			c[3]++;
		if (bound[i].getZ() < -bound[i].getW())
			c[4]++;
		if (bound[i].getZ() > bound[i].getW())
			c[5]++;
	}
	if (c[0] == 8 || c[1] == 8 || c[2] == 8 || c[3] == 8 || c[4] == 8 || c[5] == 8)
		return false;

	return true;
}

int Chunk::getBlockIndex(const int &x, const int &y, const int &z) const
{
	int index = x * CHUNK_SIZE * CHUNK_SIZE + y * CHUNK_SIZE + z;
	return index;
}

unsigned char Chunk::getBlockVisibleFaces(const int &x, const int &y, const int &z) const
{
	unsigned char result = 0;

	bool opaque = getBlock(x, y, z).isOpaque();
	bool top = m_world->getBlock(m_pos.getX() + x, m_pos.getY() + y + 1, m_pos.getZ() + z).isRendered(opaque);
	bool bottom = m_world->getBlock(m_pos.getX() + x, m_pos.getY() + y - 1, m_pos.getZ() + z).isRendered(opaque);
	bool left = m_world->getBlock(m_pos.getX() + x - 1, m_pos.getY() + y, m_pos.getZ() + z).isRendered(opaque);
	bool right = m_world->getBlock(m_pos.getX() + x + 1, m_pos.getY() + y, m_pos.getZ() + z).isRendered(opaque);
	bool front = m_world->getBlock(m_pos.getX() + x, m_pos.getY() + y, m_pos.getZ() + z - 1).isRendered(opaque);
	bool back = m_world->getBlock(m_pos.getX() + x, m_pos.getY() + y, m_pos.getZ() + z + 1).isRendered(opaque);

	result |= top 		? 0 : (1 << 0);
	result |= bottom	? 0 : (1 << 1);
	result |= left		? 0 : (1 << 2);
	result |= right		? 0 : (1 << 3);
	result |= front		? 0 : (1 << 4);
	result |= back		? 0 : (1 << 5);

	return result;
}

ABlock &Chunk::getBlock(const int &x, const int &y, const int &z) const
{
	if (!m_generated)
		return *GET_BLOCK("void");
	if (x < 0 || y < 0 || z < 0 || x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE)
		return *GET_BLOCK("void");
	return *m_blocks[getBlockIndex(x, y, z)];
}

bool Chunk::isReadyToGenerate() const
{
	if (!m_initalized)
		return false;

	Vec3<int> pos = Vec3<int>(m_pos) / CHUNK_SIZE;

	const Chunk *bottomChunk 	= m_world->getChunk(pos.getX(), pos.getY() - 1, pos.getZ());
	const Chunk *topChunk 		= m_world->getChunk(pos.getX(), pos.getY() + 1, pos.getZ());
	const Chunk *leftChunk 		= m_world->getChunk(pos.getX() - 1, pos.getY(), pos.getZ());
	const Chunk *rightChunk		= m_world->getChunk(pos.getX() + 1, pos.getY(), pos.getZ());
	const Chunk *frontChunk		= m_world->getChunk(pos.getX(), pos.getY(), pos.getZ() - 1);
	const Chunk *backChunk 		= m_world->getChunk(pos.getX(), pos.getY(), pos.getZ() + 1);

	bool bottom = bottomChunk == nullptr || (bottomChunk != nullptr && bottomChunk->getBottomStatus() != 0);
	bool top 	= topChunk == nullptr || (topChunk != nullptr && topChunk->getTopStatus() != 0);
	bool left 	= leftChunk == nullptr || (leftChunk != nullptr && leftChunk->getLeftStatus() != 0);
	bool right 	= rightChunk == nullptr || (rightChunk != nullptr && rightChunk->getRightStatus() != 0);
	bool front 	= frontChunk == nullptr || (frontChunk != nullptr && frontChunk->getFrontStatus() != 0);
	bool back 	= backChunk == nullptr || (backChunk != nullptr && backChunk->getBackStatus() != 0);

	return bottom && top && left && right && front && back;
}

bool Chunk::isReadyToRender() const
{
	if (!m_generated)
		return false;

	Vec3<int> pos = Vec3<int>(m_pos) / CHUNK_SIZE;

	const Chunk *bottomChunk 	= m_world->getChunk(pos.getX(), pos.getY() - 1, pos.getZ());
	const Chunk *topChunk 		= m_world->getChunk(pos.getX(), pos.getY() + 1, pos.getZ());
	const Chunk *leftChunk 		= m_world->getChunk(pos.getX() - 1, pos.getY(), pos.getZ());
	const Chunk *rightChunk		= m_world->getChunk(pos.getX() + 1, pos.getY(), pos.getZ());
	const Chunk *frontChunk		= m_world->getChunk(pos.getX(), pos.getY(), pos.getZ() - 1);
	const Chunk *backChunk 		= m_world->getChunk(pos.getX(), pos.getY(), pos.getZ() + 1);

	bool bottom 	= bottomChunk == nullptr || (bottomChunk != nullptr && bottomChunk->isGenerated());
	bool top 		= topChunk == nullptr || (topChunk != nullptr && topChunk->isGenerated());
	bool left 		= leftChunk == nullptr || (leftChunk != nullptr && leftChunk->isGenerated());
	bool right 		= rightChunk == nullptr || (rightChunk != nullptr && rightChunk->isGenerated());
	bool front 		= frontChunk == nullptr || (frontChunk != nullptr && frontChunk->isGenerated());
	bool back 		= backChunk == nullptr || (backChunk != nullptr && backChunk->isGenerated());

	return bottom && top && left && right && front && back;
}

const Vec3<int> &Chunk::getPosition() const
{
	return m_pos;
}

bool Chunk::isInitialized() const
{
	return m_initalized;
}

bool Chunk::isGenerated() const
{
	return m_generated;
}

bool Chunk::isRendered() const
{
	return m_rendered;
}

bool Chunk::isVisible() const
{
	return m_visible;
}

char Chunk::getTopStatus() const
{
	return m_topStatus;
}

char Chunk::getBottomStatus() const
{
	return m_bottomStatus;
}

char Chunk::getLeftStatus() const
{
	return m_leftStatus;
}

char Chunk::getRightStatus() const
{
	return m_rightStatus;
}

char Chunk::getFrontStatus() const
{
	return m_frontStatus;
}

char Chunk::getBackStatus() const
{
	return m_backStatus;
}

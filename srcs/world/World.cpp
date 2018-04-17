//
// Created by Marc on 11/04/2018.
//

#include <Core.hpp>
#include <thread>
#include <iostream>
//#include <mingw.thread.h>

World::World(int size)
	: m_size(size), m_height(1)
{
	m_chunks = new Chunk[m_size * m_height * m_size];
	m_chunkGenerationThread = std::thread(&World::generateChunks, this);
}

World::~World()
{
	m_chunkGenerationThread.join();
	delete[] m_chunks;
}

void World::generateChunk(const int &x, const int &y, const int &z)
{
	if (!(x < 0 || x >= m_size || y < 0 || y >= m_height || z < 0 || z >= m_size))
	{
		Chunk &chunk = m_chunks[getChunkIndex(x, y, z)];
		if (!chunk.isInitialized())
		{
			Vec3<int> pos(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE);
			chunk.init(this, pos);
			addChunkToGenerate(&chunk);
		}
	}
}

void World::generateChunks()
{
	std::cout << "LOL" << "\n";
	while (Core::getInstance().isRunning())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		if (m_chunksToGenerate.empty())
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		int generatedChunks = 0;
		while (!m_chunksToGenerate.empty() && generatedChunks < 1)
		{
			Chunk *c = m_chunksToGenerate.front();
			c->generateBlocks();
			m_renderedChunks.push_back(c);
			m_chunksToGenerate.pop_front();
			generatedChunks++;
		}
	}
}

void World::update()
{
	Vec3<float> player = Core::getInstance().getCamera().getPosition();
	int px = -static_cast<int>(ceilf(player.getX() / CHUNK_SIZE));
	int py = -static_cast<int>(ceilf(player.getY() / CHUNK_SIZE));
	int pz = -static_cast<int>(ceilf(player.getZ() / CHUNK_SIZE));

	generateChunk(px, py, pz);
	generateChunk(px - 1, py, pz);
	generateChunk(px + 1, py, pz);
	generateChunk(px, py - 1, pz);
	generateChunk(px, py + 1, pz);
	generateChunk(px, py, pz - 1);
	generateChunk(px, py, pz + 1);

	for (int i = 0; i < m_size * m_height * m_size; i++)
		m_chunks[i].update();
	for (size_t i = 0; i < m_renderedChunks.size(); i++)
		m_renderedChunks[i]->updateCulling();
}

void World::render(const Shader &shader)
{
	for (size_t i = 0; i < m_renderedChunks.size(); i++)
		m_renderedChunks[i]->render(shader);
}

void World::addChunkToGenerate(Chunk *chunk)
{
	m_chunksToGenerate.push_back(chunk);
}

ABlock &World::getBlock(const int &x, const int &y, const int &z)
{
	int cx = x / CHUNK_SIZE;
	int cy = y / CHUNK_SIZE;
	int cz = z / CHUNK_SIZE;
	int bx = x % CHUNK_SIZE;
	int by = y % CHUNK_SIZE;
	int bz = z % CHUNK_SIZE;

	if (cx < 0 || cx >= m_size || cy < 0 || cy >= m_height || cz < 0 || cz >= m_size)
		return *GET_BLOCK("void");
	return getChunk(cx, cy, cz)->getBlock(bx, by, bz);
}

Chunk *World::getChunk(const int &x, const int &y, const int &z)
{
	if (x < 0 || x >= m_size || y < 0 || y >= m_height || z < 0 || z >= m_size)
		return nullptr;
	Chunk &chunk = m_chunks[getChunkIndex(x, y, z)];
	if (!chunk.isInitialized())
	{
		chunk.init(this, Vec3<int>(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE));
		addChunkToGenerate(&chunk);
	}
	return &chunk;
}

int World::getChunkIndex(const int &x, const int &y, const int &z) const
{
	return z * m_size * m_height + y * m_height + x;
}

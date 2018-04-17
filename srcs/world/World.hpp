//
// Created by Marc on 11/04/2018.
//

#pragma once

#include <map>
#include <deque>
#include <vector>
#include <thread>
#include "graphics/IRendereable.hpp"
#include "world/chunks/Chunk.hpp"

class Chunk;

class World : public IRenderable
{
private:
	std::vector<Chunk *>			m_renderedChunks;
	std::deque<Chunk *>				m_chunksToGenerate;
	std::thread 					m_chunkGenerationThread;
	Chunk							*m_chunks;
	int								m_size;
	int								m_height;

public:
	World(int size);
	virtual ~World();

	void update();
	void render(const Shader &shader);

	void generateChunk(const int &x, const int &y, const int &z);
	void generateChunks();

	void addChunkToGenerate(Chunk *chunk);

	int getChunkIndex(const int &x, const int &y, const int &z) const;
	Chunk *getChunk(const int &x, const int &y, const int &z);
	ABlock &getBlock(const int &x, const int &y, const int &z);
};

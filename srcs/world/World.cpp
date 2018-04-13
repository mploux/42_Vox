//
// Created by Marc on 11/04/2018.
//

#include "World.hpp"

World::World()
{
	m_chunks = new Chunk(*this, Vec3<int>(0, 0, 0));
	m_chunks->generateBlocks();
	m_chunks->generateRenderData();
}

World::~World()
{
	delete m_chunks;
}

void World::update()
{

}

void World::render(const Shader &shader)
{
	m_chunks->render(shader);
}

Block *World::getBlock(const int &x, const int &y, const int &z)
{
	return m_chunks->getBlock(x, y, z);
}
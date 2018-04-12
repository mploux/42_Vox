//
// Created by Marc on 11/04/2018.
//

#include "World.hpp"

World::World()
{
	m_chunks = new Chunk(*this);
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

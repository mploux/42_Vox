//
// Created by Marc on 11/04/2018.
//

#pragma once

#include "graphics/IRendereable.hpp"
#include "world/blocks/ABlock.hpp"
#include "world/World.hpp"
#include "ChunkRenderer.hpp"

#define CHUNK_SIZE 24

class World;

class Chunk : public IRenderable
{
private:
	Vec3<int>			m_pos;
	World				*m_world;
	ABlock				*m_blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	bool				m_initalized;
	bool				m_generated;
	bool				m_rendered;
	int					m_renderSize;

	ChunkRenderer		m_renderer;

	char				m_topStatus;
	char				m_bottomStatus;
	char				m_leftStatus;
	char				m_rightStatus;
	char				m_frontStatus;
	char				m_backStatus;

	bool				m_visible;

public:
	Chunk();
	virtual ~Chunk();

	void init(World *world, const Vec3<int> &pos);

	void generateBlocks();
	void generateFirstChunk();

	void generateRenderData();
	void update();
	void updateCulling();
	void render(const Shader &shader);

	bool isInViewFrustum(const Mat4<float> &projection);

	int getBlockIndex(const int &x, const int &y, const int &z) const;

	unsigned char getBlockVisibleFaces(const int &x, const int &y, const int &z) const;
	ABlock &getBlock(const int &x, const int &y, const int &z) const;

	const Vec3<int> &getPosition() const;


	bool isReadyToGenerate() const;
	bool isReadyToRender() const;

	bool isInitialized() const;
	bool isGenerated() const;
	bool isRendered() const;

	bool isVisible() const;

	char getTopStatus() const;
	char getBottomStatus() const;
	char getLeftStatus() const;
	char getRightStatus() const;
	char getFrontStatus() const;
	char getBackStatus() const;
};

//
// Created by Marc on 11/04/2018.
//

#include <iostream>
#include "Block.hpp"

Block::Block(const unsigned char &texture)
	: Block(texture, texture, texture, texture, texture, texture)
{}

Block::Block(const unsigned char &top, const unsigned char &bottom,
			   const unsigned char &left, const unsigned char &right,
			   const unsigned char &front, const unsigned char &back)
{
	m_texture[0] = top;
	m_texture[1] = bottom;
	m_texture[2] = left;
	m_texture[3] = right;
	m_texture[4] = front;
	m_texture[5] = back;

	m_type = -1;
	m_solid = false;
	m_opaque = false;
}

Block::~Block()
{}

char Block::getType()
{
	return m_type;
}

bool Block::isSolid()
{
	return m_solid;
}

bool Block::isOpaque()
{
	return m_opaque;
}

bool Block::isRendered()
{
	if (m_type == -1)
		return false;
	return m_opaque;
}

const unsigned char *Block::getTextureData() const
{
	return m_texture;
}

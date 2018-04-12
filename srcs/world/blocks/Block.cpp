//
// Created by Marc on 11/04/2018.
//

#include "Block.hpp"

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
}

Block::~Block()
{}

unsigned char Block::getType()
{
	return -1;
}

bool Block::isSolid()
{
	return false;
}

const unsigned char *Block::getTextureData() const
{
	return m_texture;
}

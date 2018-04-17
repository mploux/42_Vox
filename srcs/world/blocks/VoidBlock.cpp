//
// Created by Marc on 15/04/2018.
//

#include "VoidBlock.hpp"

VoidBlock::VoidBlock()
		: ABlock(0, 0, 0, 0, 0, 0)
{
	m_type = -1;
	m_solid = false;
	m_opaque = false;
}

VoidBlock::~VoidBlock()
{
}
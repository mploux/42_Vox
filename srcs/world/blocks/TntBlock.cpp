//
// Created by Marc on 14/04/2018.
//

#include "TntBlock.hpp"

TntBlock::TntBlock()
	: Block(9, 10, 8, 8, 8, 8)
{
	m_type = 8;
	m_solid = true;
}

TntBlock::~TntBlock() {}

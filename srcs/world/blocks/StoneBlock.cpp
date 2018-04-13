//
// Created by Marc on 11/04/2018.
//

#include "StoneBlock.hpp"

StoneBlock::StoneBlock()
	: Block(1, 2, 3, 4, 5, 6)
{
}

StoneBlock::~StoneBlock() {}

unsigned char StoneBlock::getType()
{
	return 1;
}

bool StoneBlock::isSolid()
{
	return true;
}

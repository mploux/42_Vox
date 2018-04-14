//
// Created by Marc on 14/04/2018.
//

#include "TntBlock.hpp"

TntBlock::TntBlock()
	: Block(9, 10, 8, 8, 8, 8)
{
}

TntBlock::~TntBlock() {}

unsigned char TntBlock::getType()
{
	return 8;
}

bool TntBlock::isSolid()
{
	return true;
}

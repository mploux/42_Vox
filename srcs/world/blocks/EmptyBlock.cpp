//
// Created by Marc on 11/04/2018.
//

#include "EmptyBlock.hpp"

EmptyBlock::EmptyBlock()
	: Block(0, 0, 0, 0, 0, 0)
{

}

EmptyBlock::~EmptyBlock() {}

unsigned char EmptyBlock::getType()
{
	return 0;
}

bool EmptyBlock::isSolid()
{
	return false;
}

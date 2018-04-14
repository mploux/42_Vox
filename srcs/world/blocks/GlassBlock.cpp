//
// Created by Marc on 14/04/2018.
//

#include "GlassBlock.hpp"

GlassBlock::GlassBlock()
		: Block(16 * 3 + 1)
{
}

GlassBlock::~GlassBlock() {}

unsigned char GlassBlock::getType()
{
	return 16 * 3 + 1;
}

bool GlassBlock::isSolid()
{
	return true;
}

bool GlassBlock::isOpaque()
{
	return false;
}
//
// Created by Marc on 14/04/2018.
//

#pragma once


#include "Block.hpp"

class GlassBlock : public Block
{
public:
	explicit GlassBlock();
	virtual ~GlassBlock();

	unsigned char getType();
	bool isSolid();
	bool isOpaque();
};


//
// Created by Marc on 11/04/2018.
//

#pragma once

#include "Block.hpp"

class StoneBlock : public Block
{
public:
	explicit StoneBlock();
	virtual ~StoneBlock();

	unsigned char getType();
	bool isSolid();
};


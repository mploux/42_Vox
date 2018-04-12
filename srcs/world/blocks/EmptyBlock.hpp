//
// Created by Marc on 11/04/2018.
//

#pragma once

#include "Block.hpp"

class EmptyBlock : public Block
{
public:
	explicit EmptyBlock();
	virtual ~EmptyBlock();

	unsigned char getType();
	bool isSolid();
};


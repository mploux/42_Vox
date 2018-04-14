//
// Created by Marc on 11/04/2018.
//

#pragma once

#include "EmptyBlock.hpp"
#include "StoneBlock.hpp"
#include "TntBlock.hpp"
#include "GlassBlock.hpp"

namespace blocks
{
	static Block 		VOID 	= Block(0, 0, 0, 0, 0, 0);
	static EmptyBlock 	EMPTY 	= EmptyBlock();
	static StoneBlock 	STONE 	= StoneBlock();
	static TntBlock 	TNT 	= TntBlock();
	static GlassBlock 	GLASS 	= GlassBlock();
};


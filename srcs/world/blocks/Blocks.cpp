//
// Created by mploux on 14/04/18.
//

#include "Blocks.hpp"
#include "TntBlock.hpp"
#include "StoneBlock.hpp"
#include "EmptyBlock.hpp"
#include "VoidBlock.hpp"
#include "GlassBlock.hpp"

Blocks::Blocks()
{
	m_blocks["void"] = new VoidBlock();
	m_blocks["empty"] = new EmptyBlock();
	m_blocks["stone"] = new StoneBlock();
	m_blocks["tnt"] = new TntBlock();
	m_blocks["glass"] = new GlassBlock();
}

Blocks::~Blocks()
{
	m_blocks.clear();
}
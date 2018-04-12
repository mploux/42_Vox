//
// Created by Marc on 11/04/2018.
//

#pragma once

class Block
{
protected:
	unsigned char m_texture[6];

public:
	explicit Block(const unsigned char &top, const unsigned char &bottom,
		   const unsigned char &left, const unsigned char &right,
		   const unsigned char &front, const unsigned char &back);
	virtual ~Block();

	unsigned char getType();
	bool isSolid();
	const unsigned char *getTextureData() const;
};


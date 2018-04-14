//
// Created by Marc on 11/04/2018.
//

#pragma once

class Block
{
protected:
	unsigned char	m_texture[6];
	char			m_type;
	bool			m_solid;
	bool			m_opaque;

public:
	explicit Block(const unsigned char &texture);
	explicit Block(const unsigned char &top, const unsigned char &bottom,
		   const unsigned char &left, const unsigned char &right,
		   const unsigned char &front, const unsigned char &back);
	virtual ~Block();

	char getType();
	bool isSolid();
	bool isOpaque();
	bool isRendered();
	const unsigned char *getTextureData() const;
};


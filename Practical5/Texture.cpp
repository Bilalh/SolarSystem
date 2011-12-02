//
//  Texture.cpp
//  CS4102-CG-P5
//
//  Created by Bilal Syed Hussain on 01/12/2011.
//  Copyright 2011 St. Andrews KY16 9XW. All rights reserved.
//

#include "Texture.h"
#include "libjpeg.h"


Texture::Texture(char *filename, int width, int height,  bool wrap)
	:filename(filename), width(width), height(height), wrap(wrap)
{}

void Texture::create_texture()
{
	unsigned char* data = read_jpeg_file(filename);
	texture_id =loadTexture(1,data, width, height, wrap);
	free(data);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

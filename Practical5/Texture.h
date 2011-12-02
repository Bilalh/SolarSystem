//
//  Texture.h
//  CS4102-CG-P5
//
//  Created by Bilal Syed Hussain on 01/12/2011.
//  Copyright 2011 St. Andrews KY16 9XW. All rights reserved.
//
 
#ifndef TEXTURE_HH
#define TEXTURE_HH

#include "Glut.h"

class Texture {
	char *filename;
	int width, height;
	bool wrap;
	
	static GLuint texture_counter;
	
public:
	GLuint texture_id;
	Texture(char *filename, int width, int height,  bool wrap=true);
	void bind() const;
};



#endif
//
//  Texture.h
//  CS4102-CG-P5
 
#ifndef TEXTURE_HH
#define TEXTURE_HH

#include "Glut.h"

class Texture {
	char *filename;
	int width, height;
	bool wrap;
		
public:
	GLuint texture_id;
	Texture(char *filename, int width, int height,  bool wrap=true);
	void create_texture();
	void bind() const;
};



#endif
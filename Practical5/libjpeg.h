//
//  libjpeg.h
//  CS4102-CG-P5
//

#ifndef LIBJPEG_HH
#define LIBJPEG_HH

#include "Glut.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#include <jpeglib.h>

// Read a jpeg from file and return the data in a mallo'ed buffer
unsigned char *load_jpeg(const char *filename);

// Loads a texture from data load load_jpeg
GLuint load_texture(unsigned char * data, int width, int height, int wrap );


#ifdef __cplusplus
}
#endif
#endif
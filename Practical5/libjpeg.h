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

unsigned char *read_jpeg_file( char *filename );

GLuint loadTexture( int texture_id, unsigned char * data, int width, int height, int wrap );


#ifdef __cplusplus
}
#endif
#endif
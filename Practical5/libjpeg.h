//
//  libjpeg.h
//  CS4102-CG-P5
//

#ifndef LIBJPEG_HH
#define LIBJPEG_HH

#ifdef __cplusplus
extern "C" {
#endif
#include <jpeglib.h>


int read_jpeg_file( char *filename );
int write_jpeg_file( char *filename );

#ifdef __cplusplus
}
#endif
#endif
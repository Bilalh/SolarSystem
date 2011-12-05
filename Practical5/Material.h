//
//  Material.h
//  CS4102-CG-P4


#ifndef MATERIAL_HEADER__
#define MATERIAL_HEADER__

#include <stddef.h>

#include "Glut.h"
#include "Texture.h"

// Classes that store data on Materials. Inculdes methods to return predefined Materials 

struct MaterialList;

struct Material{
	const GLfloat ambient[4];
	const GLfloat diffuse[4];
	const GLfloat specular[4];
	const GLfloat shininess;
	
	const static Material* yellow();
	const static Material* grey();
	const static Material* red();
	const static Material* green();

	const static Material* white();
	const static Material* orange();
	const static Material* turquoise();
	const static Material* gold();
	const static Material* blue();

	static MaterialList* all_materials(int index=0);
	
	void draw() const;
	void draw_with_emission(const GLfloat* emission) const;
};

class MaterialList{
	const Material* materials;
	const GLfloat (*colours)[3];
	const Texture* textures;
	
	size_t length;
	size_t index;
	
	public:
	const Texture*  current_texture() const; 
	const Material* current_materials() const;
	const GLfloat*  current_colour() const;
	void next();
	
	MaterialList(const Material* materials, const Texture*  textures, const GLfloat (*colours)[3],   size_t length, size_t index=0);
};

struct Light{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat postion[4];
	GLenum  light_number;
	const static Light* white();

	void draw() const;
};

struct Colour
{		
	const static GLfloat* black();
	const static GLfloat* green();
	const static GLfloat* white();
	const static GLfloat* blue();
	const static GLfloat* red();
	const static GLfloat* orange();
	const static GLfloat* yellow();
	const static GLfloat* grey();
};

#endif
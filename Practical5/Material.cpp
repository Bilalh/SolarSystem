//
//  Material.cpp
//  Practical4


#include "Material.h"

static const GLfloat no_emission[] = {0.0F, 0.0F, 0.0F, 1.0F};

void Material::draw() const
{
	draw_with_emission(no_emission);
}

void Material::draw_with_emission(const GLfloat* emission) const
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);	
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);	
}

const Material materials[] = {
	{	// Sun 
		{ 0.9f, 0.6f, 0.1f, 1.f },
		{ 0.9f, 0.6f, 0.1f, 1.f },
		{ 1.f,  1.f,  1.f,  1.f },
		50.f,
	},
	{	// Grey 
		{0.2F, 0.2F, 0.2F, 1.0F},
		{0.8F, 0.8F, 0.8F, 1.0F},
		{0.8F, 0.8F, 0.8F, 1.0F},
		50.0F
	},
	{	// White
		{0.2F,  0.0F,  0.0F,  1.0f},
		{0.902f,0.902f,0.902f,1.0f},
		{0.8F,  0.6F,  0.6F,  1.0f},
		50.0F
	},
	{	// Green
		{0.3f, 0.3f, 0.1f, 1.f},
		{0.6f, 0.6f, 0.5f, 1.f},
		{0.9f, 0.9f, 0.7f, 1.f},
		60.f
	},
	{	// Red
		{0.2F, 0.0F, 0.0F, 1.0f},
		{0.8F, 0.0F, 0.0F, 1.0f},
		{0.8F, 0.6F, 0.6F, 1.0f},
		32.0F
	},
	{   // Orange
		{ .3f, .1f, .1f, 1.f },
		{ .7f, .3f, .1f, 1.f },
		{ .7f, .2f, .2f, 1.f },
		50.f
	},
	{	// Gold
		{0.24725f,  0.1995f,   0.0745f,   1.f},
		{0.75164f,  0.60648f,  0.22648f,  1.f},
		{0.628281f, 0.555802f, 0.366065f, 1.f},
		51.2f
	},
	{	// turquoise
		{0.1f,      0.18725f, 0.1745f,   0.8f},
		{0.396f,    0.74151f, 0.69102f,  0.8f},
		{0.297254f, 0.30829f, 0.306678f, 0.8f},
		32.f
	},
	{	// Blue
		{0.1f, 0.2f, 0.5f, 1.f},
		{0.2f, 0.4f, 0.6f, 1.f},
		{0.2f, 0.3f, 0.5f, 1.f},
		32.f
	},
};

const Material* Material::white() 
{
	return &materials[2];
}
const Material* Material::grey()  
{
	return &materials[1];
}
const Material* Material::red()   
{
	return &materials[4];
}
const Material* Material::yellow()
{
	return &materials[0];
}
const Material* Material::green() 
{
	return &materials[3];
}
const Material* Material::orange()
{
	return &materials[5];
}
const Material* Material::turquoise()  
{
	return &materials[7];
}
const Material* Material::blue()  
{
	return &materials[8];
}
const Material* Material::gold()
{
	return &materials[6];
}

void Light::draw() const
{
	glLightfv(light_number, GL_AMBIENT, ambient);
	glLightfv(light_number, GL_DIFFUSE, diffuse);
	glLightfv(light_number, GL_SPECULAR,specular);
	glLightfv(GL_LIGHT0, GL_POSITION,  postion);
}

const Light lights[] = {
	{	// White
		{0.0F, 0.0F, 0.0F, 1.0F},
		{1.0F, 1.0F, 1.0F, 1.0F},
		{1.0F, 1.0F, 1.0F, 1.0F}
	}
};

static const GLfloat colours[][3] ={
	{0.769f,0.757f,0.576f},  // Yellow
	{0.800f,0.800f,0.800f},  // Grey
	{1.000f,1.000f,0.937f},  // White
	{0.502f,1.000f,0.000f},  // Green
	{0.973f,0.286f,0.000f},  // Red
	{0.769f,0.443f,0.278f},  // Orange
	{0.259f,0.259f,0.259f},  // Black
	{0.408f,0.655f,0.776f},  // Blue
	{0.408f,0.655f,0.776f},  // Blue
};

const GLfloat* Colour::black()
{
	return colours[6];
}

const GLfloat* Colour::green()
{
	return colours[3];
}

const GLfloat* Colour::white()
{
	return colours[2];
}

const GLfloat* Colour::blue()
{
	return colours[7];
}

const GLfloat* Colour::red()
{
	return colours[4];
}

const GLfloat* Colour::orange()
{
	return colours[5];
}

const GLfloat* Colour::yellow()
{
	return colours[6];
}

const GLfloat* Colour::grey()
{
	return colours[2];
}

MaterialList::MaterialList(const Material* materials, const Texture*  textures, const GLfloat (*colours)[3],   size_t length, size_t index):
materials(materials), textures(textures), length(length),index(index),colours(colours)
{}

const Material* MaterialList::current_materials() const
{
	return &materials[index];
}

const GLfloat* MaterialList::current_colour() const
{
	return colours[index];
}


void MaterialList::next()
{
	index = (index + 1) % length;
}

static Texture textures[] ={
	Texture("images/sunmap.jpg"     , 1000, 500,true),
	Texture("images/mercurymap.jpg" , 1000, 500,true),
	Texture("images/venusmap.jpg"   , 1000, 500,true),
	Texture("images/earthmap.jpg"   , 1000, 500,true),
	Texture("images/mars.jpg"       , 1000, 500,true),
	Texture("images/jupitermap.jpg" , 1000, 500,true),
	Texture("images/saturnmap.jpg"  , 1000, 500,true),
	Texture("images/uranusmap.jpg"  , 1000, 500,true),
	Texture("images/neptunemap.jpg" , 1000, 500,true),
	//	Texture("images/moonmap.jpg"    , 1000, 500,true),
};

const Texture* MaterialList::current_texture() const
{
	return &textures[index];
}

static bool textures_initialised = false;

MaterialList* Material::all_materials(int index)
{
	if (!textures_initialised){
		for (int i =0; i < sizeof(textures)/sizeof(Texture); ++i) {
			textures[i].create_texture();
		}
		textures_initialised=true;
	}
	
	return new MaterialList(materials,textures, colours,sizeof(materials)/sizeof(Material),index);
}

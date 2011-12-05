//
//  Planet.h
//  CS4102-CG-P4


#ifndef PLANET_H
#define PLANET_H

#include <List>

#include "Material.h"

// Classes that represent objects in space, inculdes functions to draw the objects.

class Drawable{
public:
	static void init();
	virtual void draw() const = 0;
	static bool textured;
};

class Body: public Drawable {
protected:
	MaterialList* materials;
	const float radius;
	float offset;
	bool  orbit;
	float angle;
	float speed;
	virtual void draw_other() const;
	virtual void draw_material() const;	
	float spin_angle;
	
public:	
	static float speed_multiplier;
	float x;
	float z;
	
	Body(MaterialList* materials, float radius, float offset, float speed, float angle=0);
	
	virtual void draw() const;
	virtual void update();
	
	void draw_orbit() const;
	void toggle_draw_orbit();
	
	void next_material();
};

class Ring;

class Planet: public Body{
	std::list<Drawable*> drawables; // for storing rings
	std::list<Body*> moons;
	
protected:
	virtual void draw_other() const;
	
public:
	Planet(MaterialList* materials, float radius, float offset, float speed, float angle=0);
	
	void add_moon(Body *moon);
	void add_drawables(Drawable *d);
	
	virtual void update();
};


class Star: public Body{
	const GLfloat* emission;
	bool show_emission;
protected:
	virtual void draw_material() const;	
public:
	Star(MaterialList* materials, const GLfloat* emission, float radius, bool show_emission=false, float offset=0, float speed=0, float angle=0);
	void toggle_emission();
};

// For drawing rings around a planet.
class Ring : public Drawable{
	const float inner_ring;
	const float outer_ring;
	const float rotate_angle;
	Texture *texture;
	
public:
	Ring(Texture *texture, float inner_ring, float outer_ring, float rotate_angle=0);
	virtual void draw() const;
};

#endif
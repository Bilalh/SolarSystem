//
//  SolarSystem.h
//  CS4102-CG-P5

#ifndef SOLARSYSTEM_HH
#define SOLARSYSTEM_HH

#include "Planet.h"
#include "Location.h"

#include <vector>

// A solar system has a set of plaents which orbit a sun.
class SolarSystem {
	
	// The objects in space
	Star* sun;
	std::vector<Planet*> planets;
	
public:
	SolarSystem(std::vector<Planet*> planets, Star *sun);
	
	void draw(GLenum render_mode, Location &current);
	
	int selected_planet; // The currently select planet. 
	bool selected;       // True if the planets are moving.
	bool moving;         // True if planets are moving.
	
	void selected_planet_next_material();
	
	void toggle_draw_orbits();
	void toggle_sun_emission();
};
	
#endif
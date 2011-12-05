//
//  SolarSystem.cpp
//  CS4102-CG-P5
//

#include "SolarSystem.h"

#include "Glut.h"
#include "Location.h"

SolarSystem::SolarSystem(std::vector<Planet*> planets, Star *sun):
	planets(planets), selected_planet(0), moving(false), selected(false), sun(sun)
{
	Drawable::init();
}

void SolarSystem::draw(GLenum render_mode, Location &current)
{	
	if (selected){
		current.eyeX = planets[selected_planet]->x;
		current.eyeZ = -planets[selected_planet]->z;
		current.eyeY = selected_planet > 3 ? 0.2 : 0.15;
	}
	
	gluLookAt(current.eyeX,    current.eyeY,    current.eyeZ, 
			  current.centreX, current.centreY, current.centreZ, 
			  current.upX,     current.upY,     current.upZ);
	
	
	// Draws the objects 
	sun->draw();
	
	int index = 0;
	for(std::vector<Planet*>::iterator it = planets.begin(); it != planets.end(); ++it,++index){
		if (render_mode == GL_RENDER){
			if (moving) (*it)->update(); // Update the postion of the planet
		}else{
			glLoadName(index);           // Give the planet a name if we are picking	
		}
		(*it)->draw();
	}
}

void SolarSystem::selected_planet_next_material()
{
	planets[selected_planet]->next_material();	
}

void SolarSystem::toggle_draw_orbits()
{
	for(std::vector<Planet*>::iterator it = planets.begin(); it != planets.end(); ++it){
		(*it)->toggle_draw_orbit();
	}
}

void SolarSystem::toggle_sun_emission()
{
	sun->toggle_emission();
}
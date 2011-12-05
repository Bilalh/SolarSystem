//
//  Planet.cpp
//  CS4102-CG-P4

#include <math.h>
#include <list>

#include "Planet.h"
#include "Material.h"
#include "Glut.h"

// For controlling the speed of the bodies 
float Body::speed_multiplier = 1;
// For drawing spheres and rings
static GLUquadricObj *sphere = NULL;
bool Drawable::textured = true;


void Drawable::init(){
	if (sphere != NULL) return;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricTexture(sphere,GL_TRUE);
}

// constructors
Body::Body(MaterialList* materials, float radius, float offset, float speed, float angle):
	materials(materials), radius(radius), offset(offset), speed(speed), angle(angle), orbit(false), spin_angle(0)
{
	x = cosf((angle) /180.f * (float)M_PI ) * (radius+offset +0.05f);
	z = sinf((angle) /180.f * (float)M_PI ) * (radius+offset+ 0.05f);

}

Planet::Planet(MaterialList* materials, float radius, float offset, float speed, float angle):
	Body(materials,radius,offset,speed,angle)
{
	moons     = std::list<Body*>();
	drawables = std::list<Drawable*>();
}

Star::Star(MaterialList* materials, const GLfloat *emission, float radius,bool show_emission, float offset, float speed, float angle):
	Body(materials,radius,offset,speed,angle),emission(emission), show_emission(show_emission)
{}

// Drawing functions
void Body::draw() const
{
	glPushMatrix();
	if (orbit) draw_orbit();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(offset, 0, 0);
		
	// Make planet spin 
	glPushMatrix();
	glRotatef( spin_angle, 0.0f, 1.0f, 0.0f );
	glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
	if (textured){
		materials->current_texture()->bind();
		gluSphere(sphere, radius, 30, 30);
	}else{
//		glColor3fv(materials->current_colour());
		draw_material();
		glutSolidSphere(radius, 60, 60);
	}
	glPopMatrix();
	draw_other();
	glPopMatrix();
}

void Body::draw_material() const
{
	materials->current_materials()->draw();
}

void Star::draw_material() const
{
	if (show_emission){
		materials->current_materials()->draw_with_emission(emission);
	}else{
		materials->current_materials()->draw();
	}
		
}

void Body::draw_other() const {}

// Draws teh rings and moons
void Planet::draw_other() const
{
	for(std::list<Body*>::const_iterator it = moons.begin(); it != moons.end(); ++it){
		(*it)->draw();
	}
	
	for(std::list<Drawable*>::const_iterator it = drawables.begin(); it != drawables.end(); ++it){
		(*it)->draw();
	}
}


static const GLfloat orbit_emission[] = {0.0F, 0.4F, 0.6F, 0.3F};

void Body::draw_orbit() const
{

	if (!textured){
		glColor3fv(Colour::blue());
		Material::white()->draw_with_emission(orbit_emission);		
	}
	glBegin(GL_LINE_LOOP);
	int slices = 40;
	for (int i = 0; i < slices; ++i) {
		const float value = 2 * (float)M_PI/(float)slices * (float)i;
		glVertex3f(offset * sinf(value), 0.0f, offset * cosf(value));
	}
	glEnd();
}

// State changing methods

void Planet::add_moon(Body *moon)
{
	moons.push_back(moon);
}

void Planet::add_drawables(Drawable *d)
{
	drawables.push_back(d);	
}

void Planet::update()
{
	Body::update();
	for(std::list<Body*>::iterator it = moons.begin(); it != moons.end(); ++it){
		(*it)->update();
	}
}

void Body::update()
{
	angle+=speed * speed_multiplier;
	spin_angle+=4.f;
	x = cosf((angle) /180.f * (float)M_PI ) * (radius+offset +0.05f);
	z = sinf((angle) /180.f * (float)M_PI ) * (radius+offset+ 0.05f);
}

void Body::next_material()
{
	materials->next();
}

void Body::toggle_draw_orbit()
{
	orbit = !orbit;
}

void Star::toggle_emission()
{
	show_emission = !show_emission;
	printf("%d\n", show_emission);
}

Ring::Ring(Texture* texture, float inner_ring, float outer_ring, float rotate_angle):
	inner_ring(inner_ring), outer_ring(outer_ring), rotate_angle(rotate_angle),texture(texture)
{}


void Ring::draw() const
{
	glPushMatrix();
	glRotatef(rotate_angle, 1.0f, 0.0f, 0.0f);
	if (textured) texture->bind();
	gluDisk(sphere, inner_ring, outer_ring, 16, 20);
	glPopMatrix();
}

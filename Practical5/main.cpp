//
//  main.cpp
//  CS4102-CG-P4

// C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <time.h>
#include <math.h>

#include "Glut.h"
#include "libjpeg.h"

// C++
#include <iostream>
#include <vector>

#include "Planet.h"
#include "Material.h"
#include "Location.h"
#include "Texture.h"


// The objects in space
static Star* sun;
static std::vector<Planet*> planets;

static int selected_planet = 0; // The currently select planet. 
static bool moving = false;     // True if planets are moving.
static bool lighting = true;    // True if lighting is turned on.
static bool selected =false;    // True if the planets are moving.

static float ratio = 1;         // The current aspect radio

GLenum render_mode = GL_RENDER; // Which mode we are in (used for picking).


// Stores the predefined loctions.
static const int LOCATION_SIZE = 4;
static int location_index = 0;
static Location locations[LOCATION_SIZE];

// current location
static Location current;

// Frames per a second
static const int refresh_rate = 25;

// Light settings
static Light lights[] = 
{
	{
		{0.6F, 0.6F, 0.6F, 0.6F}, // ambient
		{1.0F, 1.0F, 1.0F, 1.0F}, // diffuse
		{1.0F, 1.0F, 1.0F, 1.0F}, // specular
		{ .0f, 1.f, .0f, 1.f },   // light number
		GL_LIGHT0
	},
	{
		{0.0F, 0.0F, 0.0F, 1.0F}, // ambient
		{1.0F, 1.0F, 1.0F, 1.0F}, // diffuse
		{1.0F, 1.0F, 1.0F, 1.0F}, // specular
		{ .0f, 1.f, .0f, 1.f },   // light number
		GL_LIGHT0
	}
};
static const int LIGHTS_SIZE = sizeof(lights)/sizeof(Light);
static int lights_index = 0;

GLUquadricObj *sphere;

void init_planets(void);
void init_locations(void);


void init_planets(void){
	
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricTexture(sphere,GL_TRUE);
	

	// All the parameters are in relation to earth.
	const float earth_distance = 0.9f;
	const float earth_radius   = 0.06f;
	const float earth_speed    = 1.0f;
	
	Body *moon = new Body(Material::all_materials(0), 0.025f, 0.1f, 1.f);
	GLfloat *sun_emission = new GLfloat[4];
	sun_emission[0] = .7f; 
	sun_emission[1] = .4f; 
	sun_emission[2] = .2f; 
	sun_emission[3] = 1.f; 
	sun = new Star(Material::all_materials(0), sun_emission, 0.2f);
	
	planets.push_back(new Planet(Material::all_materials(1), 0.5f*earth_radius,  0.4f*earth_distance, 2.0f*earth_speed));
	planets.push_back(new Planet(Material::all_materials(2), 0.9f*earth_radius,  0.7f*earth_distance, 1.5f*earth_speed));
	planets.push_back(new Planet(Material::all_materials(3),      earth_radius,       earth_distance,      earth_speed, 0, moon));
	planets.push_back(new Planet(Material::all_materials(4), 0.7f*earth_radius,  1.2f*earth_distance, 0.7f*earth_speed));

	planets.push_back(new Planet(Material::all_materials(5), 2.5f*earth_radius,  1.5f*earth_distance, 0.4f*earth_speed));
	Planet *saturn =  new Planet(Material::all_materials(6), 2.0f*earth_radius,  1.9f*earth_distance, 0.3f*earth_speed);
	
	Texture *t = new Texture("images/saturnringcolor.jpg", 915, 64);
	t->create_texture();
	
	saturn->set_ring( new Ring(t, 2.3f*earth_radius, 2.7f*earth_radius,-45));	                                                 
	planets.push_back(saturn);                                                                       
                                                                                                     
	Planet *uranus = new Planet(Material::all_materials(7),  1.7f*earth_radius,  2.3f*earth_distance, 0.2f*earth_speed);
	uranus->set_ring(new Ring(t,2.1f*earth_radius, 2.4f*earth_radius,0));                                                       
	planets.push_back(uranus);                                                                        
                                                                                                      
	planets.push_back(new Planet(Material::all_materials(8), 1.5f*earth_radius,  2.6f*earth_distance, 0.1f*earth_speed));
}

static Location old;

void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//	earth->bind();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
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
			glLoadName(index);          // Give the planet a name if we are picking	
		}
		(*it)->draw();
	}
	
	if (render_mode == GL_RENDER){
		glutSwapBuffers();	
	}
	
}


void idle(void)
{
	int sleep_amount = refresh_rate * 1000;
	usleep(sleep_amount);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}


void reshape (int w, int h)
{	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	ratio = (float) w / (float) h;
	gluPerspective( 60, ratio, 0.1, 1000);
}


void process_hits(int button,GLint hits, GLuint buffer[])
{
	GLuint ii, jj, *ptr;
 	
	printf ("Total hits = %d\n", hits);
	ptr = (GLuint *) buffer;
	for (unsigned i = 0; i < hits; i++) { 
		GLuint names = *ptr;
		printf (" number of names for hit = %d\n", names);
		ptr++;
		printf("  z1 is %g;", (float) *ptr/0x7fffffff); ptr++;
		printf(" z2 is %g\n", (float) *ptr/0x7fffffff); ptr++;
		printf ("   names are ");
		for (unsigned j = 0; j < names; j++) { // for each name 
			printf ("%d ", *ptr);
			if (j == 0)  // set row and column 
				ii = *ptr;
			else if (j == 1)
				jj = *ptr;
			ptr++;
		}
		printf ("\n");
		
		selected_planet = ii;
		if(button == GLUT_RIGHT_BUTTON){
			planets[selected_planet]->next_material();
		}
	}
	glutPostRedisplay();
}

#define BUFSIZE 128
void mouse(int button, int state, int x, int y)
{
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];
	
	if (state != GLUT_DOWN) return;
	
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);
	
	glInitNames();
	glPushName(0);
	
	glMatrixMode(GL_PROJECTION) ;
	glPushMatrix();
	glLoadIdentity();
	
	// create a 5x5 pixel picking region
	gluPickMatrix(x, (viewport[3] - y), 5.0, 5.0, viewport);
	gluPerspective(60, ratio, 0.1, 1000);
	render_mode = GL_SELECT;
	
	display();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	render_mode=  GL_RENDER;
	hits = glRenderMode(GL_RENDER);
	process_hits(button, hits, selectBuf);
	glutPostRedisplay();
	
}

// Handle keyboard input
void keyboard(unsigned char c, int x, int y)
{	
	switch (c){
			
		case 'e': // Turns the Sun's emissive colour turned on or off.
		case 'E':
			sun->toggle_emission();
			break;
			
		case 'r': // Shows/hides each planet's orbit.
		case 'R':
			for(std::vector<Planet*>::iterator it = planets.begin(); it != planets.end(); ++it){
				(*it)->toggle_draw_orbit();
			}
			break;
			
		case ' ': // Toggles the planets moving around sun.
			moving = !moving;
			printf("moving:%d\n",moving);
			break;
			
		case 'v': // Goes to the next location.
		case 'V': 
			selected = false;
			location_index = (location_index +1) % LOCATION_SIZE;
			printf("location index:%d\n", location_index);
			current = locations[location_index];
			break;
			
		case 'l': // Changes the light configuration.
		case 'L':
			if (lighting &&  (lights_index +1) == LIGHTS_SIZE){
				lighting = false;
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				printf("lighting off\n");
			}else{
				lighting = true;
				lights_index = (lights_index +1) % LIGHTS_SIZE;
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				lights[lights_index].draw(); 
				printf("lighting index:%d\n", lights_index);
			}
			break;
			
		case 'a': // Attaches the camera  to the currently selected planet.
		case 'A': 
			selected = !selected;
			if (selected){
				old = current;
			}else{
				current = old;
			}
			printf("selected:%d\n",selected);
			break;
		
		case 'm': // Change selected planet's material. 
		case 'M':
			planets[selected_planet]->next_material();
			break;
		
		case '+': // Speeds up/slows down  the planets.
		case '=':
			Body::speed_multiplier *=1.5f;
			break;
		case '-': 
			Body::speed_multiplier /=1.5f;
			break;
			
			
		case 27:  // Exit 
			exit(0);
			break;
			
			// Controls the loctaion of the camera of the object with  w
			//                                                        s d f
		case 'f':
			current.eyeX -= 0.1;
			break;
		case 's':
			current.eyeX += 0.1;			
			break;
		case 'w':
			current.eyeZ += 0.1;
			break;
		case 'W':
		case '[':
			current.eyeY += 0.1;
			break;			
		case 'd': 
			current.eyeZ -= 0.1;
			break;		
		case 'D': 
		case ']':
			current.eyeY -= 0.1;
			break;
			
			// Controls the loctaion of `up' of the object with   u
			//                                                  h j k
		case 'k':
			current.upX -=0.1;
			break;
		case 'h':
			current.upX +=0.1;			
			break;
		case 'u':
			current.upZ += 1;
			break;
		case 'U':
			current.upY += 1;
			break;			
		case 'j': 
			current.upZ -= 1;
			break;		
		case 'J': 
			current.upY -= 1;
			break;
		
			
			// Prints the current location, used to easily make the fixed locations. 
		case 'p':
			printf("l->eyeX = %.2f;\n"
				   "l->eyeY = %.2f;\n"
				   "l->eyeZ = %.2f;\n\n"
				   
				   "l->centreX = %.2f;\n"
				   "l->centreY = %.2f;\n"
				   "l->centreZ = %.2f;\n\n"
				   
				   "l->upX = %.2f;\n"
				   "l->upY = %.2f;\n"
				   "l->upZ = %.2f;\n",
				   current.eyeX, current.eyeY, current.eyeZ,
				   current.centreX, current.centreY, current.centreZ,
				   current.upX, current.upY, current.upZ);
			break;
			
		default: // Return since we have not done anything.
			return;
	}
	glutPostRedisplay();
}

// Handles arrow keys
void special_keys(int key, int x, int y)
{	
	int mod = glutGetModifiers();
	
	// Change the `centre'.
	switch (key) 
	{
		case GLUT_KEY_RIGHT:
			current.centreX -=0.1;
			break;
			
		case GLUT_KEY_LEFT:
			current.centreX +=0.1;
			break;
			
		case GLUT_KEY_UP:
			if (mod == GLUT_ACTIVE_SHIFT) current.centreY += 0.1;
			else                          current.centreZ+= 0.1;
			break;
			
		case GLUT_KEY_DOWN: 
			if (mod == GLUT_ACTIVE_SHIFT) current.centreY -= 0.1;
			else                          current.centreZ -= 0.1;
			break;
			
		default:    // nothing changed so don't redisplay
			return; 
	}
	glutPostRedisplay();
}


void init_locations(void) 
{
	
	Location *l =  &locations[0];
	l->eyeX = 2;
	l->eyeY = 1;
	l->eyeZ = 2;
	
	l->centreX = 0;
	l->centreY = 0;
	l->centreZ = 0;
	
	l->upX = 0;
	l->upY = 1;
	l->upZ = 0;
	
	l =  &locations[1];
	l->eyeX = 0.00;
	l->eyeY = 1.00;
	l->eyeZ = -2.00;
	
	l->centreX = 0.00;
	l->centreY = 0.00;
	l->centreZ = 0.00;
	
	l->upX = 0.00;
	l->upY = 0.00;
	l->upZ = 1.00;
	
	l = &locations[2];
	l->eyeX = 0.00;
	l->eyeY = 4.10;
	l->eyeZ = 0.00;
	
	l->centreX = 0.00;
	l->centreY = -0.20;
	l->centreZ = 0.00;
	
	l->upX = 0.00;
	l->upY = 0.00;
	l->upZ = 1.00;
	
	l =  &locations[3];
	l->eyeX = 2.40;
	l->eyeY = 0.30;
	l->eyeZ = 2.10;
	
	l->centreX = 0.60;
	l->centreY = 0.30;
	l->centreZ = 0.50;
	
	l->upX = 0.00;
	l->upY = 1.00;
	l->upZ = 0.00;

	current = locations[0];
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Practical 4");
	
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keys);
	
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);	
	lights[0].draw();
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	
	
	glEnable(GL_TEXTURE_2D);
//	glDisable(GL_CULL_FACE);

	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	init_planets();
	init_locations();
	
	glutMainLoop();
}

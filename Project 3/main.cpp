// OpenGL/GLUT starter kit for Windows 7 and Visual Studio 2010
// Created spring, 2011
//
// This is a starting point for OpenGl applications.
// Add code to the "display" function below, or otherwise
// modify this file to get your desired results.
//
// For the first assignment, add this file to an empty Windows Console project
//		and then compile and run it as is.
// NOTE: You should also have glut.h,
// glut32.dll, and glut32.lib in the directory of your project.
// OR, see GlutDirectories.txt for a better place to put them.

#include <cmath>
#include <cstring>
#include <cstdlib>
#include <GLUT/glut.h>
#include <vector>
#include <math.h>

#include "circle.h"
#include "balls.h"


// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;

std::vector<Circle *>_circles;

double kNumCircles = 10;

double gX = 200;
double gY = 200;

double gXRange = 400;
double gYRange = 400;

double gDX = 4;
double gDY = 4;

double gDXRange = 2;
double gDYRange = 2;

double gRadius = 50;
double gRadiusRange = 0;

double GRAVITY = .5;
double AIR_FRICTION = 1.0;
double FRICTION = 1.0;

const double COLLISION_FRICTION = 1;

Balls *BALLS;

//
// Collision Detection
//
struct vectortype
{
	double x;
	double y;
};

void Collide(int p1, int p2, std::vector<Circle *>particles)
{
	vectortype en; // Center of Mass coordinate system, normal component
	vectortype et; // Center of Mass coordinate system, tangential component
	vectortype u[2]; // initial velocities of two particles
	vectortype um[2]; // initial velocities in Center of Mass coordinates
	double umt[2]; // initial velocities in Center of Mass coordinates, tangent component
	double umn[2]; // initial velocities in Center of Mass coordinates, normal component
	vectortype v[2]; // final velocities of two particles
	double m[2];	// mass of two particles
	double M; // mass of two particles together
	vectortype V; // velocity of two particles together
	double size;
	int i;

	double xdif=particles[p1]->getnextx() - particles[p2]->getnextx();
	double ydif=particles[p1]->getnexty() - particles[p2]->getnexty();

	// set Center of Mass coordinate system
	size=sqrt(xdif*xdif + ydif*ydif);
	xdif/=size; ydif/=size; // normalize
	en.x=xdif;
	en.y=ydif;
	et.x=ydif;
	et.y=-xdif;

	// set u values
	u[0].x=particles[p1]->getdx();
	u[0].y=particles[p1]->getdy();
	m[0]=particles[p1]->getradius()*particles[p1]->getradius();
	u[1].x=particles[p2]->getdx();
	u[1].y=particles[p2]->getdy();
	m[1]=particles[p2]->getradius()*particles[p2]->getradius();

	// set M and V
	M=m[0]+m[1];
	V.x=(u[0].x*m[0] + u[1].x*m[1])/M;
	V.y=(u[0].y*m[0] + u[1].y*m[1])/M;

	// set um values
	um[0].x=m[1]/M * (u[0].x-u[1].x);
	um[0].y=m[1]/M * (u[0].y-u[1].y);
	um[1].x=m[0]/M * (u[1].x-u[0].x);
	um[1].y=m[0]/M * (u[1].y-u[0].y);

	// set umt and umn values
	for(i=0;i<2;i++)
	{
		umt[i] = um[i].x * et.x + um[i].y * et.y;
		umn[i] = um[i].x * en.x + um[i].y * en.y;
	}

	// set v values
	for(i=0;i<2;i++)
	{
		v[i].x = umt[i] * et.x - umn[i] * en.x + V.x;
		v[i].y = umt[i] * et.y - umn[i] * en.y + V.y;
	}

	// reset particle values
	particles[p1]->setdx(v[0].x*COLLISION_FRICTION);
	particles[p1]->setdy(v[0].y*COLLISION_FRICTION);
	particles[p2]->setdx(v[1].x*COLLISION_FRICTION);
	particles[p2]->setdy(v[1].y*COLLISION_FRICTION);
    
} /* Collide */

bool circlesCollide(Circle *circle1, Circle *circle2)
{
//    collides() =
//    d = distance between two centers of i and j
//    r1 = radius of i
//    r2 = radius of j
//    collides if d < r1 + r2
    double d = sqrt(pow(circle2->getnextx() - circle1->getnextx(), 2) + pow(circle2->getnexty() - circle1->getnexty(), 2));
    return d < circle1->radius + circle2->radius;
}

bool circlesDoCollide(double x1, double y1, double r1, double x2, double y2, double r2)
{
    //    collides() =
    //    d = distance between two centers of i and j
    //    r1 = radius of i
    //    r2 = radius of j
    //    collides if d < r1 + r2
    double d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return d < r1 + r2;
}

//
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, char *string)
{
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}

    glDisable(GL_BLEND);
}


//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

    for (int i=0; i<BALLS->getCircles().size(); i++)
    {
        Circle *circle = BALLS->getCircles()[i];
//        circle->update(i);
//        circle->draw();
        /*
         circle.update()
            dy -= gravity
            dy *= AIR_FRICTION which is .999
            dx *= AIR_FRICTION
            
            wall collisions
            ball-ball collisions
            update position
                x += dx
                y += dy
         circle.draw()
        */
        glColor3ub(circle->red, circle->green, circle->blue);
        DrawCircle(circle->x, circle->y, circle->radius);
        circle->dy -= GRAVITY;
        circle->dx -= .05;
        circle->dy *= AIR_FRICTION;
        circle->dx *= FRICTION;
        // ball-ball collisions
        for (int j=0; j<_circles.size(); j++)
        {
            for (int k=j+1; k<_circles.size(); k++)
            {
                if (circlesCollide(_circles[j], _circles[k]))
                {
//                    Collide(j, k, _circles);
                }
            }
        }

        circle->x += circle->dx;
        circle->y += circle->dy;

        // wall collisions
        if (circle->y - circle->radius <= 0 || circle->y + circle->radius > screen_y)
        {
            circle->dy = -circle->dy;
            circle->y = 0 + circle->radius;
        }
        if (circle->x - circle->radius <= 0 || circle->x + circle->radius > screen_x)
        {
            circle->dx = -circle->dx;
        }
    }

	glutSwapBuffers();
    glutPostRedisplay();
}

double randomNumberInRange(double min, double max)
{
    return min + (rand() % (int)(max - min + 1));
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
		case 27: // escape character means to quit the program
			exit(0);
			break;
		case 'b':
			// do something when 'b' character is hit.
			break;
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	// Set the projection mode to 2D orthographic, and set the world coordinates:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
    BALLS = new Balls();
    std::srand( time(NULL) );
    for (int i=0; i<kNumCircles; i++)
    {
        double x, y, radius, dx, dy, r, g, b;
        radius = randomNumberInRange(gRadius - gRadiusRange, gRadius + gRadiusRange);
        bool placeFound = false;
        while (i>0 && !placeFound)
        {
            x = randomNumberInRange(0 + radius, BALLS->getScreenX() - radius);
            y = randomNumberInRange(0 + radius, BALLS->getScreenY() - radius);
            bool collision = false;
            for (int j=0; j<i; j++)
            {
                Circle *circle = BALLS->getCircles()[j];
                if (circlesDoCollide(x, y, radius, circle->getx(), circle->gety(), circle->getradius()))
                {
                    collision = true;
                    break;
                }
            }
            if (!collision)
            {
                placeFound = true;
            }

        }
        if (i < 1)
        {
            x = randomNumberInRange(0 + radius, BALLS->getScreenX() - radius);
            y = randomNumberInRange(0 + radius, BALLS->getScreenY() - radius);
        }
        dx = randomNumberInRange(gDX - gDXRange, gDX + gDXRange);
        dy = randomNumberInRange(gDY - gDYRange, gDY + gDYRange);
        r = randomNumberInRange(0, 255);
        g = randomNumberInRange(0, 255);
        b = randomNumberInRange(0, 255);
        BALLS->addCircle(new Circle(x, y, radius, dx, dy, r, g, b));
    }
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen)
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	}
	else
	{
		glutCreateWindow("This appears in the title bar");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	InitializeMyStuff();
    
	glutMainLoop();
    
	return 0;
}

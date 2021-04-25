#include "oglwidget.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "triangle.h"
#include "vertex.h"




#define PI 3.14159265358979323846
using namespace std;

static double alpha = 45.0; // rotation angle

//Faces usually have 3 values as they are triangles

vector <Vertex> points;

vector <Triangle> tris;

void ReadData( string fname);

void CopyVertices(vector <Vertex> vertices);



// initialize Open GL lighting and projection matrix
void InitLightingAndProjection() // to be executed once before drawing
{



    ReadData("C:\\Users\\k-ht\\Documents\\Studium\\Computergrafik\\CGX\\OpenGL_Example\\tetra.obj");
    //ReadData("D:\\Downloads\\Github\\CGX\\OpenGL_Example\\tetra.obj");

// for( int i=0; i<tris.size(); i++){
//     cout <<tris[i].getA() << tris[i].getB() << tris[i].getC() <<endl;
// }



    // light positions and colors
    GLfloat LightPosition1[4] = { 10, 5, 10,  0};
    GLfloat LightPosition2[4] = { -5, 5, -10,  0};
    GLfloat ColorRedish[4] = { 1.0,  .8,  .8,  1}; // white with a little bit of red
    GLfloat ColorBlueish[4] = { .8,  .8,  1.0,  1};// white with a little bit of blue

    glEnable( GL_DEPTH_TEST); // switch on z-buffer
    glDepthFunc( GL_LESS);

    glShadeModel( GL_SMOOTH); // Gouraud shading
    //glShadeModel( GL_FLAT);

    glEnable( GL_LIGHTING); // use lighting
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, 1); // draw both sides

    // define and switch on light 0
    glLightfv( GL_LIGHT0, GL_POSITION, LightPosition1);
    glLightfv( GL_LIGHT0, GL_DIFFUSE,  ColorRedish);
    glLightfv( GL_LIGHT0, GL_SPECULAR, ColorRedish);
    glEnable( GL_LIGHT0);

    // define and switch on light 1
    glLightfv( GL_LIGHT1, GL_POSITION, LightPosition2);
    glLightfv( GL_LIGHT1, GL_DIFFUSE,  ColorBlueish);
    glLightfv( GL_LIGHT1, GL_SPECULAR, ColorBlueish);
    glEnable( GL_LIGHT1);

    glMatrixMode( GL_PROJECTION); // define camera projection
    glLoadIdentity(); // reset matrix to identity (otherwise existing matrix will be multiplied with)
    glOrtho( -15, 15, -10, 10, -20, 20); // orthogonal projection (xmin xmax ymin ymax zmin zmax)
    //glFrustum( -10, 10, -8, 8, 2, 20); // perspective projektion
}

void ReadData( string fname){ //fname = "F:\\CG21\\MeshOpenGL\\mesh1.obj";
 ifstream file( fname);
 if (!file){
    cout << "error opening file" << endl;
    return;
 }
 string key;
 float x, y, z;
 while( file){
    file >> key >> x >> y >> z;
//    cout << key <<", "<< x <<", "<< y <<", "<< z << endl;
    if (key == "v"){
        points.push_back(Vertex(x,y,z));
    }
    if (key == "f"){
        tris.push_back(Triangle(x-1,y-1,z-1));
    }
 }
 file.close();

}

float * cross( float *n, float a[3], float b[3]){ // c = a cross b
 n[0] = a[1]*b[2] - a[2]*b[1];
 n[1] = a[2]*b[0] - a[0]*b[2];
 n[2] = a[0]*b[1] - a[1]*b[0];

 return n;
}

void DrawTriangle(){
    //looping through the triangles
    glBegin( GL_TRIANGLES);
        for( int i=0; i<tris.size()-1; i++){
            float * a = points[tris[i].getA()].getCoord();
            float * b = points[tris[i].getB()].getCoord();
            float * c = points[tris[i].getC()].getCoord();

            float nv[3];

            float * n= nv;
            float ab[]= {b[0]-a[0] ,b[1]-a[1],b[2]-a[2]};
            float ac[]= {c[0]-a[0] ,c[1]-a[1],c[2]-a[2]};

            n = cross(n,ab,ac);


//             for( int i=0; i<3; i++){
//                 cout <<n[i]  << endl;
//             }

            points[tris[i].getA()].getCoord();


            glNormal3fv(n);
            glVertex3fv(a);
            glVertex3fv(b);
            glVertex3fv(c);
        }
    glEnd();

}

// define material color properties for front and back side
void SetMaterialColor( int side, float r, float g, float b){
    float	amb[4], dif[4], spe[4];
    int	i, mat;

    dif[0] = r; // diffuse color as defined by r,g, and b
    dif[1] = g;
    dif[2] = b;
    for( i=0; i<3; i++){
        amb[i] = .1 * dif[i]; // ambient color is 10 percent of diffuse
        spe[i] = .5; // specular color is just white / gray
    }
    amb[3] = dif[3] = spe[3] = 1.0; // alpha component is always 1
    switch( side){
        case 1:	mat = GL_FRONT; break;
        case 2:	mat = GL_BACK; break;
        default: mat = GL_FRONT_AND_BACK; break;
    }
    glMaterialfv( mat, GL_AMBIENT, amb); // define ambient, diffuse and specular components
    glMaterialfv( mat, GL_DIFFUSE, dif);
    glMaterialfv( mat, GL_SPECULAR, spe);
    glMaterialf( mat, GL_SHININESS, 50.0); // Phong constant for the size of highlights
}



OGLWidget::OGLWidget(QWidget *parent) // constructor
    : QOpenGLWidget(parent)
{
    // Setup the animation timer to fire every x msec
    animtimer = new QTimer(this);
    animtimer->start( 50 );

    // Everytime the timer fires, the animation is going one step forward
    connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));

    animstep = 0;
}

OGLWidget::~OGLWidget() // destructor
{
}


void OGLWidget::stepAnimation()
{
    animstep++;    // Increase animation steps
    update();      // Trigger redraw of scene with paintGL
}

void OGLWidget::initializeGL() // initializations to be called once
{
    initializeOpenGLFunctions();

    InitLightingAndProjection(); // define light sources and projection
}

void OGLWidget::paintGL() // draw everything, to be called repeatedly
{
    glEnable(GL_NORMALIZE); // this is necessary when using glScale (keep normals to unit length)

    // set background color
    glClearColor(0.8, 0.8, 1.0, 1.0); // bright blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();				// Reset The Current Modelview Matrix
    glTranslated( 0 ,-3 ,-10.0);     // Move 10 units backwards in z, since camera is at origin
    glScaled( 1.0, 1.0, 1.0);       // scale objects
    glRotated( alpha, 0, 3, 1);     // continuous rotation
    alpha += 5;

    // define color: 1=front, 2=back, 3=both, followed by r, g, and b
    SetMaterialColor( 1, 1.0, .2, .2);  // front color is red
    SetMaterialColor( 2, 0.2, 0.2, 1.0); // back color is blue

    // draw a cylinder with default resolution
    DrawTriangle();

    // make it appear (before this, it's hidden in the rear buffer)
    glFlush();
}

void OGLWidget::resizeGL(int w, int h) // called when window size is changed
{
    // adjust viewport transform
    glViewport(0,0,w,h);
}


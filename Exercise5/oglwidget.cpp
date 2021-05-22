//author: Khai Tram, Reda Khalife, Finja Papke

#include "oglwidget.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "triangle.h"
#include "vertex.h"
#include "mesh.h"




#define PI 3.14159265358979323846
using namespace std;

static double alpha = 45.0; // rotation angle

// global variables and functions

//vector <Vertex> subdiv1;

//vector <Vertex> subdiv2;

//vector <Vertex> subdiv3;

vector <Vertex> points;

vector <Triangle> tris;

Mesh tetraMesh;

void ReadData( string fname);

vector <Vertex> Subdivide(vector <Vertex> pointList);

void SubdivLevel(Mesh& mesh,int count);

void DrawTriangle();

void SetMaterialColor( int side, float r, float g, float b);

// initialize Open GL lighting and projection matrix
void InitLightingAndProjection() // to be executed once before drawing
{

    // khai's path
    //ReadData("C:\\Users\\k-ht\\Documents\\Studium\\Computergrafik\\CGX\\Exercise5\\primo.obj");

    // finja's path
    ReadData("D:\\Downloads\\Github\\CGX\\Exercise5\\ps4.obj");

    // reda's path
    //ReadData("");

    // initially set valences to 0
    for (int i=0; i<tetraMesh.pts.size(); i++){
        tetraMesh.val.push_back(0);
    }

    // subdivision using the loop subdivision two times
    SubdivLevel(tetraMesh, 2);


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


// method for reading vertices ( and faces) out of a file and storing it in vectors
void ReadData( string fname){ //fname = "F:\\CG21\\MeshOpenGL\\mesh1.obj";
 ifstream file( fname);
 if (!file){
    cout << "error opening file" << endl;
    return;
 }
 string key;
 float x, y, z;
 while( file >> key){
     if (key == "v"||key == "f"){
         file >> x >> y >> z;
         cout << key <<", "<< x <<", "<< y <<", "<< z << endl;
     }
     if (key == "v"){
         tetraMesh.pts.push_back(Vertex(x,y,z));
     }
     if (key == "f"){
         tetraMesh.tris.push_back(Triangle(x-1,y-1,z-1));
     }
  }
  file.close();
}


// subdivision loop amount adjustable
void SubdivLevel(Mesh& mesh,int count){

    //recursive function call to do different levels of the algorhythm
    for (int i= 0; i < count; i++){

        ConnectivityAlgorithm(mesh);
        LoopSubdiv(mesh);
        mesh.Print();
    }
}

// function for subdivision used in Chaikin's algorithm
vector <Vertex> Subdivide(vector <Vertex> pointList){


    vector <Vertex> newPoints;

    // loop to create the new subdivision points out of existing points
    for (int i= 0; i < pointList.size()-1; i++){

        float * a = pointList[i].getCoord();
        float * b = pointList[i+1].getCoord();

        float x;
        float y;
        float z;

        // calculate vector of A to B
        float ab[]= {b[0]-a[0] ,b[1]-a[1],b[2]-a[2]};

        // getting coordinates for first subdivision point
        x= a[0] + 0.25*ab[0];
        y= a[1] + 0.25*ab[1];
        z= a[2] + 0.25*ab[2];

        Vertex newA = Vertex(x,y,z);

        // ... second subdivision point
        x= a[0] + 0.75*ab[0];
        y= a[1] + 0.75*ab[1];
        z= a[2] + 0.75*ab[2];

        Vertex newB = Vertex(x,y,z);

        // push new vertices into vector
        newPoints.push_back(newA);
        newPoints.push_back(newB);

    }

    return newPoints;
}

void DrawTriangle(){
    //looping through the triangles

    glPointSize(3.0f);
    glLineWidth(1.5f);

    glBegin( GL_TRIANGLES);

    // faces red
    //SetMaterialColor(0, 139, 38, 38);

        for( int i=0; i<tetraMesh.tris.size(); i++){
            float * a = tetraMesh.pts[tetraMesh.tris[i].getA()].getCoord();
            float * b = tetraMesh.pts[tetraMesh.tris[i].getB()].getCoord();
            float * c = tetraMesh.pts[tetraMesh.tris[i].getC()].getCoord();

            // calculate normal vector for flat shading
            float nv[3];
            float * n = nv;
            float ab[]= {b[0]-a[0],b[1]-a[1],b[2]-a[2]};
            float ac[]= {c[0]-a[0],c[1]-a[1],c[2]-a[2]};

            n[0] = ab[1]*ac[2] - ab[2]*ac[1];
            n[1] = ab[2]*ac[0] - ab[0]*ac[2];
            n[2] = ab[0]*ac[1] - ab[1]*ac[0];

            glNormal3fv(n);
            glVertex3fv(a);
            glVertex3fv(b);
            glVertex3fv(c);

        }
    glEnd();

    glBegin( GL_LINE_STRIP);

    // outline yellow
    SetMaterialColor(0, 255, 215, 0);

        for( int i=0; i<tetraMesh.tris.size(); i++){
            float * a = tetraMesh.pts[tetraMesh.tris[i].getA()].getCoord();
            float * b = tetraMesh.pts[tetraMesh.tris[i].getB()].getCoord();
            float * c = tetraMesh.pts[tetraMesh.tris[i].getC()].getCoord();

            //glNormal3fv(n);
            glVertex3fv(a);
            glVertex3fv(b);
            glVertex3fv(c);

        }
    glEnd();

//    glBegin(GL_POINTS);

//        for(int i=0; i<tetraMesh.pts.size(); i++){
//            float * point = tetraMesh.pts[i].getCoord();

//            glVertex3fv(point);
//        }
//    glEnd();

//    glBegin( GL_LINE_STRIP);
//        for( int i=0; i<subdiv1.size(); i++){

//            float * point = subdiv1[i].getCoord();

//            glVertex3fv(point);
//        }
//    glEnd();

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
{}

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
    glTranslated( 0 ,0 ,-10.0);     // Move 10 units backwards in z, since camera is at origin
    glScaled( 0.5, 0.5, 0.5);       // scale objects
    glRotated( alpha, 0, 3, 1);     // continuous rotation
    alpha += 5;

    // define color: 1=front, 2=back, 3=both, followed by r, g, and b
    SetMaterialColor( 1, 1.0, .2, .2);  // front color is red
    SetMaterialColor( 2, 0.2, 0.2, 1.0); // back color is blue

    // draw a cylinder with default resolution
    DrawTriangle();
    //Subdivide();

    // make it appear (before this, it's hidden in the rear buffer)
    glFlush();
}

void OGLWidget::resizeGL(int w, int h) // called when window size is changed
{
    // adjust viewport transform
    glViewport(0,0,w,h);
}


#include "triangle.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Triangle::Triangle()
{
}

Triangle::Triangle(int x,int y, int z)
{
    a = x;
    b = y;
    c = z;
}

vector <Triangle> Triangle::getTris(){
    return tris;
}

vector <Vertex> Triangle::getPoints(){
    return points;
}

int Triangle::getA(){
    return a;
}

void Triangle::cross( float c[3], float a[3], float b[3]){ // c = a cross b
 c[0] = a[1]*b[2] - a[2]*b[1];
 c[1] = a[2]*b[0] - a[0]*b[2];
 c[2] = a[0]*b[1] - a[1]*b[0];
}

void Triangle::ReadData( string fname){ //fname = "F:\\CG21\\MeshOpenGL\\mesh1.obj";
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
        tris.push_back(Triangle(x--,y--,z--));
    }
 }
 file.close();
 //test correct transfer of data
  cout << points[1].getX() << endl;
  cout << tris[0].getA() << endl;
}

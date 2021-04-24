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

int Triangle::getA(){
    return a;
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
        tris.push_back(Triangle(x,y,z));
    }
 }
 file.close();
 cout << points[1].getX() << endl;
  cout << tris[1].getA() << endl;
}

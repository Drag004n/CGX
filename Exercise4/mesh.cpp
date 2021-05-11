//author: Khai Tram, Reda Khalife, Finja Papke

#include "mesh.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Mesh::Mesh()
{
}

//constructor for vector of vertices
Mesh::Mesh(vector <Vertex> points, vector <Triangle> triangles)
{
    pts= points;
    tris = triangles;
}

void Mesh::Print(){
    for (int i= 0; i< pts.size();i++){
        pts[i].Print();
    }
    for (int i= 0; i< tris.size();i++){
        tris[i].Print();
    }

}



//author: Khai Tram, Reda Khalife, Finja Papke

#ifndef MESH_H
#define MESH_H

#include <QObject>
#include "vertex.h"
#include "triangle.h"
#include <string>
#include <vector>

using namespace std;

class Mesh
{
public:
    Mesh();
    Mesh(vector <Vertex> points); // point list
    Mesh(vector <int> valences); // valence list (no. of triangles for every point)
    Mesh(vector <Triangle> tris); // triangle list
};

#endif // MESH_H

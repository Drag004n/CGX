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
    Mesh(vector <Vertex> points, vector <Triangle> tris);
    void Print();
    void ConnectivityAlgorithm(vector <Vertex> pts, vector <Triangle> tris);
private:
    vector <Vertex> pts; // point list
    vector <int> val; // valence list (no. of triangles for every point
    vector <Triangle> tris; // triangle list

    friend void ReadData(string fname);
};

#endif // MESH_H

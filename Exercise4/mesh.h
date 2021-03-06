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

private:
    vector <Vertex> pts; // point list
    vector <int> val; // valence list (no. of triangles for every point
    vector <Triangle> tris; // triangle list

    friend void ReadData(string fname);
    friend void ConnectivityAlgorithm(Mesh& mesh);
    friend void LinSubdiv(Mesh& mesh);
    friend void findTx (int tIndex, Mesh& mesh, int i);
    friend void switchTx (int tIndex, int tx, Mesh& mesh,int t);
    friend void InitLightingAndProjection();
};

#endif // MESH_H

//author: Khai Tram, Reda Khalife, Finja Papke

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include "vertex.h"
#include "mesh.h"
#include <string>
#include <vector>

using namespace std;

class Triangle
{
public:
    Triangle();
    Triangle(int a, int b, int c);
    Triangle(int vertex[3], int adjtriangle[3],int edges[3]);
    //Triangle(int x, int y, int z);
    void Print();
    int getA();
    int getB();
    int getC();

    friend void ConnectivityAlgorithm(Mesh mesh);

private:
    int iv[3]; // vertex indices
    int it[3]; // adjacent triangle indices
    int ie[3]; // edge vertex indices
};

#endif // TRIANGLE_H

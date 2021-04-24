#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include "vertex.h"
#include <string>
#include <vector>

using namespace std;

class Triangle
{
public:
    Triangle();
    Triangle(int x, int y, int z);
    void test(string test);
    void ReadData(string fname);
    int getA();

private:
    int a,b,c;
    vector <Vertex> points;
    //Faces usually have 3 values as they are triangles
    vector <Triangle> tris;
};

#endif // TRIANGLE_H

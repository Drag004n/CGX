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
    void cross( float c[3], float a[3], float b[3]);
    void ReadData(string fname);
    int getA();
    vector <Triangle> getTris();
    vector <Vertex> getPoints();

private:
    int a,b,c;
    vector <Vertex> points;
    //Faces usually have 3 values as they are triangles
    vector <Triangle> tris;
};

#endif // TRIANGLE_H

//author: Khai Tram, Reda Khalife, Finja Papke

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
    Triangle(int i[3]);
    Triangle(int x, int y, int z);
    int getA();
    int getB();
    int getC();

    int iv[3]; // vertex indices
    int it[3]; // adjacent triangle indices
    int ie[3]; // edge vertex indices

    void print();

private:
    int a,b,c;
};

#endif // TRIANGLE_H

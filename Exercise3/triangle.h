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
    Triangle(int x, int y, int z);
    int getA();
    int getB();
    int getC();
private:
    int a,b,c;
};

#endif // TRIANGLE_H

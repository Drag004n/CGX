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

// constructor for three point triangles
Triangle::Triangle(int x,int y, int z)
{
    a = x;
    b = y;
    c = z;
}

int Triangle::getA(){
    return a;
}

int Triangle::getB(){
    return b;
}

int Triangle::getC(){
    return c;
}



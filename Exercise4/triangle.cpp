//author: Khai Tram, Reda Khalife, Finja Papke

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

// constructor for three point triangle
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

//print method
//void print( string text = "myVector ="){
//    cout << text;
//    cout << " [ " << xyz[0] << "; " << xyz[1] << "; " << xyz[2] << "]" << endl;
//}


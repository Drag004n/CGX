//author: Khai Tram, Reda Khalife, Finja Papke

#include "vertex.h"
#include <QObject>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

Vertex::Vertex()
{
}

float * Vertex::getCoord(){
    return coord;
}

Vertex::Vertex( float a, float b, float c){ // constructor with initialization
    coord[0] = a;
    coord[1] = b;
    coord[2] = c;
}

void Vertex::Print(){

    cout << " [ " << coord[0] << "; " << coord[1] << "; " << coord[2] << "]" << endl;
}

Vertex operator+(Vertex a, Vertex b){
    Vertex firstVector = Vertex( a.coord[0] + b.coord[0], a.coord[1] + b.coord[1], a.coord[2] + b.coord[2]);
    return firstVector;
}
Vertex operator-(Vertex a, Vertex b){
    Vertex firstVector = Vertex( a.coord[0] - b.coord[0], a.coord[1] - b.coord[1], a.coord[2] - b.coord[2]);
    return firstVector;
}
Vertex operator-( Vertex a){ // unary -
    return -1*a;
}
// multiply float with vertex
Vertex operator*( float s, Vertex b){
    return Vertex( s*b.coord[0], s*b.coord[1], s*b.coord[2]);
}
// ... and vice versa
Vertex operator*( Vertex a, float t){
    return t*a;
}
// scalar product
float operator*( Vertex a, Vertex b){
    return a.coord[0] * b.coord[0] + a.coord[1] * b.coord[1] + a.coord[2] * b.coord[2];
}
// cross product calculation
void cross( float c[3], float a[3], float b[3]){ // c = a cross b
 c[0] = a[1]*b[2] - a[2]*b[1];
 c[1] = a[2]*b[0] - a[0]*b[2];
 c[2] = a[0]*b[1] - a[1]*b[0];
}
// cross operator
Vertex operator%( Vertex a, Vertex b){
    Vertex c;
    cross( c.coord, a.coord, b.coord);
    return c;
}



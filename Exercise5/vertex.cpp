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

Vertex::Vertex( float a, float b, float c){ // constructor creating a vertex object containing three float value coordinates x y z
    coord[0] = a;
    coord[1] = b;
    coord[2] = c;
}

void Vertex::Print(){

    cout << " [ " << coord[0] << "; " << coord[1] << "; " << coord[2] << "]" << endl;
}

// overridden operators for use on vertex objects
// plus operator
Vertex operator+(Vertex a, Vertex b){
    Vertex firstVector = Vertex( a.coord[0] + b.coord[0], a.coord[1] + b.coord[1], a.coord[2] + b.coord[2]);
    return firstVector;
}

// minus operator
Vertex operator-(Vertex a, Vertex b){
    Vertex firstVector = Vertex( a.coord[0] - b.coord[0], a.coord[1] - b.coord[1], a.coord[2] - b.coord[2]);
    return firstVector;
}

// negative operator
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

// divide vertex by float
Vertex operator/( Vertex a, float t){
    return (1/t)*a;
}

// member functions
void Vertex::operator*=( float a){
    // a *= b multiplies a with b and gives a the product value
    coord[0] *= a;
    coord[1] *= a;
    coord[2] *= a;

}

void Vertex::operator+=( Vertex a){
    // a += b adds a to b and gives a the result
    coord[0] += a.coord[0];
    coord[1] += a.coord[1];
    coord[2] += a.coord[2];
}

// compare operator rounding up (to prevent thrown false if values differ in the lower decimal places) and returning boolean
bool Vertex::operator==( Vertex a){
    float roundCoord[3];
    float roundACoord[3];
        for (int i = 0; i< 3;i++){
            roundCoord[i] = roundf(coord[i] * 100) / 100;
            roundACoord[i] = roundf(a.coord[i] * 100) / 100;
        }

    if(roundCoord[0] == roundACoord[0]&&
    roundCoord[1] == roundACoord[1]&&
    roundCoord[2]== roundACoord[2]){
        return true;
    }
    else{
        return false;
    }
}





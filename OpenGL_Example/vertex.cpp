#include "vertex.h"
#include <QObject>

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

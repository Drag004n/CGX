#include "vertex.h"
#include <QObject>

Vertex::Vertex()
{
}

float Vertex::getX(){
    return x;
}

float Vertex::getY(){
    return y;
}

float Vertex::getZ(){
    return z;
}

Vertex::Vertex( float a, float b, float c){ // constructor with initialization
    x = a;
    y = b;
    z = c;
}

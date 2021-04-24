#include "vertex.h"
#include <QObject>

Vertex::Vertex()
{

}

float Vertex::getX(){
    return x;
}

Vertex::Vertex( float a, float b, float c){ // constructor with initialization
    x = a;
    y = b;
    z = c;
}

#ifndef VERTEX_H
#define VERTEX_H

#include <QObject>

class Vertex{
public:
    Vertex(); // empty constructor
    Vertex(float a, float b, float c);
    float getX();
private:
    float x,y,z;
};




#endif // VERTEX_H

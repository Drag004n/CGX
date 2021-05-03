//author: Khai Tram, Reda Khalife, Finja Papke

#ifndef VERTEX_H
#define VERTEX_H

#include <QObject>

class Vertex{
public:
    static const int size = 3;
    Vertex(); // empty constructor
    Vertex(float a, float b, float c);
    float * getCoord();

private:

    float coord[size]; //coordinates
};




#endif // VERTEX_H

//author: Khai Tram, Reda Khalife, Finja Papke

#ifndef VERTEX_H
#define VERTEX_H

#include <QObject>
#include <string>

using namespace std;

class Vertex{//alternativley, use getters and setters
public:
    static const int size = 3;

    Vertex(); // empty constructor
    Vertex(float points[3]);
    Vertex(float a, float b, float c);
    float * getCoord();
    void Print();

    friend Vertex operator+( Vertex a, Vertex b); // add points or vectors
    friend Vertex operator-( Vertex a, Vertex b); // subtract points or vectors
    friend Vertex operator*( float a, Vertex b); // product between scalar and vector
    friend float operator*( Vertex a, Vertex b); // scalar product
    friend Vertex operator%( Vertex a, Vertex b); // cross product


private:
    float coord[size]; //coordinates
};



#endif // VERTEX_H

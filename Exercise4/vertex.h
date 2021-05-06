//author: Khai Tram, Reda Khalife, Finja Papke

#ifndef VERTEX_H
#define VERTEX_H

#include <QObject>

class Vertex{//alternativley, use getters and setters
public:
    float p[3];//coordinates
    static const int size = 3;

    Vertex(); // empty constructor
    Vertex(float points[3]);
    Vertex(float a, float b, float c);
    float * getCoord();

    friend Vertex operatorPlus( Vertex a, Vertex b); // add points or vectors
    friend Vertex operatorMinus( Vertex a); // subtract points or vectors
    friend Vertex operatorMultipy( float a, Vertex b); // product between scalar and vector
    friend float operatorScalar( Vertex a, Vertex b); // scalar product
    friend void operatorCross( Vertex a, Vertex b); // cross product
    friend float * getPoint(Vertex a, int position);


private:
    float coord[size]; //coordinates


};



#endif // VERTEX_H

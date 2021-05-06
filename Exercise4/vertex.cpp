//author: Khai Tram, Reda Khalife, Finja Papke

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

// add points or vectors
//Vertex Vertex::operatorPlus( Vertex a, Vertex b){
//    Vertex firstVector = Vertex( a.p[0] + b.p[0], a.p[1] + b.p[1], a.p[2] + b.p[2]);
//    return firstVector;
//};

//// subtract points or vectors
////Vertex Vertex::operatorMinus(Vertex a){
////    return -1*a;
////};

//// product between scalar and vector
//Vertex Vertex:: operatorMultipy( float a, Vertex b){
//    return Vertex( a*b.p[0], a*b.p[1], a*b.p[2]);
//};

// scalar product
//float Vertex::operatorMultiplyTwo( Vertex a, Vertex b){
//    float a = 3f;
//    return a  ;
//};

// cross product
//void::operatorCross( Vertex a, Vertex b){
//};

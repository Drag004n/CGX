
#define VERTEX_H


class vertex{
public:
    float x,y,z;

    vertex(); // empty constructor
    vertex( float x, float y, float z); // constructor with initialization


};

vertex::vertex(){}; // empty constructor

vertex::vertex( float a, float b, float c){ // constructor with initialization
    x = a;
    y = b;
    z = c;
}

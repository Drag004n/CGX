//author: Khai Tram, Reda Khalife, Finja Papke

#include "triangle.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Triangle::Triangle()
{
}

// constructor for a triangle object containing a size 3 array of vertex indices referring to the vertex vector
Triangle::Triangle(int a, int b, int c)
{
    iv[0]= a;
    iv[1]= b;
    iv[2]= c;
}

void Triangle::Print(){

    cout << " [Points:" << iv[0] << "; " << iv[1] << "; " << iv[2] << "]" << endl;
    cout << " [neighbours:" << it[0] << "; " << it[1] << "; " << it[2] << "]" << endl;
    cout << " [Edges:" << ie[0] << "; " << ie[1] << "; " << ie[2] << "]" << endl;
}

//getters
int Triangle::getA(){
    return iv[0];
}

int Triangle::getB(){
    return iv[1];
}

int Triangle::getC(){
    return iv[2];
}

/* constructor for a triangle object containing the vertex index array,
 * a 3 size array with the neighbor triangle indices and
 * a 3 size array with the indices of the added edge vertices
 */
Triangle::Triangle(int vertex[3], int adjtriangle[3],int edges[3])
{
    for (int i=0; i<3; i++){
        iv[i] = vertex[i];
        it[i] = adjtriangle[i];
        ie[i] = edges[i];
    }
}


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

// constructor for three point triangle
//Triangle::Triangle(int x,int y, int z)
//{
//    a = x;
//    b = y;
//    c = z;
//}



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

Triangle::Triangle(int vertex[3], int adjtriangle[3],int edges[3])
{
    for (int i=0; i<3; i++){
        iv[i] = vertex[i];
        it[i] = adjtriangle[i];
        ie[i] = edges[i];
    }
}



//print method
//void print( string text = "myVector ="){
//    cout << text;
//    cout << " [ " << xyz[0] << "; " << xyz[1] << "; " << xyz[2] << "]" << endl;
//}


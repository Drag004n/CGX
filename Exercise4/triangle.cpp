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

    cout << " [ " << iv[0] << "; " << iv[1] << "; " << iv[2] << "]" << endl;
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


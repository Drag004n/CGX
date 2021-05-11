//author: Khai Tram, Reda Khalife, Finja Papke

#include "mesh.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Mesh::Mesh()
{
}

//constructor for vector of vertices
Mesh::Mesh(vector <Vertex> points, vector <Triangle> triangles)
{
    pts= points;
    tris = triangles;
}

void Mesh::Print(){
    for (int i= 0; i< pts.size();i++){
        pts[i].Print();
    }
    for (int i= 0; i< tris.size();i++){
        tris[i].Print();
    }
}

void ConnectivityAlgorithm(Mesh mesh){
    vector <int> val;

    //set all vertice valences to 0
    for (int i=0; i<mesh.pts.size(); i++){
        val.push_back(0);
    }

    //run through triangles and find neighbors and valences
    for (int i=0; i<mesh.tris.size(); i++){
        Triangle t = mesh.tris[i];
        int a = mesh.tris[i].iv[0];
        int b = mesh.tris[i].iv[1];
        int c = mesh.tris[i].iv[2];
         cout << " [ " << a << "; " << b << "; " << c << "]" << endl;
        //find t0 containing b and c but not a
//        for (Triangle t0 : mesh.tris) // iterate over array fibonacci
//        {

//        }

        //find t with c and a no b

        //find t with a and b no c

        //n a ++
        //n b ++
        //n c ++
    }

    //save n's for each point in vector with right indices
    //save neighbor triangles as it[i] with ie[i]
}

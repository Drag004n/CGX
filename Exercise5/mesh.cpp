//author: Khai Tram, Reda Khalife, Finja Papke

#include "mesh.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define PI 3.14159265358979323846
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

void findTx (int tx, Mesh& mesh,int i);

void Mesh::Print(){



    for (int i= 0; i< pts.size();i++){
        pts[i].Print();
    }
    for (int i= 0; i< tris.size();i++){
        tris[i].Print();
    }

    for (int i= 0; i< val.size();i++){
        cout << " [valences: " << i << "; " << val[i] << "]" << endl;
    }
}

// calculate beta of n with n being the valence of a point
float betaN(int n){
    float alpha_n = 3.0f/8.0f + pow(3.0f/8.0f + 1.0f/4.0f * cos(2*PI/n), 2);
    float beta_n = 8.0f/5.0f * alpha_n - 3.0f/5.0f;
    return beta_n;
        cout << beta_n << endl;
}

void ConnectivityAlgorithm(Mesh& mesh){

//    int n = 5;
//    float bt_n = betaN(n);
//    cout << "betaTest: " << bt_n << endl;

    // set valences to 0
    for (int i = 0; i<mesh.pts.size(); i++){
        mesh.val[i] = 0;
    }

    //run through triangles and find neighbors and valences
    for (int i=0; i<mesh.tris.size(); i++)
    {
        int a = mesh.tris[i].getA();
        int b = mesh.tris[i].getB();
        int c = mesh.tris[i].getC();

        for (int tx=0; tx<3; tx++){

        //find neighbours of the triangle with index
        findTx(tx, mesh, i);
        }

        // increase valence values for every point of t by 1
        mesh.val[a]++;
        mesh.val[b]++;
        mesh.val[c]++;

    }
}

/* find adjacent Triangle with common points and pushes
 * it to it of triangle
 *
 * t0 containing b and c but not a
 * t1 containing a and c but not b
 * t2 containing a and b but not c
 *
 *
 *param:
 *tIndex = switch Index to find correct neighbour
 *tx= index of neighbour triangle
 *tria = triangle vector of mesh
 *t= index of initial triangle
 */
void switchTx (int tIndex, int tx, Mesh& mesh, int t){

    //gets vertex indices of initial Triangle
    int a = mesh.tris[t].getA();
    int b = mesh.tris[t].getB();
    int c = mesh.tris[t].getC();

    //counts amount of vertices in common, must be 2 in order to be adjacent triangle
    int count = 0;

    switch(tIndex) {
        //find t0 containing b and c but not a
        case 0:
            //loop through all vertices of the current triangle and
            //compares them with the vertices of the initial triangle
            for (int indV=0 ; indV <3; indV++ )
            {
                int v = mesh.tris[tx].iv[indV];
                // when point b or c matches increase the counter
                if (v == b || v== c){
                    count++;

                }
            }

            if (count ==2){
                 //push index of adjacent triangle into it of t
                mesh.tris[t].it[tIndex]= tx;
            }
            break;
        //find t1 with c and a no b
        case 1:
        //loop through all vertices of the current triangle
        //and compares them with the vertices of the initial triangle
            for (int indV=0; indV <3; indV++ )
            {
                int v = mesh.tris[tx].iv[indV];
                // when point a or c matches increase the counter
                if (v == a || v== c){
                    count++;

                }
            }

            if (count ==2){
                 //push index of adjacent triangle into it of t
                mesh.tris[t].it[tIndex]= tx;
            }
            break;
        //find t2 with a and b no c
        case 2:
            for (int indV=0; indV <3; indV++ )
            {
                int v = mesh.tris[tx].iv[indV];
                // when point a or b matches increase the counter
                if (v == a || v== b){
                    count++;

                }
            }

            if (count ==2){
                 //push index of adjacent triangle into it of t
                mesh.tris[t].it[tIndex]= tx;
            }
            break;
       }

}

/* find the adjacent triangle on a specific side
 *
 * tIndex= index to find correct neighbour (important for switch case)
 * mesh= the mesh
 * i = index of initial triangle
 *
 * return:indexT = Index of adjacent Triangle
 */
void findTx (int tIndex, Mesh& mesh, int i){
    // loops again throiugh all triangles to compare them with initial triangle
    for (int tx=0; tx<mesh.tris.size(); tx++)
       {
           //if not the initial triangle
           if (tx != i){
               switchTx(tIndex, tx, mesh, i);
            }
       }
}

// calculate and store edge vertices in vector of points and as ie of triangles
void CalcEdge(Mesh& mesh, int i0, int i1, int i2, int i3, int i){

    //get points from indices
    Vertex v0 = mesh.pts[i0];
    Vertex v1 = mesh.pts[i1];
    Vertex v2 = mesh.pts[i2];
    Vertex v3 = mesh.pts[i3];

    Vertex ev = 1.0f/8.0f*(v0 + 3*v1 + 3*v2 + v3);

    //ev.Print();

    mesh.pts.push_back(ev);
    mesh.tris[i].ie[mesh.pts.size()-1];

}

// loop to create new subdivision points out of existing points
void LoopSubdiv (Mesh& mesh){

    // calculate edge mask out of two adjacent triangle points
    // loop through triangles and all neighbors to find e, test if e exists


    //loop through all triangles
    for (int i= 0; i < mesh.tris.size(); i++){

        // get Vertices of current Triangle
        int a = mesh.tris[i].getA();
        int b = mesh.tris[i].getB();
        int c = mesh.tris[i].getC();
        int d;

        // loop through all 3 neighbors and find fourth point index,
        for (int j=0; j<3; j++){
            // vertex index of current neighbour
            int tx = mesh.tris[i].it[j];

            if(i < tx){
                // loop through points of the neighbour
                for (int k = 0; k<3; k++){
                    //v = index of current point
                    int v = mesh.tris[tx].iv[k];

                    //current point musn't be contained in current triangle
                    if (v != a && v != b && v != c){
                        d = v;

                        switch (j){
                        case 0:
                            CalcEdge(mesh, a, b, c, d, i);
                            break;
                        case 1:
                            CalcEdge(mesh, b, a, c, d, i);
                            break;
                        case 2:
                           CalcEdge(mesh, c, b, a, d, i);
                            break;
                        }
                       }
                        // assign indices of e's to triangle ie

                }
            }
        }



        //cout << "Test: " << i0 << "," << i1 << "," << i2 << "," << i3 << endl

        float x;
        float y;
        float z;

        // calculate vector of A to B
        //float ab[]= {b[0]-a[0] ,b[1]-a[1],b[2]-a[2]};

        // getting coordinates of edge vertex
//        x= a[0] + 0.5*ab[0];
//        y= a[1] + 0.5*ab[1];
//        z= a[2] + 0.5*ab[2];

        Vertex newE = Vertex(x,y,z);

        // push three new edge vertices into ie of corresponding triangle
        // check if point exists yet, otherwise no push

        //mesh.tris[t].ie.push_back(newE);
        //testprint
    }

    // implement new points with faces into mesh to make
    // 4 triangles out of 1
}

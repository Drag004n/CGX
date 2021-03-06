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
        //cout << beta_n << endl;
}

// algorithm for creating the connectivity of a mesh by finding the valences and neighbor triangles
void ConnectivityAlgorithm(Mesh& mesh){

//    int n = 5;
//    float bt_n = betaN(n);
//    cout << "betaTest: " << bt_n << endl;

    // set valences to 0
    for (int i = 0; i<mesh.pts.size(); i++){
        mesh.val[i] = 0;

        if (i >= mesh.val.size()){
            mesh.val.push_back(0);
        }
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

//    LoopSubdiv(mesh);
//    mesh.Print();
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
Vertex CalcEdge(Mesh& mesh, int i0, int i1, int i2, int i3){

    //get points from indices
    Vertex v0 = mesh.pts[i0];
    Vertex v1 = mesh.pts[i1];
    Vertex v2 = mesh.pts[i2];
    Vertex v3 = mesh.pts[i3];

    Vertex ev = 1.0f/8.0f*(v0 + 3*v1 + 3*v2 + v3);

    return ev;
}

// relocate vertices using vertex mask
void VertexMask(Mesh& mesh){
    // loop through all points and multiply by beta of valence
    for (int i=0; i<mesh.val.size(); i++){
        int n = mesh.val[i];
        float beta = betaN(n);
        mesh.pts[i] *= beta;
    }

    // relocate points using formula
    for (int i=0; i<mesh.tris.size(); i++){

    // valences and edge vertices
    int valA = mesh.val[mesh.tris[i].iv[0]];
    int valB = mesh.val[mesh.tris[i].iv[1]];
    int valC = mesh.val[mesh.tris[i].iv[2]];

    Vertex e0 = mesh.pts[mesh.tris[i].ie[0]];
    Vertex e1 = mesh.pts[mesh.tris[i].ie[1]];
    Vertex e2 = mesh.pts[mesh.tris[i].ie[2]];


    mesh.pts[mesh.tris[i].iv[0]] += (1 - betaN(valA)) / valA * (e1 + e2) / 2;
    mesh.pts[mesh.tris[i].iv[1]] += (1 - betaN(valB)) / valB * (e2 + e0) / 2;
    mesh.pts[mesh.tris[i].iv[2]] += (1 - betaN(valC)) / valC * (e0 + e1) / 2;


    }

}

// method for creating and inserting the new triangles into the triangle vector by replacing the vector by a new one containing the triangles
void NewTris(Mesh& mesh){
    // create new triangle vector to replace with existing one
    vector <Triangle> newTris;

    // replace triangle t by first of the four new ones, add rest to triangle vector
    for (int i=0; i<mesh.tris.size(); i++){

        // three triangle vertice indices
        int a = mesh.tris[i].iv[0];
        int b = mesh.tris[i].iv[1];
        int c = mesh.tris[i].iv[2];

        // edge vertice indices of the triangle
        int e0 = mesh.tris[i].ie[0];
        int e1 = mesh.tris[i].ie[1];
        int e2 = mesh.tris[i].ie[2];

        // build new triangles and push into new triangle vector (four triangles for each of the old triangles)
        /* NOTE! New triangles will have no edges, thus showing incorrect values in the print.
         * Their neighbors are found by running the connectivity algorithm a second time,
         * which is used to find their edge vertices with each new following subdivision.
         */
        newTris.push_back(Triangle(e1, e0, c));
        newTris.push_back(Triangle(e1, e2, e0));
        newTris.push_back(Triangle(a, e2, e1));
        newTris.push_back(Triangle(e2, b, e0));
    }
    // replace new triangle vector with old one in mesh
    mesh.tris = newTris;
}

// loop to create new subdivision points out of existing points
void LoopSubdiv (Mesh& mesh){

    // calculate edge mask out of adjacent triangle points
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
            // triangle index of current neighbour
            int tx = mesh.tris[i].it[j];

            Vertex ev;
                // loop through points of the neighbour
                for (int k = 0; k<3; k++){
                    //v = index of current point
                    int v = mesh.tris[tx].iv[k];

                    //current point musn't be contained in current triangle
                    if (v != a && v != b && v != c){
                        d = v;

                        switch (j){
                        case 0:
                            ev= CalcEdge(mesh, a, b, c, d);
                            break;
                        case 1:
                            ev =CalcEdge(mesh, b, a, c, d);
                            break;
                        case 2:
                            ev= CalcEdge(mesh, c, b, a, d);
                            break;
                        }
                       }
                }

                    if(i < tx){
                    mesh.pts.push_back(ev);
                    mesh.tris[i].ie[j]= mesh.pts.size()-1;

                    } else {
                     // if the Edge has already been calculated we compare it
                     // with the existing edges of initial triangle and add that index

                        int eIndex;
                        Vertex compE;

                        //loop through edges of current triangle
                        for (int ii = 0; ii<3; ii++){
                            eIndex = mesh.tris[tx].ie[ii];
                            compE = mesh.pts[eIndex];

                            if (compE == ev){
                                mesh.tris[i].ie[j]= eIndex;

                            }
                        }
                    }
        }
    }

    // relocate existing vertices by multiplying them with beta of valence
    // vertex mask formula
    VertexMask(mesh);

    // replace triangle by four newly calculated ones
    NewTris(mesh);
}

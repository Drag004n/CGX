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
        //find t0 containing b and c but not a
        findTx(tx, mesh, i);
        }

        // increase valence values for every point of t by 1
        mesh.val[a]++;
        mesh.val[b]++;
        mesh.val[c]++;

    }
}

/* find adjacent Triangle
 *
 * t0 containing b and c but not a
 * t1 containing a and c but not b
 * t2 containing a and b but not c
 *
 *
 *param:
 *tIndex = switch Index for point identificatiion
 *tx= index of neighbour triangle
 *tria = triangle vector of mesh
 *t= index of initial triangle
 *countPointer = pointer to our counter in findTx
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
            //loop through all vertices of the current triangle and compares them with the vertices of the initial triangle
            for (int indV=0 ; indV <3; indV++ )
            {


                int v = mesh.tris[tx].iv[indV];
                // when point b or c matchess increase the counter
                if (v == b || v== c){
                    count++;

                }
            }

            if (count ==2){
                 //push index of adjacent triangle into it of t
                mesh.tris[t].it[tIndex]= tx;
            }
            break;
        //find t with c and a no b
        case 1:
        //loop through all vertices of the current triangle and compares them with the vertices of the initial triangle
            for (int indV=0; indV <3; indV++ )
            {
                int v = mesh.tris[tx].iv[indV];
                // when point a or c matchess increase the counter
                if (v == a || v== c){
                    count++;

                }
            }

            if (count ==2){
                 //push index of adjacent triangle into it of t
                mesh.tris[t].it[tIndex]= tx;
            }
            break;
        //find t with a and b no c
        case 2:
            for (int indV=0; indV <3; indV++ )
            {
                int v = mesh.tris[tx].iv[indV];
                // when point a or b matchess increase the counter
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
 * tIndex= index of neighbour triangle (important for switch case)
 * tria= triangles from the mesh
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
           // if counter reaches, which means two common points the the index will be returned

       }
}

// calculate and store edge vertices in vector of points and as ie of triangles
void CalcEdge(Mesh& mesh, int i0, int i1, int i2, int i3, int i){

    //get points from indices
    Vertex v0 = mesh.pts[i0];
    Vertex v1 = mesh.pts[i1];
    Vertex v2 = mesh.pts[i2];
    Vertex v3 = mesh.pts[i3];

    Vertex ev = 3.0f/8.0f*(v0 + v1) + 1.0f/8.0f*(v2 + v3);

    mesh.pts.push_back(ev);
    mesh.tris[i].ie[mesh.pts.size()-1];
}

// loop to create new subdivision points out of existing points
void LoopSubdiv (Mesh& mesh){

    // calculate edge mask out of two adjacent triangle points
    // loop through triangles and all neighbors to find e, test if e exists

    for (int i= 0; i < mesh.tris.size(); i++){

        // t points 0 to 2 and t0 point 3
        //indices of points
        int i0 = 0;
        int i1 = 0;
        int i2 = 0;
        int i3 = 0;

        // loop through all 3 neighbors and find fourth point index
        for (int j=0; j<3; j++){

            // change order of assignment of points of t for each "rotation" through neighbor triangles
            if (j==0){
                i0 = mesh.tris[i].iv[0];
                i1 = mesh.tris[i].iv[1];
                i2 = mesh.tris[i].iv[2];
            } else if (j == 1){
                i0 = mesh.tris[i].iv[1];
                i1 = mesh.tris[i].iv[0];
                i2 = mesh.tris[i].iv[2];
            } else if (j == 2){
                i0 = mesh.tris[i].iv[2];
                i1 = mesh.tris[i].iv[0];
                i2 = mesh.tris[i].iv[1];
            }

            int it3 = mesh.tris[i].it[j];
            // if index of t less than index of neighbor t0 calculate edge vertices
            //if (i<j){
                for (int k = 0; k<3; k++){

                    int v = mesh.tris[it3].iv[k];

                    if (v != i0 && v != i1 && v != i2){
                        i3 = v;

                        CalcEdge(mesh, i0, i1, i2, i3, i);
                    }
                }
                // if index of t greater than index of neighbor t0 get ie from t0
            //} else {
                //mesh.tris[i].ie[j] = mesh.tris[it3].ie[j];
            //}
        }
        //cout << "Test: " << i0 << "," << i1 << "," << i2 << "," << i3 << endl;
    }

    // implement new points with faces into mesh to make
    // 4 triangles out of 1
}

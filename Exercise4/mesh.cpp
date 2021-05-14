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

void ConnectivityAlgorithm(Mesh& mesh){

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

void LinSubdiv (Mesh& mesh){
    // loop to create new subdivision points out of existing points

    /* every point's connection vector to all others needs to be
     * checked and halved to create new edge vertices
     */

    // loop not correct yet!! only passes through all points in a line
    for (int i= 0; i < mesh.pts.size()-1; i++){

        float * a = mesh.pts[i].getCoord();
        float * b = mesh.pts[i+1].getCoord();

        float x;
        float y;
        float z;

        // calculate vector of A to B
        float ab[]= {b[0]-a[0] ,b[1]-a[1],b[2]-a[2]};

        // getting coordinates of edge vertex
        x= a[0] + 0.5*ab[0];
        y= a[1] + 0.5*ab[1];
        z= a[2] + 0.5*ab[2];

        Vertex newE = Vertex(x,y,z);

        // push three new edge vertices into ie of corresponding triangle
        // check if point exists yet, otherwise no push

        //mesh.tris[t].ie.push_back(newE);
        //testprint
    }

    // implement new points with faces into mesh to make
    // 4 triangles out of 1
}

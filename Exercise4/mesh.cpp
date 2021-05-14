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

int findTx (int tx, vector <Triangle> tria,int i);

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
    for (int i=0; i<mesh.tris.size(); i++)
    {
        //declare variables for faces and Trirangle
        Triangle t = mesh.tris[i];
//        int a = t.getA();
//        int b = mesh.tris[i].getB();
//        int c = mesh.tris[i].getC();
//         cout << " [ " << a << "; " << b << "; " << c << "]" << endl;

        //find t0 containing b and c but not a
        int t0 = findTx(0, mesh.tris, i);

        //find t with c and a no b
        int t1 = findTx(1, mesh.tris, i);

        //find t with a and b no c
        int t2 = findTx(2, mesh.tris, i);

   //t.it= [t0,t1,t2];
        //n a ++
        //n b ++
        //n c ++
    }
    //save n's for each point in vector with right indices
    //save neighbor triangles as it[i] with ie[i]
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
void switchTx (int tIndex, int tx, vector<Triangle> tria,int t, int * countPointer){

    //gets vertex indices of initial Triangle
    int a = tria[t].getA();
    int b = tria[t].getB();
    int c = tria[t].getC();

    switch(tIndex) {
        case 0:
            //loop through all vertices of the current triangle and compares them with the vertices of the initial triangle
            for (int indV=0 ; indV <3; indV++ )
            {
                int v = tria[tx].iv[indV];
                // when point b or c matchess increase the counter
                if (v == b || v== c){
                    *countPointer++;
                    cout<< *countPointer << endl;
                }
            }
            break;
        case 1:
        //loop through all vertices of the current triangle and compares them with the vertices of the initial triangle
            for (int indV=0; indV <3; indV++ )
            {
                int v = tria[tx].iv[indV];
                // when point a or c matchess increase the counter
                if (v == a || v== c){
                    *countPointer++;
                    cout<< *countPointer << endl;
                }
            }
           break;
        case 2:
            for (int indV=0; indV <3; indV++ )
            {
                int v = tria[tx].iv[indV];
                // when point a or b matchess increase the counter
                if (v == a || v== b){
                    *countPointer++;
                    cout<< *countPointer << endl;
                }
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
int findTx (int tIndex, vector <Triangle> tria, int i){
    int IndexT;
    // loops again throiugh all triangles to compare them with initial triangle
    for (int tx=0; tx<tria.size(); tx++)
       {
           //counts amount of vertices in common, must be 2 in order to be adjacent triangle
           int count = 0;
           int * countPointer = &count;

           //if not the initial triangle
           if (tx != i){

               switchTx(tIndex, tx, tria, i,countPointer );
            }
           // if counter reaches, which means two common points the the index will be returned
           if (count ==2){
                //return index of adcaendt triangle;
                //save all 3 indexes of adjacent Triangles
           }
       }
           return 0;
}



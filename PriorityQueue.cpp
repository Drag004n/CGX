// Priority Queue Example with Data Structure for Fractions
// Author: MHB
// Date: 10.2017

#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

// class representing fractions of integers
class komplexZahl{
public:
    float real, img;

    komplexZahl(); // empty constructor
    komplexZahl( float real, float img); // constructor with initialization

    friend bool operator<( komplexZahl x, komplexZahl y); // less operator
};

komplexZahl::komplexZahl(){}; // empty constructor

komplexZahl::komplexZahl( float a, float b){ // constructor with initialization
    real = a;
    img = b;
}

bool operator<( komplexZahl x, komplexZahl y){ // less operator
    float absX;
    float absY;

    absX= sqrt(pow(x.real,2)+pow(x.img,2));
    absY= sqrt(pow(y.real,2)+pow(y.img,2));

    return absX < absY;
}

int main()
{
    const int n=5; // number of data elements
    int zaehler[n] = {4, 4, 4, 2, 2};
    int nenner[n]  = {5, 7, 9, 3, 6};
    komplexZahl b;

    // queue containing fractions
    priority_queue< komplexZahl, vector<komplexZahl>, less<komplexZahl> > Q;

    // fill queue with data
    cout << "The input list is:" << endl;
    for( int i=0; i<n; i++){
        b = komplexZahl( zaehler[i], nenner[i]);
        Q.push( b);
        cout << b.real << "/" << b.img << endl;
    }
    cout << endl;

    // print sorted list
    cout << "The sorted list is:" << endl;
    while( Q.size() > 0)
    {
        cout << Q.top().real << "/" << Q.top().img;
        cout << " = " << (float)Q.top().real / Q.top().img << endl;
        Q.pop(); // remove element from queue
    }
}

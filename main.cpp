#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>

#include "Node.hpp"
#include "Edge.hpp"
#include "Graph.hpp"
#include "FibHeap.hpp"

using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using namespace std;

int main(int argc, char* argv[]){
    /**
    if (argc < 2)
        return -1;
    /**/
    //ofstream f(argv[2], ios::app);
    /*
    Graph *g = new Graph();
    for(int i = 0; i < 8; i++)
        g->insertNode(i);
    g->insertEdges(0,2,6);
    g->insertEdges(0,1,14);
    g->insertEdges(0,3,10);
    g->insertEdges(0,4,5);
    g->insertEdges(1,3,3);
    g->insertEdges(2,4,4);
    g->insertEdges(3,5,8);
    g->insertEdges(4,6,9);
    g->insertEdges(4,5,2);
    g->insertEdges(5,7,15);
    g->print();

    auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    g->PrimsMTS();
    auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    g->print();
    /**/
    /*
    f   << "Binomni heap sa : " << N << " elemenata\n"
        << "Vreme za extractmin :" << extractmin - pocetak << "ms\n"
        << "Vreme za decrement key :" << deckey - extractmin << "ms\n"
        << "Vreme za delete node : " << delnode - deckey << "ms\n"
        << "Vreme za add : " << add - delnode << "ms\n"
        << "-----------------------------------------\n";
        */
    //f.close();
    FibHeap* f = new FibHeap();
    for(int i = 0; i < 10; i++)
        f->insert(new Node(i, 0));
    f->min->print(f->min);
    cout << endl;
    Node* min = f->extractMin();
    cout << endl;
    f->min->print(f->min);
    cout << endl;
    while (min = f->extractMin())
        cout << min->key << endl;

    return 1;
}
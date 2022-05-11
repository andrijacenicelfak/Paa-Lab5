#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

#include "Edge.hpp"
#include "FibHeap.hpp"
#include "Graph.hpp"
#include "Node.hpp"

using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using namespace std;

int main(int argc, char* argv[]) {
    /***
    Graph* g = new Graph();
    for (int i = 0; i < 8; i++) g->insertNode(i);
    g->insertEdges(0, 2, 6);
    g->insertEdges(0, 1, 14);
    g->insertEdges(0, 3, 10);
    g->insertEdges(0, 4, 5);
    g->insertEdges(1, 3, 3);
    g->insertEdges(2, 4, 4);
    g->insertEdges(3, 5, 8);
    g->insertEdges(4, 6, 9);
    g->insertEdges(4, 5, 2);
    g->insertEdges(5, 7, 15);
    g->print();
    auto start =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch())
            .count();
    g->KruskalsMTS();
    auto end =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch())
            .count();
    g->print();
    /**/
    if (argc < 3) return -1;

    stringstream ss(argv[1]);
    int N = 0;
    ss >> N;
    int E = 100 * N;

    Graph* g = new Graph();
    Node** nodes = new Node*[N];
    for (int i = 0; i < N; i++) {
        nodes[i] = g->insertNode(i);
    }
    for (int i = 0; i < E; i++) {
        g->insertEdges(nodes[rand() % N], nodes[rand() % N], rand() % N);
    }
    ofstream f(argv[2], ios::app);
    auto start =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch())
            .count();
    g->KruskalsMTS();
    auto end =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch())
            .count();
    // g->print();
    f << "Graph sa : " << N << " cvorova\n"
      << "I sa : " << E << " grana\n"
      << "Vreme za Kruskalov Algoritam :" << end - start << "ms\n"
      << "-----------------------------------------\n";
    f.close();

    /**
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
    /**/
    return 1;
}
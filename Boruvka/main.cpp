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
#include <vector>

using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using namespace std;
using namespace std;
class Edge {
   public:
    int weight;
    int dest;
    int src;
    Edge *next;

    Edge(int weight, int src, int dest) {
        this->weight = weight;
        this->dest = dest;
        this->src = src;
        this->next = NULL;
    }
};
class State {
   public:
    int parent;
    int rank;
    State(int parent, int rank) {
        this->parent = parent;
        this->rank = rank;
    }
};
class Graph {
   public:
    int vertices;
    vector<vector<Edge *> > graphEdge;
    Graph(int vertices) {
        this->vertices = vertices;

        for (int i = 0; i < this->vertices; ++i) {
            this->graphEdge.push_back(vector<Edge *>());
        }
    }
    void addEdge(int src, int dest, int w) {
        if (dest < 0 || dest >= this->vertices || src < 0 ||
            src >= this->vertices) {
            return;
        }
        // add node edge
        this->graphEdge.at(src).push_back(new Edge(w, src, dest));
        if (dest == src) {
            return;
        }
        this->graphEdge.at(dest).push_back(new Edge(w, dest, src));
    }
    void printGraph() {
        cout << "\n Graph Adjacency List ";
        for (int i = 0; i < this->vertices; ++i) {
            cout << " \n [" << i << "] :";
            for (int j = 0; j < this->graphEdge.at(i).size(); ++j) {
                cout << "  " << this->graphEdge.at(i).at(j)->dest;
            }
        }
    }
    int find(State **subsets, int i) {
        if (subsets[i]->parent != i) {
            subsets[i]->parent = this->find(subsets, subsets[i]->parent);
        }
        return subsets[i]->parent;
    }
    void findUnion(State **subsets, int x, int y) {
        int a = this->find(subsets, x);
        int b = this->find(subsets, y);
        if (subsets[a]->rank < subsets[b]->rank) {
            subsets[a]->parent = b;
        } else if (subsets[a]->rank > subsets[b]->rank) {
            subsets[b]->parent = a;
        } else {
            subsets[b]->parent = a;
            subsets[a]->rank++;
        }
    }
    void boruvkaMST() {
        int result = 0;
        int selector = this->vertices;
        State **subsets = new State *[this->vertices];
        Edge **cheapest = new Edge *[this->vertices];
        for (int v = 0; v < this->vertices; ++v) {
            subsets[v] = new State(v, 0);
        }
        while (selector > 1) {
            for (int v = 0; v < this->vertices; ++v) {
                cheapest[v] = NULL;
            }
            for (int k = 0; k < this->vertices; k++) {
                for (int i = 0; i < this->graphEdge.at(k).size(); ++i) {
                    int set1 =
                        this->find(subsets, this->graphEdge.at(k).at(i)->src);
                    int set2 =
                        this->find(subsets, this->graphEdge.at(k).at(i)->dest);
                    if (set1 != set2) {
                        if (cheapest[k] == NULL) {
                            cheapest[k] = this->graphEdge.at(k).at(i);
                        } else if (cheapest[k]->weight >
                                   this->graphEdge.at(k).at(i)->weight) {
                            cheapest[k] = this->graphEdge.at(k).at(i);
                        }
                    }
                }
            }
            for (int i = 0; i < this->vertices; i++) {
                if (cheapest[i] != NULL) {
                    int set1 = this->find(subsets, cheapest[i]->src);
                    int set2 = this->find(subsets, cheapest[i]->dest);
                    if (set1 != set2) {
                        selector--;
                        this->findUnion(subsets, set1, set2);
                        result += cheapest[i]->weight;
                    }
                }
            }
        }
    }
};

long long time() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
        .count();
}

int main(int argc, char *argv[]) {
    stringstream ss(argv[1]);
    int N = 0;
    ss >> N;
    int E = 100 * N;
    Graph *g = new Graph(N);
    int *got = new int[N];
    int p, n = 0;
    for (int i = 0; i < E; i++) {
        if (i < N)
            g->addEdge(i % N, (i + 1) % N, rand() % N);
        else
            g->addEdge(rand() % N, rand() % N, rand() % N);
    }
    ofstream f(argv[2], ios::app);
    auto start = time();
    g->boruvkaMST();
    auto end = time();
    f << "Graph sa : " << N << " cvorova\n"
      << "I sa : " << E << " grana\n"
      << "Vreme za Boruvkin Algoritam :" << end - start << "ms\n"
      << "-----------------------------------------\n";
    f.close();

    return 0;
}
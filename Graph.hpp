#pragma once
#include "Edge.hpp"
#include "FibHeap.hpp"
#include "Node.hpp"
#include "Stack.hpp"
class Graph {
   public:
    Node* start;
    int size;

    Graph() { start = nullptr; }
    ~Graph() { delete[] start; }
    Node* findNode(int key);
    Edge* findEdge(int keySrc, int keyDest);
    Node* insertNode(int key);
    bool insertEdges(int keySrc, int keyDest, int weight);
    bool insertEdges(Node* nodeSrc, Node* nodeDest, int weight);
    bool insertEdge(int keySrc, int keyDest, int weight);  //
    void deleteNodeEdges(Node* dest);
    void deleteEgdesToNode(Node* dest);  //
    bool deleteEdges(int keySrc, int keyDest);
    bool deleteEdge(int keySrc, int keyDest);  //
    bool deleteNode(int key);
    void print();
    void printStatus();

    void setStatusForAllNodes(int status);

    void PrimsMTS();
    void KruskalsMTS();
};

Node* Graph::findNode(int key) {
    Node* node = start;
    while (node != nullptr && node->key != key) node = node->link;
    return node;
}
Edge* Graph::findEdge(int keySrc, int keyDest) {
    Node* src = findNode(keySrc);
    Edge* e = src->adj;
    while (e != nullptr && e->dest->key != keyDest) e = e->link;
    return e;
}
Node* Graph::insertNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->link = start;
    this->start = node;
    return node;
}
bool Graph::insertEdges(int keySrc, int keyDest, int weight) {
    Node* nodeSrc = nullptr;
    Node* nodeDest = nullptr;
    Node* node = start;
    while (node != nullptr && (nodeSrc == nullptr || nodeDest == nullptr)) {
        if (node->key == keySrc)
            nodeSrc = node;
        else if (node->key == keyDest) {
            nodeDest = node;
        }
        node = node->link;
    }
    if (nodeSrc == nullptr || nodeDest == nullptr) return false;
    Edge* std = new Edge(nodeDest, nodeSrc->adj, weight);
    std->src = nodeSrc;
    nodeSrc->adj = std;

    Edge* dts = new Edge(nodeSrc, nodeDest->adj, weight);
    dts->src = nodeDest;
    nodeDest->adj = dts;

    return true;
}
bool Graph::insertEdges(Node* nodeSrc, Node* nodeDest, int weight) {
    if (nodeSrc == nullptr || nodeDest == nullptr) return false;
    Edge* std = new Edge(nodeDest, nodeSrc->adj, weight);
    std->src = nodeSrc;
    nodeSrc->adj = std;

    Edge* dts = new Edge(nodeSrc, nodeDest->adj, weight);
    dts->src = nodeDest;
    nodeDest->adj = dts;

    return true;
}
void Graph::deleteNodeEdges(Node* dest) {
    Node* ptr = start;
    delete[] dest->adj;
    dest->adj = nullptr;
    while (ptr != nullptr) {
        Edge* pEdgePrev = nullptr;
        Edge* pEdge = ptr->adj;
        while (pEdge != nullptr && pEdge->dest != dest) {
            pEdgePrev = pEdge;
            pEdge = pEdge->link;
        }
        if (pEdge != nullptr) {
            if (pEdgePrev == nullptr)
                ptr->adj = pEdge->link;
            else
                pEdgePrev->link = pEdge->link;
            delete pEdge;
        }
        ptr = ptr->next;
    }
}
bool Graph::deleteEdges(int keySrc, int keyDest) {
    Node* src = findNode(keySrc);
    Node* dest = findNode(keyDest);
    if (dest == nullptr || src == nullptr) return false;

    Edge *e = src->adj, *prevE = nullptr;
    while (e != nullptr && e->dest != dest) {
        prevE = e;
        e = e->link;
    }
    if (prevE == nullptr) {
        src->adj = e->link;
    } else {
        prevE->link = e->link;
    }
    if (e != nullptr) delete e;

    e = dest->adj;
    prevE = nullptr;
    while (e != nullptr && e->dest != src) {
        prevE = e;
        e = e->link;
    }
    if (prevE == nullptr) {
        src->adj = e->link;
    } else {
        prevE->link = e->link;
    }
    if (e != nullptr) delete e;
}
bool Graph::deleteNode(int key) {
    Node* prev = nullptr;
    Node* node = start;
    while (node != nullptr && node->key != key) {
        prev = node;
        node = node->link;
    }
    if (node == nullptr) return false;
    deleteNodeEdges(node);
    if (node == start) {
        start = start->link;
    } else {
        prev->link = node->link;
    }
    delete node;
    return true;
}

void Graph::print() {
    Node* ptr = start;
    while (ptr != nullptr) {
        cout << ptr->key << " -> ";
        Edge* pEdge = ptr->adj;
        while (pEdge != nullptr) {
            if (pEdge->mark == 1) cout << "*";
            cout << pEdge->dest->key << " | ";
            pEdge = pEdge->link;
        }
        cout << endl;
        ptr = ptr->link;
    }
}
void Graph::printStatus() {
    Node* ptr = start;
    while (ptr != nullptr) {
        cout << ptr->status << " -> ";
        Edge* pEdge = ptr->adj;
        while (pEdge != nullptr) {
            cout << pEdge->dest->status << " | ";
            pEdge = pEdge->link;
        }
        cout << endl;
        ptr = ptr->link;
    }
}
void Graph::setStatusForAllNodes(int status) {
    Node* node = start;
    while (start != nullptr) {
        node->status = status;
        node = node->link;
    }
}
void Graph::PrimsMTS() {
    FibHeap* f = new FibHeap();

    // Cuvamo kljuc
    start->status = start->key;
    start->key = 0;
    f->insert(start);

    Node* node = start->link;
    while (node != nullptr) {
        node->status = node->key;
        node->key = 2147483647;
        f->insert(node);
        node = node->link;
    }
    Edge* pom;
    node = f->extractMin();

    while (node != nullptr) {
        // printStatus();
        // cout << node->status << " : " << node->key << endl;
        Edge* e = node->adj;
        if (node != start) node->C = 'D';
        while (e != nullptr) {
            if (e->dest->C != 'D' && e->dest->key > e->weight) {
                f->setKey(e->dest, e->weight);
                pom = e->dest->adj;
                while (pom != nullptr) {
                    pom->mark = 0;
                    if (pom->dest == node) pom->mark = 1;
                    pom = pom->link;
                }
            }

            e = e->link;
        }
        node = f->extractMin();
    }
    /**
    node = start;
    while (node != nullptr) {
        node->key = node->status;
        node = node->link;
    }
    /**/
    /***
    // print();
    node = start;
    Edge *e, *p = nullptr;
    while (node != nullptr) {
        e = node->adj;
        p = nullptr;
        while (e != nullptr && e->mark != 1) {
            p = e;
            e = e->link;
        }
        if (e == node->adj) {
            delete node->adj->link;
        } else if (e != nullptr) {
            p->link = e->link;
            delete node->adj;
            node->adj = e;
        } else {
            // node->key = node->status;
            node = node->link;
            continue;
        }
        e->link = nullptr;

        // node->key = node->status;
        node = node->link;
    }
    // print();
    /**/
}

void Graph::KruskalsMTS() {
    FibHeap* heap = new FibHeap();
    Node* node = start;
    int i = 0;
    while (node != nullptr) {
        Edge* e = node->adj;
        while (e != nullptr) {
            e->mark = 0;
            Node* edgeNode = new Node();
            edgeNode->adj = e;
            edgeNode->key = e->weight;
            heap->insert(edgeNode);
            e = e->link;
        }
        node->status = i++;
        node = node->link;
    }
    int br;
    br = 0;
    Node* en = nullptr;
    Stack<Node*> stack(size);
    while ((en = heap->extractMin()) && br < size) {
        if (en->adj->src->status != en->adj->dest->status) {
            en->adj->mark = 1;
            stack.push(en->adj->dest);
            int ost = en->adj->dest->status;
            int nst = en->adj->src->status;
            Node* nn;
            Edge* ne;
            while (!stack.isEmpty()) {
                nn = stack.pop();
                nn->status = nst;
                ne = nn->adj;
                while (ne != nullptr) {
                    if (ne->dest->status == ost) stack.push(ne->dest);
                    ne = ne->link;
                }
            }
            br++;
        }
    }
}
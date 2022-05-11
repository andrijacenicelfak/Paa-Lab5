#pragma once
#include <iostream>

#include "Edge.hpp"

using namespace std;
class Edge;
class Node {
   public:
    Node *parent, *child, *prev, *next, *link;
    Edge* adj;
    int key, degree, status;
    char C;
    Node(int key, int degree) {
        this->key = key;
        this->degree = degree;
        status = 0;
        parent = child = prev = next = nullptr;
        link = nullptr;
        next = nullptr;
        child = nullptr;
        parent = nullptr;
        adj = nullptr;
    }
    Node() {
        key = 0;
        degree = 0;
        status = 0;
        parent = child = prev = next = nullptr;
        link = nullptr;
        next = nullptr;
        child = nullptr;
        parent = nullptr;
        adj = nullptr;
    }
    ~Node() { /**/
        if (child != nullptr) delete child;
        if (prev != nullptr) delete prev;
        if (next != nullptr) delete next;
    }
    void setParent(Node* p) {
        if (parent == p) return;
        parent = p;
        next->setParent(p);
    }
    void print(Node* node) {
        cout << key << " -> ";
        if (node != next)
            next->print(node);
        else
            cout << next->key;
    }
    bool checkNeighbour(Node* st) {
        if (prev == nullptr || next == nullptr) return false;
        if (next == st) return true;
        return next->checkNeighbour(st);
    }
    // void setStatusRecursive(int st);
};
/**
void Node::setStatusRecursive(int st) {
    Edge* e = adj;
    int ost = status;
    status = status;
    while (e != nullptr) {
        if (e->dest->status == ost) e->dest->setStatusRecursive(st);
        e = e->link;
    }
}
/**/
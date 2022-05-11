#pragma once
#include "Node.hpp"
class Node;
class Edge {
   public:
    int weight;
    Edge* link;
    Node *dest, *src;
    int mark;

    Edge() {
        weight = 0;
        link = nullptr;
        mark = 0;
        dest = nullptr;
    }
    Edge(Node* dest, Edge* link, int weight) {
        this->dest = dest;
        this->link = link;
        this->weight = weight;
        mark = 0;
    }
};
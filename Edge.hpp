#pragma once
#include "Node.hpp"

class Edge{
    public:
    double weight;
    Edge* link;
    Node* dest;
    Edge(){
        weight = 0;
        link = nullptr;
        dest = nullptr;
    }

    Edge(Node* dest, Edge* link, double weight){
        this->dest = dest;
        this->link = link;
        this->weight = weight;
    }
};
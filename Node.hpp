#pragma once
#include "Edge.hpp"
class Node{
    public:
    Node *parent, *child, *prev, *next, *link;
    Edge* adj;
    int key, degree, status;
    Node(int key, int degree){
        this->key = key;
        this->degree = degree;
        status = 0;
        parent = child = prev = next = nullptr;
    }

    ~Node(){/**/
        if(child != nullptr)
            delete child;
        if(prev != nullptr)
            delete prev;
        if(next != nullptr)
            delete next;
    }
};
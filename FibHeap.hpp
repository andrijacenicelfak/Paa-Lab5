#pragma once
#pragma once
#include <cmath>
#include <iostream>

#include "Node.hpp"
using namespace std;
class FibHeap {
    int size;

   public:
    Node* min;
    FibHeap() {
        min = nullptr;
        size = 0;
    }
    ~FibHeap() {
        if (min != nullptr) delete min;
    }
    void insert(Node* node);
    void link(Node* n1, Node* n2, bool zameni);
    Node* consolidateTree(Node* node);
    Node* findMin(Node* node);
    Node* unija(Node* n1, Node* n2);  // ne menja parente ni jednog ni drugog
    void setParent(Node* child, Node* parent);
    Node* extractMin();
    Node* pretrazi(int key, Node* node);  // nullptr da bi proslo celo stablo
    void setKey(int key, int vrednost);
    void setKey(Node* node, int vrednost);
    void brisiNode(int key);
};
void FibHeap::insert(Node* node) {
    if (min == nullptr) {
        min = node;
        min->next = min;
        min->prev = min;
    } else {
        Node* minprev = min->prev;
        minprev->next = node;
        node->next = min;
        min->prev = node;
        node->prev = minprev;
        if (node->key < min->key) min = node;
    }
    node->parent = nullptr;
    size++;
}
void FibHeap::link(Node* n1, Node* n2, bool zameni) {
    if (n1 == nullptr || n2 == nullptr) return;

    /**
    n1->print(n1);
    cout << '\n';
    n2->print(n2);
    cout << '\n';
    /**/
    if (!(n1->next == n2 || n1->prev == n2 || n2->next == n1 ||
          n2->prev == n1) &&
        zameni) {
        Node* n1prev = n1->prev;
        Node* n1next = n1->next;

        Node* n2prev = n2->prev;
        Node* n2next = n2->next;

        n1prev->next = n2;
        n1next->prev = n2;

        n2->prev = n1prev;
        n2->next = n1next;

        n2prev->next = n1;
        n2next->prev = n1;

        n1->next = n2next;
        n1->prev = n2prev;
    }
    /**
    n1->print(n1);
    cout << '\n';
    n2->print(n2);
    cout << '\n';
    /**/
    n2->prev->next = n2->next;
    n2->next->prev = n2->prev;
    n2->parent = n1;
    if (n1->child == nullptr) {
        n2->prev = n2;
        n2->next = n2;
    } else {
        n2->next = n1->child->next;
        n2->prev = n1->child;
        n2->next->prev = n2;
        n2->prev->next = n2;
    }
    n1->child = n2;
    n1->degree++;  // Broj potomaka => direktnih ili ukupno? Ostavljam ovako gde
                   // je to broj direktnih potomaka
}
Node* FibHeap::consolidateTree(Node* node) {
    if (node == nullptr) return nullptr;
    int vel = (int)log2(size) + 1;
    vel *= 2;
    Node** degree = new Node*[vel];

    for (int i = 0; i < vel; i++) degree[i] = nullptr;

    node = min;
    if (node == nullptr) {
        return nullptr;
    }
    bool done = false;
    int st = node->degree;
    while (!done) {
        st = node->degree;
        if (degree[st] == nullptr) {
            degree[st] = node;
            node = node->next;
        } else if (degree[node->degree] != node) {
            if (degree[st]->key < node->key) {
                link(degree[st], node, true);
                node = degree[st];
            } else {
                link(node, degree[st], false);
            }
            degree[st] = nullptr;
        } else if (node == degree[st]) {
            done = true;
        }
    }
    min = node;
    return findMin(node);
}
Node* FibHeap::findMin(Node* node) {
    if (node == nullptr) return nullptr;
    Node* st = node;
    int mink = node->key;
    while (node->next != st) {
        if (node->next->key < mink) {
            min = node->next;
            mink = min->key;
        }
        node = node->next;
    }
    /**
    min->print(min);
    cout << endl;
    /**/
    return min;
}
Node* FibHeap::unija(Node* n1, Node* n2) {
    if (n1 == nullptr) return n2;
    if (n2 == nullptr) return n1;

    n1->next->prev = n2->prev;
    n2->prev->next = n1->next;

    n1->next = n2;
    n2->prev = n1;
    return n1;
}
void FibHeap::setParent(Node* child, Node* parent) {
    while (child->parent != parent) {
        child->parent = parent;
        child = child->next;
    }
}
Node* FibHeap::extractMin() {
    if (min == nullptr) return nullptr;
    if (min->next == min) {
        Node* m = min;
        if (min->child != nullptr) min->child->setParent(nullptr);
        min = min->child;
        m->next = nullptr;
        m->prev = nullptr;
        m->child = nullptr;
        findMin(min);
        return m;
    }
    Node* prev = min->prev;
    Node* next = min->next;

    prev->next = next;
    next->prev = prev;
    min->prev = nullptr;
    min->next = nullptr;
    Node* ret = min;
    min = next;

    if (ret->child != nullptr) {
        Node* child = ret->child;
        child->setParent(nullptr);
        min = unija(min, child);
    }
    consolidateTree(min);
    return ret;
}
Node* FibHeap::pretrazi(int key, Node* node) {
    Node* ret = nullptr;
    if (node == nullptr && min->key != key)
        node = min->next;
    else if (min->key == key)
        return min;

    while (ret != nullptr && node != min) {
        if (node->key < key && node->child != nullptr)
            ret = pretrazi(key, node->child);
        node = node->next;
    }
    return ret;
}
void FibHeap::setKey(int key, int vrednost) {
    Node* node = pretrazi(key, nullptr);
    if (node == nullptr) return;  // NIJE NASLO ELEMENT
    node->key = vrednost;
    while (node->parent != nullptr && node->parent->key > node->key) {
        key = node->parent->key;
        node->parent->key = node->key;
        node->key = key;
        node = node->parent;
    }
}
void FibHeap::setKey(Node* node, int vrednost) {
    if (node == nullptr) return;  // NO
    if (node->next == nullptr) {
        node->next = node;
        node->prev = node;
    }
    if (node->parent != nullptr) {
        node->parent->child = nullptr;
        node->parent->degree = 0;
        setParent(node, nullptr);
    }
    node->key = vrednost;
    findMin(unija(min, node));
}
/**
void FibHeap::setKey(Node* node, int vrednost) {
    if (node == nullptr) return;  // NIJE NASLO ELEMENT
    int key = node->key;
    node->key = vrednost;
    Node *n1prev, *n1next, *n2prev, *n2next;
    Node *n1, *n2;
    Edge* pom;
    while (node->parent != nullptr && node->parent->key > node->key) {
        n1 = node;
        n2 = node->parent;

        n1prev = n1->prev;
        n1next = n1->next;

        n2prev = n2->prev;
        n2next = n2->next;

        n1prev->next = n2;
        n1next->prev = n2;
        n2->next = n1next;
        n2->prev = n1prev;

        n2prev->next = n1;
        n2next->prev = n1;
        n1->next = n2next;
        n1->prev = n2prev;

        n2prev = n2->parent;
        n2next = n1;

        n1prev = n2;
        n1next = n1->child;

        if (n2prev != nullptr) {
            n2prev->child = n1;
        }
        n1->parent = n2prev;
        n1->child = n2;
        n2->parent = n1;

        n2->child = n1next;
        if (n1next != nullptr) n1next->parent = n2;

        int deg = n1->degree;
        n1->degree = n2->degree;
        n2->degree = deg;
    }
    min = findMin(min);
}/**/
void FibHeap::brisiNode(int key) {
    size--;
    Node* node = pretrazi(key, nullptr);
    if (node == nullptr) return;  // NIJE NASLO CVOR!
    Node* child = node->child;
    setParent(child, nullptr);
    unija(child, min);
    node->prev->next = node->next;
    node->next->prev = node->prev;
    if (node == min) findMin(node->next);
    node->prev = nullptr;
    node->next = nullptr;
    node->child = nullptr;
    delete node;
}
/**/
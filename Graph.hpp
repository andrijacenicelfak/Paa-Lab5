#pragma once
#include "Node.hpp"
#include "Edge.hpp"

class Graph{
    public:
    Node* start;
    int size;

    Graph(){
        start = nullptr;
    }
    ~Graph(){
        delete[] start;
    }
    Node* findNode(int key);
    Edge* findEdge(int keySrc, int keyDest);
    void insertNode(int key);
    bool insertEdge(int keySrc, int keyDest, double weight);
    void deleteEdgeToNode(Node* dest);
    bool deleteEdge(int keySrc, int keyDest);
    bool deleteNode(int key);
    void print();

    void setStatusForAllNodes(int status);
};

Node* Graph::findNode(int key){
    Node* node = start;
    while(node != nullptr && node->key != key)
        node = node->link;
    return ptr;
}
Node* Graph::findEndge(int keySrc, int keyDest){
    Node* src = findNode(keySrc);
    Edge* e = src->adj;
    while(e != nullptr && e->dest->key != keyDest)
        e = e->next;
    return e;
}
void Graph::insertNode(int key){
    Node * node = new Node();
    node->key = key;
    node->link = start;
    start = link;
}
bool Graph::insertEdge(int keySrc, int keyDest, double weight){
    Node* nodeSrc = nullptr;
    Node* nodeDest = nullptr;
    Node* node = start;
    while(node != nullptr && (nodeSrc == nullptr || nodeDest == nullptr)){
        if(node->key == keySrc)
            nodeSrc = node;
        else if(node->key == keyDest){
            nodeDest = node;
        }
        node = node->link;
    }
    if(nodeSrc == nullptr || nodeDest == nullptr)
        return false;
    Edge* std = new Edge(nodeDest, nodeSrc->adj, weight);
    nodeSrc->adj = std;

    Edge* dts = new Edge(nodeSrc, nodeDest->adj, weight);
    nodeDest->adj = dts;

    return true;
}
void Graph::deleteEdgeToNode(Node* dest){
    Node* ptr = start;
    delete[] dest->adj;
    dest->adj = nullptr;
	while (ptr != nullptr)
	{
		Edge* pEdgePrev = nullptr;
		Edge* pEdge = ptr->adj;
		while (pEdge != nullptr && pEdge->dest != dest) {
			pEdgePrev = pEdge;
			pEdge = pEdge->link;
		}
		if (pEdge != nullptr)
		{
			if (pEdgePrev == nullptr)
				ptr->adj = pEdge->link;
			else
				pEdgePrev->link = pEdge->link;
            delete pEdge;
		}
		ptr = ptr->next;
	}
}
bool Graph::deleteEdge(int keySrc, int keyDest){
    Node* src = findNode(keySrc);
    Node* dest = findNode(keyDest);
    if(dest == nullptr || src == nullptr)
        return false;

    Edge* e = src->adj, prevE = nullptr;
    while(e != nullptr && e->dest != dest){
        prevE = e;
        e = e->link;
    }
    if(prevE == nullptr){
        src->adj = e->link;
    }else{
        prevE->link = e->link;
    }
    if(e != nullptr)
        delete e;

    e = dest->adj;
    prevE = nullptr;
    while(e != nullptr && e->dest != src){
        prevE = e;
        e = e->link;
    }
    if(prevE == nullptr){
        src->adj = e->link;
    }else{
        prevE->link = e->link;
    }
    if(e != nullptr)
        delete e;
}
bool deleteNode(int key){
    Node* prev = nullptr;
    node* node = start;
    while(node != nullptr && node->key != key){
        prev = node;
        node = node->link;
    }
    if(node == nullptr)
        return false;
    deleteEdgeToNode(node);
    if(node == start){
        start = start->link;
    }else{
        prev->link = node->link;
    }
    delete node;
    return true;
}

void Graph::print(){
    Node* ptr = start;
	while (ptr != nullptr)
	{
		cout << ptr->key << " -> ";
		Edge* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			cout << pEdge->dest->key << " | ";
			pEdge = pEdge->link;
		}
		cout << endl;
		ptr = ptr->next;
	}
}
void Graph::setStatusForAllNodes(int status){
    Node* node = start;
    while(start != nullptr){
        node->status = status;
        node = node->link;
    }
}

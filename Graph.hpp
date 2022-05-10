#pragma once
#include "Node.hpp"
#include "Edge.hpp"
#include "FibHeap.hpp"
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
    bool insertEdges(int keySrc, int keyDest, int weight);
    bool insertEdge(int keySrc, int keyDest, int weight);//
    void deleteNodeEdges(Node* dest);
    void deleteEgdesToNode(Node* dest);//
    bool deleteEdges(int keySrc, int keyDest);
    bool deleteEdge(int keySrc, int keyDest);//
    bool deleteNode(int key);
    void print();
    void printStatus();

    void setStatusForAllNodes(int status);

    void PrimsMTS();

    void Kruskal();
};

void Graph::Kruskal() {

}

Node* Graph::findNode(int key){
    Node* node = start;
    while(node != nullptr && node->key != key)
        node = node->link;
    return node;
}
Edge* Graph::findEdge(int keySrc, int keyDest){
    Node* src = findNode(keySrc);
    Edge* e = src->adj;
    while(e != nullptr && e->dest->key != keyDest)
        e = e->link;
    return e;
}
void Graph::insertNode(int key){
    Node * node = new Node();
    node->key = key;
    node->link = start;
    this->start = node;
}
bool Graph::insertEdges(int keySrc, int keyDest, int weight){
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
    std->link = nodeSrc->adj;
    nodeSrc->adj = std;

    Edge* dts = new Edge(nodeSrc, nodeDest->adj, weight);
    nodeDest->adj = dts;

    return true;
}
void Graph::deleteNodeEdges(Node* dest){
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
bool Graph::deleteEdges(int keySrc, int keyDest){
    Node* src = findNode(keySrc);
    Node* dest = findNode(keyDest);
    if(dest == nullptr || src == nullptr)
        return false;

    Edge* e = src->adj, *prevE = nullptr;
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
bool Graph::deleteNode(int key){
    Node* prev = nullptr;
    Node* node = start;
    while(node != nullptr && node->key != key){
        prev = node;
        node = node->link;
    }
    if(node == nullptr)
        return false;
    deleteNodeEdges(node);
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
		ptr = ptr->link;
	}
}
void Graph::printStatus() {
    Node* ptr = start;
    while (ptr != nullptr)
    {
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
void Graph::setStatusForAllNodes(int status){
    Node* node = start;
    while(start != nullptr){
        node->status = status;
        node = node->link;
    }
}
void Graph::PrimsMTS(){
    FibHeap* f = new FibHeap();

    //Cuvamo kljuc
    start->status = start->key;
    start->key = 0;
    f->insert(start);

    Node* node = start->link;
    while(node != nullptr){
        node->status = node->key;
        node->key = 2147483647;
        f->insert(node);
        node = node->link;
    }
    Edge* pom;
    node = f->extractMin();
    cout << node->status << " : " << node->key << endl;

    while(node != nullptr){
        //printStatus();
        Edge* e = node->adj;
        while(e != nullptr){
            if(e->dest->key > e->weight){
                f->setKey(e->dest, e->weight);
                pom = e->dest->adj;
                while(pom != nullptr){
                    pom->mark = 0;
                    if(pom->dest == node)
                        pom->mark = 1;
                    pom = pom->link;
                }
            }
            
            e = e->link;
        }
        node = f->extractMin();
        cout << node->status << " : " << node->key << endl;
    }

    /**/
    node = start;
    Edge* e, *p = nullptr;
    while(node != nullptr){
        e = node->adj;
        p = nullptr;
        while(e != nullptr && e->mark != 1){
            p = e;
            e = e->link;
        }
        if(e == node->adj){
            delete node->adj->link;
        }else if(e != nullptr) {
            p->link = e->link;
            delete node->adj;
            node->adj = e;
        }
        else {
            //node->key = node->status;
            node = node->link;
            continue;
        }
        e->link = nullptr;

        //node->key = node->status;
        node = node->link;
    }
    print();
    /**/
    //Ne znam da li da treba da pamtim povratne grane??? Zbog slike ne???!?!?

}
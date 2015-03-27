/*
 * Graph.h
 *
 *  Created on: Dec 13, 2014
 *      Author: pinogal
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <unordered_map>
#include <vector>
#include <iostream>

#include "Vertex.h"

using namespace std;

/*
 * Adjacency list representation
 */
class Graph {
private:
    unordered_map<Vertex*, vector<Vertex*>*,
        hash_Vertex, equal_Vertex>* adj_list;
    Vertex* head;

public:
    Graph();
    virtual ~Graph();

    int getNumberOfEdges(Vertex* v);
    int getLength();
    Vertex* getHead();
    void setHead(Vertex* v);
    void add_edge (Vertex* from, Vertex* to);
    void print();
//    map<Vertex*, vector<Vertex*>*>* get_adj_list();
};

#endif /* GRAPH_H_ */

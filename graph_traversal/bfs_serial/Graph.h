/*
 * Copyright (C) 2015 Computer Architecture and Parallel Systems Laboratory (CAPSL)
 *
 * Original author: Sergio Pino
 * E-Mail: sergiop@udel.edu
 *
 * License
 *
 * Redistribution of this code is allowed only after an explicit permission is
 * given by the original author or CAPSL and this license should be included in
 * all files, either existing or new ones. Modifying the code is allowed, but
 * the original author and/or CAPSL must be notified about these modifications.
 * The original author and/or CAPSL is also allowed to use these modifications
 * and publicly report results that include them. Appropriate acknowledgments
 * to everyone who made the modifications will be added in this case.
 *
 * Warranty
 *
 * THIS CODE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES THAT
 * THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR
 * PURPOSE OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE
 * OF THE COVERED CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN
 * ANY RESPECT, YOU (NOT THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME
 * THE COST OF ANY NECESSARY SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER
 * OF WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS LICENSE. NO USE OF ANY
 * COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER THIS DISCLAIMER.
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <unordered_map>
#include <vector>
#include <iostream>
#include <cmath>

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
    vector<Vertex*>* getEdges(Vertex* v);
    Vertex* getVertex(Vertex* v);
    int getLength();
    Vertex* getHead();
    void setHead(Vertex* v);
    void add_edge (Vertex* from, Vertex* to);
    void print();
    void resetColors();
    unordered_map<Vertex*, vector<Vertex*>*,
            hash_Vertex, equal_Vertex>* get_adj_list();
};

#endif /* GRAPH_H_ */

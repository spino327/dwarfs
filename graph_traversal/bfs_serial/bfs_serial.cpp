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

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <stdio.h>
#include <time.h>

#include <queue>
#include <vector>
#include <map>
#include <set>

#include "Graph.h"
#include "Vertex.h"

using namespace std;

static const char* USAGE = "./bfs_serial <graph_file>";

bool loadData(const char* fn, Graph** graph) {

    // checks the file name
    if (!fn)
        return false;

    ifstream in{fn};
    if (not in) {
        cerr << "error opening ifstream for " << fn << "\n";
    } else {
        string line_buff;
        istringstream iss;

        bool setHead = false;

        Graph* tmp_graph = new Graph();

        //reading the list of vertices and edges
        while (getline(in, line_buff)) {
            iss.clear();
            iss.str(line_buff);

            int from_id, to_id;
            // vertex
            iss >> from_id;
            Vertex* from = new Vertex(from_id);

            if (!setHead) {
                tmp_graph->setHead(from);
                setHead = true;
                cerr << "setting head to " << tmp_graph->getHead()->getID() << "\n";
            }

            while (iss >> to_id)
                tmp_graph->add_edge(from, new Vertex(to_id));
        }

        *graph = tmp_graph;
        in.close();

        return true;
    }

    return false;
}

void bfs1 (Graph* graph) {

    queue<Vertex*> Q;

    map<int, Vertex*>* ord_adj_list = new map<int, Vertex*>();
    for (auto vertex : *graph->get_adj_list()) {
        ord_adj_list->insert( pair<int, Vertex*> (vertex.first->getID(), vertex.first) );
    }

    for (auto vertex : *ord_adj_list) {

        if (vertex.second->getColor() != 0)
            continue;

        vertex.second->setColor(1);
        Q.push(vertex.second);

        //while queue not empty
        while (!Q.empty()) {
            //take the first element
            Vertex* v = Q.front();
            Q.pop();

            for (Vertex* to : *graph->getEdges(v)) {
                Vertex* u = graph->getVertex(to);

                if (u->getColor() == 0) {
                    u->setColor(1);
                    u->setParent(v);
                    Q.push(u);
                }
            }
        }
    }

    ord_adj_list->clear();
}

int main(int argc, char **argv) {

    // reading the user parameters
    if (argc != 2) {
        cout << USAGE;
        return -1;
    }

    Graph *graph;// = new Graph();
    char* input_fname = argv[1];

    if (!loadData(input_fname, &graph)) {
        cerr << "couldn't load the graph from the input file!\n";
        return -1;
    }

    // iterative
    clock_t init = clock();
    bfs1(graph);
    cout << "bfs1 = " << (double)(clock()-init)/CLOCKS_PER_SEC << " sec\n";

    // print graph
//    graph->print();

    return 0;
}

/*
 * dfs_serial.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: pinogal
 */

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

#include <stdio.h>

#include <time.h>
#include <deque>
#include <vector>
#include <map>

#include "Graph.h"
#include "Vertex.h"

using namespace std;

static const char* USAGE = "./dfs_serial <graph_file>";

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

void iterative_dfs (Graph* graph) {

    deque<Vertex*> dq;

    map<int, Vertex*>* ord_adj_list = new map<int, Vertex*>();
    for (auto vertex : *graph->get_adj_list()) {
        ord_adj_list->insert( pair<int, Vertex*> (vertex.first->getID(), vertex.first) );
    }

    for (auto vertex : *ord_adj_list) {

        if (vertex.second->getColor() != 0)
            continue;

        cout << "-\n";
        dq.push_front(vertex.second);

        //while deque not empty
        while (!dq.empty()) {
            //take the first element
            Vertex* current = dq.front();
            dq.pop_front();

            if (current->getColor() == 0) {
                cout << current->getID() << "\n";

                // set label as discovered
                current->setColor(current->getColor() + 1);
                deque<Vertex*>::iterator it = dq.begin();
                for (Vertex* to : *graph->getEdges(current)) {
                    Vertex* real = graph->getVertex(to);
                    it = dq.insert(it, real);
                    it++;
                }
            }
        }
    }

    ord_adj_list->clear();
}

void dfs_visit (Graph* g, Vertex* u) {
    u->setColor(1);
    cout << u->getID() << "\n";
    for (Vertex* v : *g->getEdges(u)) {
        v = g->getVertex(v);
        if (v->getColor() == 0)
            dfs_visit(g, v);
    }
    u->setColor(2);
}

void recursive_dfs (Graph* graph) {

    map<int, Vertex*>* ord_adj_list = new map<int, Vertex*>();
    for (auto vertex : *graph->get_adj_list()) {
        ord_adj_list->insert( pair<int, Vertex*> (vertex.first->getID(), vertex.first) );
    }

    for (auto vertex : *ord_adj_list) {

        if (vertex.second->getColor() == 0) {
            cout << "-\n";
            dfs_visit(graph, vertex.second);
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

    // print graph
    graph->print();

    // iterative
    clock_t init = clock();
    iterative_dfs(graph);
    cout << "Iterative_dfs = " << (double)(clock()-init)/CLOCKS_PER_SEC << " sec\n";

    // reset Colors
    graph->resetColors();

    init = clock();
    recursive_dfs(graph);
    cout << "Recursive_dfs = " << (double)(clock()-init)/CLOCKS_PER_SEC << " sec\n";

    return 0;
}

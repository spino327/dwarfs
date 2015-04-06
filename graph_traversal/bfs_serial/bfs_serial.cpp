/*
 * bfs_serial.cpp
 *
 */

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

#include <stdio.h>

#include <time.h>
#include <queue>
#include <vector>
#include <map>

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

void bfs (Graph* graph) {

    queue<Vertex*> Q;

    map<int, Vertex*>* ord_adj_list = new map<int, Vertex*>();
    for (auto vertex : *graph->get_adj_list()) {
        ord_adj_list->insert( pair<int, Vertex*> (vertex.first->getID(), vertex.first) );
    }

    for (auto vertex : *ord_adj_list) {

        if (vertex.second->getColor() != 0)
            continue;

        cout << "-\n";
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
    bfs(graph);
    cout << "bfs = " << (double)(clock()-init)/CLOCKS_PER_SEC << " sec\n";

    // print graph
    graph->print();

    return 0;
}

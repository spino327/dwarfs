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
#include <stack>
#include <queue>
#include <vector>
#include <map>

#include "Graph.h"
#include "Vertex.h"

using namespace std;

static const char* USAGE = "./dfs_serial <graph_file>";

bool loadData(const char* fn, Graph** graph) {

    string y;
    // checks the file name
    if (!fn)
        return false;

    ifstream in{fn};
    if (not in) {
        perror(strcat("error opening ifstream for ", fn));
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

        (*graph)->print();

        in.close();

        return true;
    }

    return false;
}

int main(int argc, char **argv) {

    // reading the user parameters
    if (argc != 2) {
        cout << USAGE;
        exit(-1);
    }

    Graph *graph;// = new Graph();
    char* input_fname = argv[1];

    if (!loadData(input_fname, &graph)) {
        perror ("couldn't load the graph from the input file!");
    }

    stack<Vertex*> stack;

    map<int, Vertex*>* ord_adj_list = new map<int, Vertex*>();
    for (auto vertex : *graph->get_adj_list()) {
        ord_adj_list->insert( pair<int, Vertex*> (vertex.first->getID(), vertex.first) );
    }

    for (auto vertex : *ord_adj_list) {

        if (vertex.second->getColor() != 0)
            continue;

        vertex.second->setColor(vertex.second->getColor() + 1);
        stack.push(vertex.second);
        //while stack not empty
        int tabs = 0;
        while (!stack.empty()) {

            //take the first element
            Vertex* current = stack.top();

            //for all edges of current vertex
            bool visited = false;
            for (int i = 0; i < tabs; i++)
                cout << "-";
            cout << current->getID() << "\n";

            for(Vertex* to : *graph->getEdges(current)) {

                Vertex* real = graph->getVertex(to);
                int color = real->getColor();

                if (color == 0) {
                    tabs++;
                    //adding new vertex to work stack
                    visited = true;
                    stack.push(real);
                    real->setColor(real->getColor() + 1);
                    break;
                }
            }
            if(!visited) {
                tabs--;
                stack.pop();
                current->setColor(current->getColor() + 1);
            }
        }
    }

    graph->print();

    ord_adj_list->clear();
    delete []ord_adj_list;

    return 0;
}

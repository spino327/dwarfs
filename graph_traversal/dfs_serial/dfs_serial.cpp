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

#include "Graph.h"
#include "Vertex.h"

using namespace std;

static const char* USAGE = "./dfs_serial <graph_file>";

bool loadData(const char* fn, Graph* graph) {

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

        int vertexIndex = 0;

//        // how many vertices
//        getline(in, line_buff);
//        iss.str(line_buff);
//        int num_vertices;
//        iss >> num_vertices;
//        cerr << "The number of v: " << num_vertices << "\n";

        graph = new Graph();
        bool setHead = false;

        //reading the list of vertices and edges
        while (getline(in, line_buff)) {
            iss.clear();
            iss.str(line_buff);

            int from_id, to_id;
            // vertex
            iss >> from_id;
            Vertex* from = new Vertex(from_id);
            if (!setHead) {
                graph->setHead(from);
                setHead = true;
                cerr << "setting head to " << graph->getHead()->getID() << "\n";
            }

            while (iss >> to_id)
                graph->add_edge(from, new Vertex(to_id));

        }

        graph->print();

        in.close();
    }

//    //reading the count of edges
//    queue<int> s;
//    int previousElement = 0;
//    //reading the list of vertices and edges
//    while(!feof(file))
//    {
//        if(getNumber(str, file))
//        {
//            vertexIndex = atoi(str);
//            if(vertexIndex != 0){
//                //create new array for store edges for vertex with index = previousElement
//                solver->graph->edgesMatrix[previousElement] = new int[s.size()];
//                solver->graph->arrayOfcounts[previousElement] = (int)s.size();
//            }
//
//            for( int i =0; !s.empty() ; i++)
//            {
//                solver->graph->edgesMatrix[previousElement][i] = s.front();
//                s.pop();
//            }
//            previousElement = vertexIndex;
//        }
//        else if (str[0] != '\0')
//        {   //write the edge and add to queue of edges
//            int index = atoi(str);
//            s.push(index);
//        }
//    }
//
//    //read last element
//    solver->graph->edgesMatrix[previousElement] = new int[s.size()];
//    solver->graph->arrayOfcounts[previousElement] = (int)s.size();
//
//    for( int i =0; !s.empty() ; i++)
//    {
//        solver->graph->edgesMatrix[vertexIndex][i] = s.front();
//        s.pop();
//    }
//
//    fclose(file);
//
//    return 0;

    return false;
}

int main(int argc, char **argv) {


    // reading the user parameters
    if (argc != 2) {
        cout << USAGE;
        exit(-1);
    }

    Graph *graph;
    char* input_fname = argv[1];

    if (!loadData(input_fname, graph)) {
        perror ("couldn't load the graph from the input file!");
    }

    stack<Vertex*> s;
    //set the head of graph
    Vertex* head = graph->getHead();
    cout << "color: " << head->getColor() << "\n";
//    head->setColor(head->getColor());

    s.push(head);
    //while stack not empty
    while (!s.empty())
    {
        //take the first element
        Vertex* u = s.top();
        //for all edges of current vertex
        bool hasNoVisited = true;
        for(int j = 0; j < graph->getNumberOfEdges(u) ; j++)
        {
//            int count =  graph->getVisited(graph->edgesMatrix[u][j]);
//            if(count == 0)
//            {
//                //adding new vertex to work stack
//                hasNoVisited = false;
//                s.push(graph->edgesMatrix[u][j]);
//                graph->setVisited(graph->edgesMatrix[u][j]);
//                break;
//            }
        }
        if(hasNoVisited)
        {
            s.pop();
        }
    }

    return 0;
}

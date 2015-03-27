/*
 * Graph.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: pinogal
 */

#include "Graph.h"

Graph::Graph() {
    this->adj_list = new unordered_map<Vertex*, vector<Vertex*>*,
            hash_Vertex, equal_Vertex>;
    this->head = NULL;
}

Graph::~Graph() {
//    //deletion of edges Matrix
//    for(int i = 0;i <length;i++)
//    {
//        delete []edgesMatrix[i];
//    }
//    delete []edgesMatrix;
//
//    //deletion visited list
//    delete []visited;
}

int Graph ::getLength()
{
    return this->adj_list->size();
}

Vertex* Graph ::getHead()
{
    return head;
}

void Graph::setHead(Vertex* v)
{
    head = v;
}

int Graph::getNumberOfEdges(Vertex* v) {
    vector<Vertex*>* tmp = this->adj_list->at(v);
    return tmp->size();
}

void Graph::add_edge (Vertex* from, Vertex* to) {

    vector<Vertex*>* tmp;
    if (adj_list->find(from) == adj_list->end()) {
        tmp = new vector<Vertex*>;
        adj_list->insert( pair<Vertex*, vector<Vertex*>*> (from, tmp) );
    } else
        tmp = adj_list->at(from);

    tmp->push_back(to);
    if (adj_list->find(to) == adj_list->end()) {
        adj_list->insert(pair<Vertex*, vector<Vertex*>*> (to, new vector<Vertex*>) );
    }
}

void Graph::print() {

    for (auto from : *adj_list) {
        cerr << from.first->getID() << "\t[";

        for (vector<Vertex*>::size_type i{0}, end{from.second->size()}; i != end; ++i)
            cerr << from.second->at(i)->getID() << ' ';

        cerr << "]\n";
    }
}

//map<vtx::Vertex*, vector<vtx::Vertex*>*>* Graph::get_adj_list() {
//    return adj_list;
//}

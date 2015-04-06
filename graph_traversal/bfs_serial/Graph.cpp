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
    this->head = nullptr;
}

Graph::~Graph() {
    //deletion of adj list
    adj_list->clear();
    delete []adj_list;
}

int Graph ::getLength() {
    return this->adj_list->size();
}

Vertex* Graph ::getHead() {
    return head;
}

void Graph::setHead(Vertex* v) {
    head = v;
}

int Graph::getNumberOfEdges(Vertex* v) {
    vector<Vertex*>* tmp = this->adj_list->at(v);
    return tmp->size();
}

vector<Vertex*>* Graph::getEdges(Vertex* v) {
    return adj_list->at(v);
}

Vertex* Graph::getVertex(Vertex* v) {
    return (adj_list->find(v))->first;
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

void Graph::resetColors() {
    // setting colors back to white
    for (auto vertex : *this->get_adj_list())
        vertex.first->setColor(0);
}

void Graph::print() {

    for (auto from : *adj_list) {
        Vertex* p = from.first->getParent();
        cerr << from.first->getID() << " : color=" << from.first->getColor()
                << "\tparent=" << (p != nullptr ? p->getID() : INFINITY)
                << "\t[";

        for (vector<Vertex*>::size_type i{0}, end{from.second->size()}; i != end; ++i)
            cerr << from.second->at(i)->getID() << ' ';

        cerr << "]\n";
    }
}

unordered_map<Vertex*, vector<Vertex*>*,
            hash_Vertex, equal_Vertex>* Graph::get_adj_list() {
    return adj_list;
}

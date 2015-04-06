/*
 * Vertex.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pinogal
 */

#include "Vertex.h"

Vertex::Vertex(int id) {
    color = 0;
    this->id = id;
    this->parent = nullptr;
}

Vertex::~Vertex() {
}


int Vertex::getID() {
    return id;
}

int Vertex::getColor() {
    return color;
}

void Vertex::setColor(int c) {
    color = c;
}

Vertex* Vertex::getParent() {
    return this->parent;
}

void Vertex::setParent(Vertex* p) {
    this->parent = p;
}

/*
 * Vertex.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: pinogal
 */

#include "Vertex.h"

Vertex::Vertex(int id) {
    color = 0;
    parent = nullptr;
    this->id = id;
}

Vertex::~Vertex() {
    parent = nullptr;
}

Vertex* Vertex::getParent() {
    return parent;
}

int Vertex::getID() {
    return id;
}

int Vertex::getColor() {
    return color;
}

void Vertex::setParent(Vertex* parent) {
    this->parent = parent;
}

void Vertex::setColor(int c) {
    color = c;
}

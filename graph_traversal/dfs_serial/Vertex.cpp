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

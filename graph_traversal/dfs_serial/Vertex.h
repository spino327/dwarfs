/*
 * Vertex.h
 *
 *  Created on: Dec 18, 2014
 *      Author: pinogal
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <iostream>
#include <functional>

using namespace std;

class Vertex {

public:
    Vertex(int id);
    virtual ~Vertex();
    Vertex* getParent();
    int getColor();
    int getID();
    void setParent(Vertex* parent);
    void setColor(int c);
    int id;

private:
    /**
     * 0: white
     * 1: gray
     * 2: black
     */
    int color;
    Vertex* parent;
};

struct hash_Vertex {
    size_t operator() (const Vertex* x) const {
        return hash<int>()(x->id);
    }
};

struct equal_Vertex {
    bool operator() (const Vertex* x, const Vertex* y) const {
        return x->id == y->id;
    }
};

#endif /* VERTEX_H_ */

/*
 * Copyright (C) 2015 Computer Architecture and Parallel Systems Laboratory (CAPSL)
 *
 * Original author: Sergio Pino
 * E-Mail: sergiop@udel.edu
 *
 * License
 *
 * Redistribution of this code is allowed only after an explicit permission is
 * given by the original author or CAPSL and this license should be included in
 * all files, either existing or new ones. Modifying the code is allowed, but
 * the original author and/or CAPSL must be notified about these modifications.
 * The original author and/or CAPSL is also allowed to use these modifications
 * and publicly report results that include them. Appropriate acknowledgments
 * to everyone who made the modifications will be added in this case.
 *
 * Warranty
 *
 * THIS CODE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES THAT
 * THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR
 * PURPOSE OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE
 * OF THE COVERED CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN
 * ANY RESPECT, YOU (NOT THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME
 * THE COST OF ANY NECESSARY SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER
 * OF WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS LICENSE. NO USE OF ANY
 * COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER THIS DISCLAIMER.
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
    int getColor();
    int getID();
    void setColor(int c);
    Vertex* getParent();
    void setParent(Vertex* p);
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

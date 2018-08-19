/* 
 * File:   NodeComparator.h
 * Author: Shreshth Tuli
 *
 */

#ifndef NODECOMPARATOR_H
#define	NODECOMPARATOR_H

#include "Node.h"

/**
 * Node is a conference configuration alias
 * This class compares two nodes based on the f function of A* algo
 * 
 * @author Shreshth Tuli
 *
 */

class NodeComparator {

public:

    /**
     * Node Comparator function
     */
    int operator() (const Node& node1, const Node& node2){
        return node1.score > node2.score;
    }

};

#endif	/* NODECOMPARATOR_H */


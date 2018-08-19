/* 
 * File:   Node.h
 * Author: Shreshth Tuli
 *
 */

#ifndef NODE_H
#define	NODE_H


#include <iostream>
#include <cstdlib>
#include "Session.h"
using namespace std;

/**
 * Node is a conference configuration alias
 * 
 * @author Shreshth Tuli
 *
 */

class Node {
    
private:    
    
    static int size;
    static int parallelTracks;
    static int sessionsInTrack;
    static int papersInSession;
    int num_elements;
    
public:
    Session *array;         // Configuration array   
    double score;           // score of this node


    /**
     * Node constructor
     * Initialize node array with all elements = -1
     */
    Node(int parallelTracks, int sessionsInTrack, int papersInSession);

    /**
     * Node Constructor
     * Forms a new node with values as copy of the parent node
     */
    Node(Session *node_array);

    /**
     * Get value at specified location
     */
    int get(int tracknumber, int sessionnumber, int paperIndex);

    /**
     * Set value at specified location
     * return false if full
     */
    bool set(int tracknumber, int sessionnumber, int value);

    /**
     * Returns if session is empty
     */
    bool isSessionEmpty(int tracknumber, int sessionnumber);

    /**
     * Is the Node complete, i.e. number of elements = size
     */
    bool isComplete();


    void printNode();
};

#endif	/* NODE_H */


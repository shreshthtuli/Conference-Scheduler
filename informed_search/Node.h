/* 
 * File:   Node.h
 * Author: Shreshth Tuli
 *
 */

#ifndef NODE_H
#define	NODE_H


#include <iostream>
#include <cstdlib>
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
    
public:
    int *array;             // Configuration array   
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
    Node(int *node_array);

    /**
     * Get value at specified location
     */
    int get(int tracknumber, int sessionnumber, int paperIndex);

    /**
     * Set value at specified location
     */
    void set(int tracknumber, int sessionnumber, int paperIndex, int value);

    /**
     * Returns true if session is full
     * false otherwise
     */
    bool isSessionFull(int tracknumber, int sessionnumber);


    void printNode();
};

#endif	/* NODE_H */


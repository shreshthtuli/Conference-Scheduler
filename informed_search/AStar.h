/* 
 * File:   AStar.h
 * Author: Shreshth Tuli
 *
 */

#ifndef ASTAR_H
#define	ASTAR_H


#include <iostream>
#include <cstdlib>
#include <queue>
#include "Node.h"
#include "NodeComparator.h"
using namespace std;

/**
 * The A* algo implementation
 * and heuristic function comparator
 * 
 * @author Shreshth Tuli
 *
 */

class AStar {
    
private:    
    
    int parallelTracks;
    int sessionsInTrack;
    int papersInSession;
    
public:
    // A* priority queue  
    priority_queue<Node, vector<Node>, NodeComparator> priority_queue;             
    // max score of the nodes
    double max_score;       
    double ** distanceMatrix;


    /**
     * A* constructor
     * Initialize queue with start element
     */
    AStar(int parallelTracks, int sessionsInTrack, int papersInSession);

    /**
     * Iterate function
     */
    void iterate();

    /**
     * Generate Successors and add to priority queue
     */
    void generateSucessors();

    /**
     * Calculate Scores of generated nodes based on 
     * heuristic function
     */
    double calcScore();


    void printConference(char *);
};

#endif	/* NODE_H */


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
    int n;
    double tradeoffCoefficient;
    Node curNode;
    Node newNode;
    int index;
    
public:
    // A* priority queue  
    priority_queue<Node, vector<Node>, NodeComparator> queue;             
    // max score of the nodes
    double max_score;       
    double ** distanceMatrix;

    // Value Functions
    double * maxDistanceArray;
    double * maxSimilarityArray;
    double maxDistance;
    double maxSimilarity;


    /**
     * A* constructor
     * Initialize queue with start element
     */
    AStar(int parallelTracks, int sessionsInTrack, int papersInSession, double tradeoffCoefficient);

    /**
     * Iterate function
     */
    void iterate();

    /**
     * Update Value functions
     */
    void updateValueFunction();

    /**
     * Generate Successors and add to priority queue
     */
    void generateSucessors();

    /**
     * Calculate Scores of generated nodes based on 
     * heuristic function
     */
    void calcScore();


    void printConference(char *);
};

#endif	/* NODE_H */


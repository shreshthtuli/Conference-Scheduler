/* 
 * File:   SessionOrganizer.h
 * Author: Kapil Thakkar
 *
 */

#ifndef SESSIONORGANIZER_H
#define	SESSIONORGANIZER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>


#include "Conference.h"
#include "Track.h"
#include "Session.h"

using namespace std;


/**
 * SessionOrganizer reads in a similarity matrix of papers, and organizes them
 * into sessions and tracks.
 * 
 * @author Kapil Thakkar
 *
 */
class SessionOrganizer {
private:
    double ** distanceMatrix;

    int parallelTracks ;
    int papersInSession ;
    int sessionsInTrack ;

    Conference *conference;
    Conference *best_conference;

    double global_max;

    double currentTime;
    double endTime;
    double startTime;
    double tradeoffCoefficient ; // the tradeoff coefficient
    double cur_score;
    double new_score;


public:
    double processingTimeInMinutes ;
    SessionOrganizer();
    SessionOrganizer(string filename);

    void initializeConference();

    struct Paper{
        int id;
        double distance;
        // bool operator<(const Paper& rhs) const{
        //     return distance > rhs.distance;
        // }
    };

    // static bool paperComparator(Paper a, Paper b)
    // {
    //     return a.distance > b.distance;
    // }
    
    class paperComparator
    {
        public:
        bool operator() (Paper p1, Paper p2)
        {
            return p1.distance > p2.distance;
        }
    };
    
    /**
     * Read in the number of parallel tracks, papers in session, sessions
     * in a track, and the similarity matrix from the specified filename.
     * @param filename is the name of the file containing the matrix.
     * @return the similarity matrix.
     */
    void readInInputFile(string filename);
    
    
    
    /**
     * Organize the papers according to some algorithm.
     */
    void organizePapers();
    
    
    /**
     * Get the distance matrix.
     * @return the distance matrix.
     */
    double** getDistanceMatrix();
    
    
    /**
     * Score the organization.
     * @return the score.
     */
    double scoreOrganization();

    /**
     * Move to better sucessor based on First choice Hill Climbing
     * @return true if such successor found, and false otherwise (stop)
     */
    bool getSuccessor(int k_dy);    
    bool getSuccessor1();    

    double getWeightedAvg(double * a, int idx);
    /**
     * Keep running getSuccessor() till it returns true
     * When it returns false, return max score
     */
    double run();

    /**
     * Copies confernce to best_conference
     */
    void copyConference();
    void reverseCopyConference();
    
    void printSessionOrganiser(char *);
};

#endif	/* SESSIONORGANIZER_H */


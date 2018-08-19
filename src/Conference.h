/* 
 * File:   Conference.h
 * Author: Kapil Thakkar
 *
 * Created on 9 August, 2015, 10:07 AM
 */

#ifndef CONFERENCE_H
#define	CONFERENCE_H

#include<iostream>
#include<fstream>
using namespace std;

#include "Track.h"

class Conference {
private:
    // The array of tracks.
    Track *tracks;

    // The number of parallel tracks.
    int parallelTracks;

    // The number of sessions in a track.
    int sessionsInTrack;

    // The number of papers in a session.
    int papersInSession;

    // Paper IDs used for swap
    int paper1;
    int paper2;

    // Shuffled array of integers 1 to n
    int *shuffled_array;
    int n;

public:
    Conference();
    
    /**
     * Constructor for Conference.
     * 
     * @param parallelTracks is the number of parallel tracks.
     * @param sessionsInTrack is the number of sessions in a track.
     * @param papersInSession is the number of papers in a session.
     */
    Conference(int parallelTracks, int sessionsInTrack, int papersInSession);
    
    
    /**
     * Initialize the tracks.
     * @param parallelTracks is the number of parallel tracks.
     * @param sessionsInTrack is the number of sessions in a track.
     * @param papersInSession is the number of papers in a session.
     */
    void initTracks(int parallelTracks, int sessionsInTrack, int papersInSession);


    /**
     * Shuffle conference values
     */
    void shuffle();
    
    
    /**
     * Gets the number of parallel tracks.
     * @return the number of parallel tracks.
     */
    int getParallelTracks();
    
    
    /**
     * Gets the number of sessions in a track.
     * @return the number of sessions in a track.
     */
    int getSessionsInTrack();
    
    
    /**
     * Gets the number of papers in a session.
     * @return the number of papers in a session.
     */
    int getPapersInSession();
    
    
    /**
     * Gets the track at the specified index.
     * @param index is the index of the specified track.
     * @return the track
     */
    Track getTrack(int index);
    
    
    /**
     * Sets the paper in the specified slot to the given paper id.
     * @param trackIndex is the track index.
     * @param sessionIndex is the session index.
     * @param paperIndex is the paper index.
     * @param paperId is the id of the paper.
     */
    void setPaper(int trackIndex, int sessionIndex, int paperIndex, int paperId);

    /**
     * Swaps two papers specified by their trackIndex, sessionIndex and paperIndex
     */
    void swapPapers(int trackIndex1, int sessionIndex1, int paperIndex1, int trackIndex2, int sessionIndex2, int paperIndex2);
    
    
    void printConference(char *);
};

#endif	/* CONFERENCE_H */


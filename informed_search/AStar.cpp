/* 
 * File:   AStar.cpp
 * Author: Shreshth Tuli
 * 
 */

#include "AStar.h"

AStar::AStar(int parallelTracks, int sessionsInTrack, int papersInSession)
{
    this->max_score = 0;
    this->parallelTracks = parallelTracks;
    this->sessionsInTrack = sessionsInTrack;
    this->papersInSession = papersInSession;
}

void AStar::iterate()
{

}

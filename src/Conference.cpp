/* 
 * File:   Conference.cpp
 * Author: Kapil Thakkar
 * 
 */

#include "Conference.h"
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>

Conference::Conference ( )
{
    this->parallelTracks = 0;
    this->sessionsInTrack = 0;
    this->papersInSession = 0;
}

Conference::Conference ( int parallelTracks, int sessionsInTrack, int papersInSession )
{
    this->parallelTracks = parallelTracks;
    this->sessionsInTrack = sessionsInTrack;
    this->papersInSession = papersInSession;
    this->n = parallelTracks * sessionsInTrack * papersInSession;
    this->shuffled_array = (int *) malloc (sizeof (int) * n);
    for(int i = 0; i < n; i++){
        this->shuffled_array[i] = i;
    }
    initTracks ( parallelTracks, sessionsInTrack, papersInSession );
}

void Conference::initTracks ( int parallelTracks, int sessionsInTrack, int papersInSession )
{
    tracks = ( Track * ) malloc ( sizeof (Track ) * parallelTracks );
    for ( int i = 0; i < parallelTracks; i++ )
    {
        Track tempTrack ( sessionsInTrack );
        for ( int j = 0; j < sessionsInTrack; j++ )
        {
            Session tempSession ( papersInSession );
            tempTrack.setSession ( j, tempSession );
        }
        tracks[i] = tempTrack;
    }
}

void Conference::shuffle()
{
    int counter = 0;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(&this->shuffled_array[0], &this->shuffled_array[n], g);

    for ( int i = 0; i < this->getSessionsInTrack ( ); i++ )
    {
        for ( int j = 0; j < this->getParallelTracks ( ); j++ )
        {
            for ( int k = 0; k < this->getPapersInSession ( ); k++ )
            {
                setPaper ( j, i, k, this->shuffled_array[counter]);
                counter++;
            }
        }
    }
}

int Conference::getParallelTracks ( )
{
    return parallelTracks;
}

int Conference::getSessionsInTrack ( )
{
    return sessionsInTrack;
}

int Conference::getPapersInSession ( )
{
    return papersInSession;
}

Track Conference::getTrack ( int index )
{
    if ( index < parallelTracks )
    {
        return tracks[index];
    }
    else
    {
        cout << "Index out of bound - Conference::getTrack" << endl;
        exit ( 0 );
    }
}

void Conference::setPaper ( int trackIndex, int sessionIndex, int paperIndex, int paperId )
{
    if ( this->parallelTracks > trackIndex )
    {
        Track curTrack = tracks[trackIndex];
        curTrack.setPaper ( sessionIndex, paperIndex, paperId );
    }
    else
    {
        cout << "Index out of bound - Conference::setPaper" << endl;
        exit ( 0 );

    }
}

void Conference::swapPapers(int trackIndex1, int sessionIndex1, int paperIndex1, int trackIndex2, int sessionIndex2, int paperIndex2)
{
    this->paper1 = getTrack(trackIndex1).getSession(sessionIndex1).getPaper(paperIndex1);
    this->paper2 = getTrack(trackIndex2).getSession(sessionIndex2).getPaper(paperIndex2);
    setPaper(trackIndex1, sessionIndex1, paperIndex1, this->paper2);
    setPaper(trackIndex2, sessionIndex2, paperIndex2, this->paper1);
}

void Conference::printConference (char * filename )
{
    ofstream ofile(filename);

    for ( int i = 0; i < sessionsInTrack; i++ )
    {
        for ( int j = 0; j < parallelTracks; j++ )
        {
            for ( int k = 0; k < papersInSession; k++ )
            {
                ofile<< tracks[j].getSession ( i ).getPaper ( k ) << " ";
            }
            if ( j != parallelTracks - 1 )
            {
                ofile<<"| ";
            }
        }
        ofile<<"\n";
    }
    ofile.close();
    cout<<"Organization written to ";
    printf("%s :)\n",filename);

}

void Conference::printConference ()
{
    for ( int i = 0; i < sessionsInTrack; i++ )
    {
        for ( int j = 0; j < parallelTracks; j++ )
        {
            for ( int k = 0; k < papersInSession; k++ )
            {
                cout<< tracks[j].getSession ( i ).getPaper ( k ) << " ";
            }
            if ( j != parallelTracks - 1 )
            {
                cout<<"| ";
            }
        }
        cout<<"\n";
    }
}
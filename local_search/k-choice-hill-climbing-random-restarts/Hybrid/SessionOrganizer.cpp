/* 
 * File:   SessionOrganizer.cpp
 * Author: Kapil Thakkar
 * 
 */

#include "SessionOrganizer.h"
#include "Util.h"
#include <ctime>
#include <iostream>

SessionOrganizer::SessionOrganizer ( )
{
    parallelTracks = 0;
    papersInSession = 0;
    sessionsInTrack = 0;
    processingTimeInMinutes = 0;
    tradeoffCoefficient = 1.0;
}

SessionOrganizer::SessionOrganizer ( string filename )
{
    global_max = 0;
    readInInputFile ( filename );
    conference = new Conference ( parallelTracks, sessionsInTrack, papersInSession );
    best_conference = new Conference (parallelTracks, sessionsInTrack, papersInSession);
    int counter = 0;
    for ( int i = 0; i < best_conference->getSessionsInTrack ( ); i++ )
    {
        for ( int j = 0; j < best_conference->getParallelTracks ( ); j++ )
        {
            for ( int k = 0; k < best_conference->getPapersInSession ( ); k++ )
            {
                conference->setPaper ( j, i, k, counter++ );
            }
        }
    }
    conference->printConference();
    cout << "Start score : " << scoreOrganization() << "\n";
}

void SessionOrganizer::organizePapers ( )
{
    double result;
    while(currentTime - startTime < ((processingTimeInMinutes * 60) - 10)){
        result = run();
        if (result > global_max){
            global_max = result;
            copyConference();
        }
        currentTime = time(0);
    }
}

void SessionOrganizer::copyConference(){

    int paperId;
    for ( int i = 0; i < best_conference->getSessionsInTrack ( ); i++ )
    {
        for ( int j = 0; j < best_conference->getParallelTracks ( ); j++ )
        {
            for ( int k = 0; k < best_conference->getPapersInSession ( ); k++ )
            {
                paperId = conference->getTrack(j).getSession(i).getPaper(k);
                best_conference->setPaper ( j, i, k, paperId );
            }
        }
    }
}

double SessionOrganizer::run ( )
{
    conference->shuffle();
    double max = 0;
    // cout << "Shuffled conference \n";
    // conference->printConference();
    // cout << "Score : " << scoreOrganization() << "\n" ;
    while(getSuccessor() && currentTime - startTime < ((processingTimeInMinutes * 60) - 10)){
        // conference->printConference();
        // cout << "Score : " << scoreOrganization() << "\n" ;
    }
    max = scoreOrganization();
    return max;
}

void SessionOrganizer::readInInputFile ( string filename )
{
    vector<string> lines;
    string line;
    startTime = time(0);
    ifstream myfile ( filename.c_str () );
    if ( myfile.is_open ( ) )
    {
        while ( getline ( myfile, line ) )
        {
            //cout<<"Line read:"<<line<<endl;
            lines.push_back ( line );
        }
        myfile.close ( );
    }
    else
    {
        cout << "Unable to open input file";
        exit ( 0 );
    }

    if ( 6 > lines.size ( ) )
    {
        cout << "Not enough information given, check format of input file";
        exit ( 0 );
    }

    processingTimeInMinutes = atof ( lines[0].c_str () );
    papersInSession = atoi ( lines[1].c_str () );
    parallelTracks = atoi ( lines[2].c_str () );
    sessionsInTrack = atoi ( lines[3].c_str () );
    total_neighbours = papersInSession * sessionsInTrack * parallelTracks * (parallelTracks * sessionsInTrack - 1) * papersInSession / 2;
    tradeoffCoefficient = atof ( lines[4].c_str () );

    int n = lines.size ( ) - 5;
    double ** tempDistanceMatrix = new double*[n];
    for ( int i = 0; i < n; ++i )
    {
        tempDistanceMatrix[i] = new double[n];
    }


    for ( int i = 0; i < n; i++ )
    {
        string tempLine = lines[ i + 5 ];
        string elements[n];
        splitString ( tempLine, " ", elements, n );

        for ( int j = 0; j < n; j++ )
        {
            tempDistanceMatrix[i][j] = atof ( elements[j].c_str () );
        }
    }
    distanceMatrix = tempDistanceMatrix;

    int numberOfPapers = n;
    int slots = parallelTracks * papersInSession*sessionsInTrack;
    if ( slots != numberOfPapers )
    {
        cout << "More papers than slots available! slots:" << slots << " num papers:" << numberOfPapers << endl;
        exit ( 0 );
    }
}

double** SessionOrganizer::getDistanceMatrix ( )
{
    return distanceMatrix;
}

bool SessionOrganizer::getSuccessor()
{
    this->cur_score = scoreOrganization();
    stringSet.clear();
    int i,j,k,l,m,n;
    int counter = 0;
    while(counter < total_neighbours){
        while(true)
        {
            i = rand() % conference->getSessionsInTrack ( );
            l = rand() % conference->getSessionsInTrack ( );
            j = rand() % conference->getParallelTracks ( );
            m = rand() % conference->getParallelTracks ( );
            if(i!=l || j!=m){
                break;
            }
        }
        k = rand() % conference->getPapersInSession();
        n = rand() % conference->getPapersInSession();

        if(stringSet.find(to_string(i)+to_string(j)+to_string(k)+to_string(l)+to_string(m)+to_string(n))!=stringSet.end() 
        || stringSet.find(to_string(l)+to_string(m)+to_string(n)+to_string(i)+to_string(j)+to_string(k))!=stringSet.end())
        {
            continue;
        }

        counter++;
        stringSet.insert(to_string(i)+to_string(j)+to_string(k)+to_string(l)+to_string(m)+to_string(n));
        conference->swapPapers(j, i, k, m, l, n);
        this->new_score = scoreOrganization();
        if (this->new_score > this->cur_score){
            // If performance improved return true
            return true;
        }
        else{
            // Swap back and continue
            conference->swapPapers(j, i, k, m, l, n);
        }
    }

    // No successor found with better score
    return false;

}

void SessionOrganizer::printSessionOrganiser ( char * filename)
{
    best_conference->printConference ( filename);
    conference = best_conference;
    cout << "Best score : " << scoreOrganization() << " \n";
}

double SessionOrganizer::scoreOrganization ( )
{
    // Sum of pairwise similarities per session.
    double score1 = 0.0;
    for ( int i = 0; i < conference->getParallelTracks ( ); i++ )
    {
        Track tmpTrack = conference->getTrack ( i );
        for ( int j = 0; j < tmpTrack.getNumberOfSessions ( ); j++ )
        {
            Session tmpSession = tmpTrack.getSession ( j );
            for ( int k = 0; k < tmpSession.getNumberOfPapers ( ); k++ )
            {
                int index1 = tmpSession.getPaper ( k );
                for ( int l = k + 1; l < tmpSession.getNumberOfPapers ( ); l++ )
                {
                    int index2 = tmpSession.getPaper ( l );
                    score1 += 1 - distanceMatrix[index1][index2];
                }
            }
        }
    }

    // Sum of distances for competing papers.
    double score2 = 0.0;
    for ( int i = 0; i < conference->getParallelTracks ( ); i++ )
    {
        Track tmpTrack1 = conference->getTrack ( i );
        for ( int j = 0; j < tmpTrack1.getNumberOfSessions ( ); j++ )
        {
            Session tmpSession1 = tmpTrack1.getSession ( j );
            for ( int k = 0; k < tmpSession1.getNumberOfPapers ( ); k++ )
            {
                int index1 = tmpSession1.getPaper ( k );

                // Get competing papers.
                for ( int l = i + 1; l < conference->getParallelTracks ( ); l++ )
                {
                    Track tmpTrack2 = conference->getTrack ( l );
                    Session tmpSession2 = tmpTrack2.getSession ( j );
                    for ( int m = 0; m < tmpSession2.getNumberOfPapers ( ); m++ )
                    {
                        int index2 = tmpSession2.getPaper ( m );
                        score2 += distanceMatrix[index1][index2];
                    }
                }
            }
        }
    }
    double score = score1 + tradeoffCoefficient*score2;
    return score;
}

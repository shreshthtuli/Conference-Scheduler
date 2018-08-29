/* 
 * File:   SessionOrganizer.cpp
 * Author: Kapil Thakkar
 * 
 */

#include "SessionOrganizer.h"
#include "Util.h"
#include <ctime>
#include <iostream>
#include <algorithm> 
#include <list>
#include <queue>
#include <cmath>


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
    
    initializeConference();
    
    // conference->printConference();
    // cout << "Start score : " << scoreOrganization() << "\n";  

    // for ( int i = 0; i < best_conference->getSessionsInTrack ( ); i++ )
    // {
    //     for ( int j = 0; j < best_conference->getParallelTracks ( ); j++ )
    //     {
    //         for ( int k = 0; k < best_conference->getPapersInSession ( ); k++ )
    //         {
    //             conference->setPaper ( j, i, k, counter++ );
    //         }
    //     }
    // }
    
    // for(int i = 0; i < conference->n; i++)
    // {
    //     for(int j = 0; j < conference->n; j++)
    //     {
    //         cout << distanceMatrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // for(int i = 0; i < conference->n; i++)
    // {
    //     for(int j = 0; j < conference->n; j++)
    //     {
    //         cout << distanceMatrixInt[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    conference->printConference();
    cout << "Start score : " << scoreOrganization() << "\n";
    // exit(0);
}

void SessionOrganizer::initializeConference()
{
    list<int> remainingPapers;
    priority_queue<Paper, std::vector<Paper>, paperComparator> distances;
    for(int i = 0; i < conference->n; i++)
    {
        remainingPapers.push_back(i);
    }

    for(int i = 0; i < conference->sessionsInTrack; i++)
    {
        for(int j = 0; j < conference->parallelTracks; j++)
        {
            int num = remainingPapers.front();
            remainingPapers.pop_front();
            distances = priority_queue<Paper, std::vector<Paper>, paperComparator>();
            for(auto v : remainingPapers)
            {
                Paper tmp;
                tmp.id = v;
                tmp.distance = distanceMatrix[num][v];
                distances.push(tmp);
            }
            conference->setPaper(j,i,0,num);
            // cout << "Added paper "<< num << endl;
            int counter = 1;
            int dist_size = distances.size();
            for(int a = 0 ; a < dist_size ; a++){
                Paper p = distances.top();
                distances.pop();

                // cout << i << " " << j << " " << counter << " : " << p.id << endl;
                conference->setPaper(j,i,counter, p.id); counter++;
                remainingPapers.remove(p.id);
                if(counter >= conference->papersInSession){
                    break;
                }
            }
        }
    }
    
}

void SessionOrganizer::organizePapers ( )
{
    double result;
    // cout << (double)(time(0)) << endl;
    // cout << endTime << endl;
    while(currentTime < endTime){
        result = run();
        // cout << time(0) - startTime << endl;
        currentTime = time(0);
    }
}

void SessionOrganizer::copyConference(){

    int paperId;
    for ( int i = 0; i < best_conference->sessionsInTrack; i++ )
    {
        for ( int j = 0; j < best_conference->parallelTracks; j++ )
        {
            for ( int k = 0; k < best_conference->papersInSession; k++ )
            {
                paperId = conference->tracks[j].sessions[i].papers[k];
                best_conference->setPaper ( j, i, k, paperId );
            }
        }
    }
}


void SessionOrganizer::reverseCopyConference(){

    int paperId;
    for ( int i = 0; i < best_conference->getSessionsInTrack ( ); i++ )
    {
        for ( int j = 0; j < best_conference->getParallelTracks ( ); j++ )
        {
            for ( int k = 0; k < best_conference->getPapersInSession ( ); k++ )
            {
                paperId = best_conference->getTrack(j).getSession(i).getPaper(k);
                conference->setPaper ( j, i, k, paperId );
            }
        }
    }
}

double SessionOrganizer::run ( )
{
    double max = 0;
    cout << "Shuffled conference \n";
    // conference->printConference();
    cout << "Score : " << scoreOrganization() << "\n" ;

    int k_param;
    double improvement = 0.0 ;
    double last_scores[5];
    int curr_index = 0;

    bool b ;
    int iter_num = 0;

    k_param = n > 300 ? 25 : 4;

    for( ; ; iter_num++){
        b = getSuccessorRand(k_param, 5*n);
        if(b == false){
            break;
        }
        double cscore = scoreOrganization();
        curr_index = iter_num % 5;
        last_scores[curr_index] = cscore;
        cout << "Score : " << cscore << "\n" ;
        if (cscore > global_max){
            global_max = cscore;
            copyConference();
        }
        if(  (iter_num % 50 == 0) && (iter_num > 5)  ){
            improvement = abs(cscore - getWeightedAvg(last_scores, curr_index));
            cout << iter_num << " : " << k_param<< " : " << improvement << " : Thesh : " << 0.00025 * cscore << endl;
            if(improvement < (0.00025 * cscore)){
                // k_param = k_param >= 1 ? k_param -1 : 0 ;
                k_param = k_param >= 1 ? k_param -1 : 0 ;
                if(k_param == 0){
                    break;
                }
            }
        }
    }

    cout << "RANDOM K SHORT maximization complete" << endl;
    k_param = 2;


    for( ; ; iter_num++){
        b = getSuccessor(k_param, true);
        if(b == false){
            cout << scoreOrganization() << endl;
            break;
        }
        double cscore = scoreOrganization();
        curr_index = iter_num % 5;
        last_scores[curr_index] = cscore;
        cout << "Score : " << cscore << "\n" ;
        if (cscore > global_max){
            global_max = cscore;
            copyConference();
        }
        if( (iter_num % 50 == 0) && (iter_num > 5)  ){
            improvement = abs(cscore - getWeightedAvg(last_scores, curr_index));
            cout << iter_num << " : " << k_param<< " : " << improvement << " : Thesh : " << 0.0009 * cscore << endl;
            
            if(improvement < (0.0009 * cscore)){
                k_param = k_param >= 1 ? k_param -1 : 0 ;
                if(k_param == 0){
                    break;
                }
            }
        }
    }

    k_param = 2;
    // while(getSuccessor(0, true)){
    //     cout << "Score : " << this->cur_score << "\n" ;
    //     if (this->cur_score > global_max){
    //         global_max = this->cur_score;
    //         copyConference();
    //     }
    // }

    cout << "K INT LONG maximization complete" << endl;

    for( ; ; iter_num++){
        b = getSuccessor(k_param, false);
        if(b == false){
            cout << scoreOrganization() << endl;
            break;
        }
        double cscore = scoreOrganization();
        curr_index = iter_num % 5;
        last_scores[curr_index] = cscore;
        cout << "Score : " << cscore << "\n" ;
        if (cscore > global_max){
            global_max = cscore;
            copyConference();
        }
        if( (iter_num % 50 == 0) && (iter_num > 5) ){
            improvement = abs(cscore - getWeightedAvg(last_scores, curr_index));

            cout << iter_num << " : " << k_param<< " : " << improvement << " : Thesh : " << 0.005 * cscore << endl;
            
            if(improvement < (0.005 * cscore)){
                k_param = k_param >= 1 ? k_param -1 : 0 ;
            }
        }
    }

    cout << "K DOUBLE  maximization complete" << endl;


    max = scoreOrganization();
    conference->shuffle();
    return max;
}

double SessionOrganizer::getWeightedAvg(double * a, int idx){
    
    double sum =  0.0;
    // 4 iterations
    for(int i = 1; i < 5; i++){
        sum += (a[(idx+i)%5])*(i);
    }
    // sum /= 10;
    return (sum/10.0);
}

void SessionOrganizer::readInInputFile ( string filename )
{
    startTime = time(0);
    vector<string> lines;
    string line;
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
    tradeoffCoefficient = atof ( lines[4].c_str () );
    total_neighbours = papersInSession * sessionsInTrack * parallelTracks * (parallelTracks * sessionsInTrack - 1) * papersInSession / 2;
    n = papersInSession * parallelTracks * sessionsInTrack;

    endTime = startTime + ((processingTimeInMinutes * 60) - 1);
    int n = lines.size ( ) - 5;
    double ** tempDistanceMatrix = new double*[n];
    unsigned short ** tempDistanceMatrixInt = new unsigned short*[n];
    for ( int i = 0; i < n; ++i )
    {
        tempDistanceMatrix[i] = new double[n];
        tempDistanceMatrixInt[i] = new unsigned short[n];
    }


    for ( int i = 0; i < n; i++ )
    {
        string tempLine = lines[ i + 5 ];
        string elements[n];
        splitString ( tempLine, " ", elements, n );

        for ( int j = 0; j < n; j++ )
        {
            tempDistanceMatrix[i][j] = atof ( elements[j].c_str () );
            tempDistanceMatrixInt[i][j] = 10 * tempDistanceMatrix[i][j];
        }
    }
    distanceMatrix = tempDistanceMatrix;
    distanceMatrixInt = tempDistanceMatrixInt;

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

bool SessionOrganizer::getSuccessor(int K_dyn, bool integerscore)
{
    int count = 0; 
    double glob_max = 0.0;
    
    saved_i = 0; saved_j = 0 ; saved_k = 0;
    saved_l = 0; saved_m = 0; saved_n = 0;
    bool flag = false;

    if(integerscore){
        this->cur_score = scoreOrganizationInt();
    }
    else{
        this->cur_score = scoreOrganization();
    }
    // Find first index
    int x = rand() % conference->sessionsInTrack;
    int y = rand() % conference->parallelTracks;
    int i,j;
    for ( int i1 = 0; i1 < conference->sessionsInTrack; i1++ )
    {
        i = (i1 + x) % conference->sessionsInTrack;
        for ( int j1 = 0; j1 < conference->parallelTracks; j1++ )
        {
            j = (j1 + y) % conference->parallelTracks;
            for ( int k = 0; k < conference->papersInSession; k++ )
            {
                // Find another index
                for ( int l = i; l < conference->sessionsInTrack; l++)
                {
                    for ( int m = j+1; m < conference->parallelTracks; m++)
                    {
                        // if (l == i && m <= j){
                        //     // Skip those of same or previous tracks for this session number
                        //     continue; 
                        // }
                        currentTime = time(0);
                        if(currentTime > endTime)
                        {
                            return false;
                        }
                        for (int n = 0; n < conference->getPapersInSession (); n++)
                        {
                            conference->swapPapers(j, i, k, m, l, n);
                            if(integerscore){
                                this->new_score = scoreOrganizationInt();
                            }
                            else{
                                this->new_score = scoreOrganization();
                            }
                                                        
                            if (this->new_score > this->cur_score){
                                // If performance improved return true
                                flag = true;
                                count++;
                                if(this->new_score > glob_max){
                                    glob_max = this->new_score;
                                    saved_i = i; saved_j = j; saved_k = k;
                                    saved_l = l; saved_m = m; saved_n = n;                                    
                                }
                                //what if we don't get k greator symbols?
                                if(count > K_dyn){
                                    //restore config
                                    conference->swapPapers(j, i, k, m, l, n);

                                    //swap to the saved thing
                                    conference->swapPapers(saved_j,saved_i,saved_k, saved_m, saved_l, saved_n);
                                    return true;
                                }

                                // //restore and continue
                                // conference->swapPapers(j, i, k, m, l, n);
                            }
                            // else{
                            // Swap back and continue in any case
                            conference->swapPapers(j, i, k, m, l, n);
                            // }
                        }
                    }
                }

            }
        }
    }

    if(flag){
        conference->swapPapers(saved_j,saved_i,saved_k, saved_m, saved_l, saved_n);
    }
    // No successor found with better score
    return flag;

}

// bool SessionOrganizer::getSuccessor1()
// {
//     this->cur_score = scoreOrganization();
//     // Find first index
//     int x = rand() % conference->getSessionsInTrack();
//     int y = rand() % conference->getParallelTracks();
//     int i,j;
//     for ( int i1 = 0; i1 < conference->getSessionsInTrack ( ); i1++ )
//     {
//         i = (i1 + x) % conference->getSessionsInTrack();
//         for ( int j1 = 0; j1 < conference->getParallelTracks ( ); j1++ )
//         {
//             j = (j1 + y) % conference->getParallelTracks();
//             for ( int k = 0; k < conference->getPapersInSession ( ); k++ )
//             {
//                 // Find another index
//                 for ( int l = i; l < conference->getSessionsInTrack(); l++)
//                 {
//                     for ( int m = 0; m < conference->getParallelTracks(); m++)
//                     {
//                         currentTime = time(0);
//                         if(currentTime > endTime)
//                         {
//                             return false;
//                         }
//                         if (l == i && m <= j){
//                             // Skip those of same or previous tracks for this session number
//                             continue; 
//                         }
//                         for (int n = 0; n < conference->getPapersInSession (); n++)
//                         {
//                             conference->swapPapers(j, i, k, m, l, n);
//                             this->new_score = scoreOrganization();
//                             if (this->new_score > this->cur_score){
//                                 // If performance improved return true
//                                 return true;
//                             }
//                             else{
//                                 // Swap back and continue
//                                 conference->swapPapers(j, i, k, m, l, n);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     // No successor found with better score
//     return false;

// }


bool SessionOrganizer::getSuccessorRand(int k_def, int limit)
{
    this->cur_score = scoreOrganizationInt();
    int i,j,k,l,m,n;
    int counter = 0;
    while(counter++ < limit){
        currentTime = time(0);
        if(currentTime > endTime)
        {
            return false;
        }
        while(counter < limit)
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

        conference->swapPapers(j, i, k, m, l, n);
        this->new_score = scoreOrganizationInt();
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

double SessionOrganizer::scoreOrganizationInt ()
{
    // Sum of pairwise similarities per session.
    unsigned short score1 = 0;
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
                    if(distanceMatrixInt[index1][index2] > 9)
                    {
                        score1 = 0;
                    }
                    else{
                        score1 = score1 + 9 - distanceMatrixInt[index1][index2];
                    }
                }
            }
        }
    }

    // Sum of distances for competing papers.
    unsigned short score2 = 0;
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
                        score2 += distanceMatrixInt[index1][index2];
                    }
                }
            }
        }
    }
    double score = score1 + tradeoffCoefficient*score2;
    return score/10;
}

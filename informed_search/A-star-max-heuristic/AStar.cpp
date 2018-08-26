/* 
 * File:   AStar.cpp
 * Author: Shreshth Tuli
 * 
 */

#include "AStar.h"
#include "Node.h"
#include "NodeComparator.h"
#include <fstream>
#include <random>
#include <algorithm>

AStar::AStar(int parallelTracks, int sessionsInTrack, int papersInSession, double tradeOffCoefficient)
{
    max_score = 0;
    this->parallelTracks = parallelTracks;
    cout << "Parallel Tracks : " << parallelTracks << endl;
    this->sessionsInTrack = sessionsInTrack;
    cout << "Sessions in Track : " << sessionsInTrack << endl;
    this->papersInSession = papersInSession;
    cout << "Papers in session : " << papersInSession << endl;
    n = parallelTracks * sessionsInTrack * papersInSession;
    this->tradeoffCoefficient = tradeOffCoefficient;

    this->maxDistanceArray = new double[n]();
    this->maxSimilarityArray = new double[n]();
    this->maxDistance = 1;
    this->maxSimilarity = 1;
    this->shuffled_array = new int[n]();
    for(int i = 0; i < n; i++){
        this->shuffled_array[i] = i;
        
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(&this->shuffled_array[0], &this->shuffled_array[n], g);
    for(int i = 0; i < n; i++){
        cout << this->shuffled_array[i] << " ";
    }
    Node first_node (parallelTracks, sessionsInTrack, papersInSession);
    cout << first_node.set(0, 0, this->shuffled_array[0]) << endl;
    cout << "First node : \n";
    first_node.printNode();
    queue.push(first_node);

    this->distanceMatrix = new double*[n];
    for ( int i = 0; i < n; ++i )
    {
        this->distanceMatrix[i] = new double[n];
    }
}

void AStar::iterate()
{
    cout << "Queue size : " << queue.size() << endl;
    while(!queue.empty())
    {
        curNode = queue.top();
        //cout << "Current Node \n";
        //curNode.printNode();
        //cout << "Score : " << curNode.score << "\n";
        queue.pop();
        if(curNode.num_elements == curNode.size * papersInSession){
            cout << "Exiting while \n";
            break;
        }
        generateSucessors();
    }
    cout << "A* iterate method ended" << endl;
    max_score = curNode.score;

}

void AStar::generateSucessors()
{
    index = this->shuffled_array[curNode.num_elements]; // Increment index
    //cout << "Inserting index = " << index << endl;
    for(int i = 0; i < this->sessionsInTrack; i++)
    {
        for(int j = 0; j < this->parallelTracks; j++)
        {
            if( i >= 1 && curNode.isSessionEmpty(j, i-1) )
            {
                continue;
            }
            Node newNode (curNode.array, curNode.parallelTracks, curNode.sessionsInTrack, curNode.papersInSession, curNode.num_elements);
            if(newNode.set(j, i, index))
            {
                //cout << "Inserted a node at " << i << ", " << j << endl;
                //newNode.printNode();
                newNode.score = calcScore(newNode); // Calculate score of newNode
                queue.push(newNode);
            }
        }
    }
}

void AStar::updateValueFunction()
{
    double gmax = 0;
    double gmin = 1;
    for(int i = 0; i < n; i++)
    {
        double max = 0;
        double min = 1;
        for(int j = 0; j < n; j++)
        {   
            if(i == j){
                continue;
            }
            if(this->distanceMatrix[i][j] > max){
                max = distanceMatrix[i][j];
            }
            if(this->distanceMatrix[i][j] < min)
            {
                min = distanceMatrix[i][j];
            }
        }
        this->maxDistanceArray[i] = max;
        this->maxSimilarityArray[i] = 1 - min;

        if(gmax < max)
        {
            gmax = max;
        }
        if(gmin > min)
        {
            gmin = min;
        }
    }

    this->maxDistance = gmax;
    this->maxSimilarity = 1 - gmin;
}

double AStar::calcScore(Node newNode)
{
    // Similarity Score
    double score1 = 0;
    int x;
    int y;
    for(int i = 0; i < this->parallelTracks; i++)
    {
        for(int j = 0; j < this->sessionsInTrack; j++)
        {
            for(int k = 0; k < this->papersInSession; k++)
            {
                for(int l = k+1; l < this->papersInSession; l++)
                {
                    x = newNode.get(i, j, k);
                    y = newNode.get(i, j, l);
                    if(x != -1 && y != -1){
                        score1 += (1 - this->distanceMatrix[x][y]);
                    }
                    else if(x != -1 && y == -1){
                        score1 += this->maxSimilarityArray[x];
                    }
                    else if(x == -1 && y != -1){
                        score1 += this->maxSimilarityArray[y];
                    }
                    else if(x == -1 && y == -1){
                        score1 += this->maxSimilarity;
                    }
                    
                }
            }
        }
    }    

    // Distance score
    double score2 = 0;
    for(int i = 0; i < this->parallelTracks; i++)
    {
        for(int j = 0; j < this->sessionsInTrack; j++)
        {
            for(int k = 0; k < this->papersInSession; k++)
            {
                for(int l = i + 1; l < this->parallelTracks; l++)
                {
                    for(int m = 0; m < this->papersInSession; m++)
                    {
                        x = newNode.get(i, j, k);
                        y = newNode.get(l, j, m);
                        if(x != -1 && y != -1){
                            score2 += this->distanceMatrix[x][y];
                        }
                        else if(x != -1 && y == -1){
                            score2 += this->maxDistanceArray[x];
                        }
                        else if(x == -1 && y != -1){
                            score1 += this->maxDistanceArray[y];
                        }
                        else if(x == -1 && y == -1){
                            score1 += this->maxDistance;
                        }
                    }
                }
            }
        }
    }
    //cout << "Score : " << score1+score2 << endl;
    return score1 + score2;
}

void AStar::printConference(char * filename)
{
    curNode.printNode(filename);
}

void AStar::printConference()
{
    for ( int i = 0; i < this->sessionsInTrack; i++ )
    {
        for ( int j = 0; j < this->parallelTracks; j++ )
        {
            for ( int k = 0; k < this->papersInSession; k++ )
            {
                cout << curNode.get(j, i, k) << " ";
            }
            if ( j != this->parallelTracks - 1 )
            {
                cout <<"| ";
            }
        }
        cout <<"\n";
    }
}

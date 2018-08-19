/* 
 * File:   AStar.cpp
 * Author: Shreshth Tuli
 * 
 */

#include "AStar.h"

AStar::AStar(int parallelTracks, int sessionsInTrack, int papersInSession, double tradeOffCoefficient)
{
    max_score = 0;
    parallelTracks = parallelTracks;
    sessionsInTrack = sessionsInTrack;
    papersInSession = papersInSession;
    n = parallelTracks * sessionsInTrack * papersInSession;
    tradeoffCoefficient = tradeOffCoefficient;

    Node *first_node = new Node(parallelTracks, sessionsInTrack, papersInSession);
    first_node->set(0, 0, 0, 0);
    queue.push(*first_node);
    index = 0;
}

void AStar::iterate()
{
    while(!queue.empty())
    {
        curNode = queue.top();
        queue.pop();
        generateSucessors();
    }

}

void AStar::generateSucessors()
{
    index++; // Increment index
    for(int i = 0; i < sessionsInTrack; i++)
    {
        for(int j = 0; j < parallelTracks; j++)
        {
            if( i > 1 && curNode.isSessionEmpty(j, i-1) )
            {
                continue;
            }
            newNode = Node(curNode.array);
            if(newNode.set(j, i, index))
            {
                calcScore(); // Calculate score of newNode
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
            if(distanceMatrix[i][j] > max){
                max = distanceMatrix[i][j];
            }
            if(distanceMatrix[i][j] < min)
            {
                min = distanceMatrix[i][j];
            }
        }
        maxDistanceArray[i] = max;
        maxSimilarityArray[i] = 1 - min;

        if(gmax > max)
        {
            gmax = max;
        }
        if(gmin < min)
        {
            gmin = min;
        }
    }

    maxDistance = gmax;
    maxSimilarity = 1 - gmin;
}

void AStar::calcScore()
{
    // Similarity Score
    double score1 = 0;
    double x;
    double y;
    for(int i = 0; i < parallelTracks; i++)
    {
        for(int j = 0; j < sessionsInTrack; j++)
        {
            for(int k = 0; k < papersInSession; k++)
            {
                for(int l = k+1; l < papersInSession; l++)
                {
                    x = newNode.get(i, j, k);
                    y = newNode.get(i, j, l);
                    if(x != -1 && y != -1){
                        score1 += distanceMatrix[k][l];
                    }
                    if(x != -1 && y == -1){
                        score1 += maxSimilarityArray[k];
                    }
                    if(x == -1 && y != -1){
                        score1 += maxSimilarityArray[l];
                    }
                    if(x == -1 && y == -1){
                        score1 += maxSimilarity;
                    }
                    
                }
            }
        }
    }    

    // Distance score
    double score2 = 0;
}

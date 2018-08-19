/* 
 * File:   Node.cpp
 * Author: Shreshth Tuli
 * 
 */

#include "Node.h"

Node::Node(int parallelTracks, int sessionsInTrack, int papersInSession)
{
    Node::parallelTracks = parallelTracks;
    Node::sessionsInTrack = sessionsInTrack;
    Node::papersInSession = papersInSession;

    Node::size = parallelTracks * sessionsInTrack * papersInSession;
    this->array = ( int * ) malloc ( sizeof (int ) * this->size  );
    for(int i = 0; i < Node::size; i++){
        this->array[i] = -1;
    }
}

Node::Node(int * node_array)
{
    this->array = ( int * ) malloc ( sizeof (int ) * this->size  );
    for(int i = 0; i < Node::size; i++){
        this->array[i] = node_array[i];
    }
}

int Node::get(int tracknumber, int sessionnumber, int paperIndex)
{
    return (this->array[paperIndex + Node::sessionsInTrack * (sessionnumber + (Node::parallelTracks * tracknumber))]);
}

void Node::set(int tracknumber, int sessionnumber, int paperIndex, int value)
{
    this->array[paperIndex + Node::sessionsInTrack * (sessionnumber + (Node::parallelTracks * tracknumber))] = value;
}

bool Node::isSessionFull(int tracknumber, int sessionnumber)
{
    for(int i = 0; i < this->papersInSession; i++)
    {
        if(this->get(tracknumber, sessionnumber, i) == -1){
            return false;
        }
    }
    return true;
}
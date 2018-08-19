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
    this-> score = 0;

    Node::size = parallelTracks * sessionsInTrack;
    this->array = ( Session * ) malloc ( sizeof (Session ) * Node::size );
    for(int i = 0; i < Node::size; i++){
        this->array[i] = Session (papersInSession);
    }
}

Node::Node(Session * node_array)
{
    this->score = 0;
    this->array = ( Session * ) malloc ( sizeof (Session ) * this->size  );
    for(int i = 0; i < Node::size; i++){
        this->array[i].copySession(node_array[i].papers);
    }
}

int Node::get(int tracknumber, int sessionnumber, int paperIndex)
{
    return (this->array[sessionnumber + (Node::parallelTracks * tracknumber)].getPaper(paperIndex));
}

bool Node::set(int tracknumber, int sessionnumber, int value)
{
    if(this->array[sessionnumber + (Node::parallelTracks * tracknumber)].isSessionFull()){
        return false;
    }
    this->array[sessionnumber + (Node::parallelTracks * tracknumber)].addPaper(value);
    return true;
}

bool Node::isSessionEmpty(int tracknumber, int sessionnumber)
{
    return this->array[sessionnumber + (Node::parallelTracks * tracknumber)].isSessionEmpty();
}

bool Node::isComplete()
{
    return this->num_elements == this->size;
}

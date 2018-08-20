/* 
 * File:   Node.cpp
 * Author: Shreshth Tuli
 * 
 */

#include "Node.h"

Node::Node()
{
    this-> score = 0;
    this->num_elements = 0;
}

Node::Node(int parallelTracks, int sessionsInTrack, int papersInSession)
{
    this->parallelTracks = parallelTracks;
    this->sessionsInTrack = sessionsInTrack;
    this->papersInSession = papersInSession;
    this->score = 0;
    this->num_elements = 0;

    this->size = parallelTracks * sessionsInTrack;
    this->array = ( Session * ) malloc ( sizeof (Session ) * size );
    for(int i = 0; i < this->size; i++){
        this->array[i] = Session (papersInSession);
    }
}

Node::Node(Session * node_array)
{
    this->score = 0;
    this->num_elements = 0;
    this->array = ( Session * ) malloc ( sizeof (Session ) * this->size  );
    for(int i = 0; i < this->size; i++){
        this->array[i].copySession(node_array[i].papers);
    }
}

int Node::get(int tracknumber, int sessionnumber, int paperIndex)
{
    return (this->array[sessionnumber + (this->parallelTracks * tracknumber)].getPaper(paperIndex));
}

bool Node::set(int tracknumber, int sessionnumber, int value)
{
    this->num_elements++;
    if(this->array[sessionnumber + (this->parallelTracks * tracknumber)].isSessionFull()){
        return false;
    }
    this->array[sessionnumber + (this->parallelTracks * tracknumber)].addPaper(value);
    return true;
}

bool Node::isSessionEmpty(int tracknumber, int sessionnumber)
{
    return this->array[sessionnumber + (this->parallelTracks * tracknumber)].isSessionEmpty();
}

bool Node::isComplete()
{
    return this->num_elements == this->size;
}

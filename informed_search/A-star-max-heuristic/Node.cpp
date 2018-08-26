/* 
 * File:   Node.cpp
 * Author: Shreshth Tuli
 * 
 */

#include "Node.h"
#include <fstream>

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
    this->array = new Session[this->size](papersInSession);
    for(int i = 0; i < this->size; i++){
        Session tempSession = Session(papersInSession);
        this->array[i] = tempSession;
    }
}

Node::Node(Session * node_array, int parallelTracks, int sessionsInTrack, int papersInSession, int num_el)
{
    this->parallelTracks = parallelTracks;
    this->sessionsInTrack = sessionsInTrack;
    this->papersInSession = papersInSession;
    this->score = 0;
    this->num_elements = num_el;
    this->size = parallelTracks * sessionsInTrack;
    this->array = new Session[this->size](papersInSession);
    for(int i = 0; i < this->size; i++){
        Session tempSession = Session(papersInSession);
        tempSession.num_papers = node_array[i].num_papers;
        for(int j = 0; j < this->papersInSession; j++){
            tempSession.papers[j] = node_array[i].papers[j];
        }
        this->array[i] = tempSession;
    }
}

int Node::get(int tracknumber, int sessionnumber, int paperIndex)
{
    return (this->array[tracknumber + (this->parallelTracks * sessionnumber)].getPaper(paperIndex));
}

bool Node::set(int tracknumber, int sessionnumber, int value)
{
    this->num_elements++;
    if(this->array[tracknumber + (this->parallelTracks * sessionnumber)].isSessionFull()){
        return false;
    }
    this->array[tracknumber + (this->parallelTracks * sessionnumber)].addPaper(value);
    return true;
}

bool Node::isSessionEmpty(int tracknumber, int sessionnumber)
{
    Session c = this->array[tracknumber + (this->parallelTracks * sessionnumber)];
    return c.isSessionEmpty();
}

bool Node::isComplete()
{
    return this->num_elements == this->size;
}

void Node::printNode(char* filename)
{
    ofstream ofile(filename);

    for ( int i = 0; i < sessionsInTrack; i++ )
    {
        for ( int j = 0; j < parallelTracks; j++ )
        {
            for ( int k = 0; k < papersInSession; k++ )
            {
                ofile<< this->get(j, i, k) << " ";
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

void Node::printNode()
{
    for ( int i = 0; i < sessionsInTrack; i++ )
    {
        for ( int j = 0; j < parallelTracks; j++ )
        {
            for ( int k = 0; k < papersInSession; k++ )
            {
                cout << this->get(j, i, k) << " ";
            }
            if ( j != parallelTracks - 1 )
            {
                cout <<"| ";
            }
        }
        cout <<"\n";
    }
}

Node::~Node()
{
    delete(array);
}
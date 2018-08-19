/* 
 * File:   Session.cpp
 * Author: Kapil Thakkar
 * 
 */

#include <errno.h>
#include <vector>

#include "Session.h"

Session::Session ( int papersInSession )
{
    this->papersInSession = papersInSession;
    this->num_papers = 0;
    initPapers ( papersInSession );
}

void Session::initPapers ( int papersInSession )
{
    this->papers = ( int * ) malloc ( sizeof (int ) * papersInSession );
    for ( int i = 0; i < papersInSession; i++ )
    {
        papers[i] = -1;
    }
}

int Session::getPaper ( int index )
{
    return papers[index];
}

void Session::addPaper ( int paperId )
{
    papers[num_papers++] = paperId;
}

bool Session::isSessionFull()
{
    return num_papers == papersInSession;
}

bool Session::isSessionEmpty()
{
    return num_papers == 0;
}

void Session::copySession(int * papers_copy)
{
    for(int i = 0; i < papersInSession; i++){
        papers[i] = papers_copy[i];
    }
}

void Session::printSession ( )
{
    for ( int i = 0; i < papersInSession ; i++ )
    {
        cout<<papers[i]<<" ";
    }
    cout<<endl;
}

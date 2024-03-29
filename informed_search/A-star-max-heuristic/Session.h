/* 
 * File:   Session.h
 * Author: Kapil Thakkar
 *
 */

#ifndef SESSION_H
#define	SESSION_H

#include <iostream>
#include <cstdlib>
using namespace std;

/**
 * Session holds an array of papers.
 * 
 * @author Kapil Thakkar
 *
 */

class Session {
    
private:    
    int papersInSession;    // number of papers    
    
public:
    int num_papers;

    int *papers;            // array of paper    

    /**
     * Constructor
     * 
     * @param papersInSession the number of papers in a session.
     */
    Session();

    /**
     * Initialize the array of papers.
     * 
     * @param papersInSession the number of papers in a session.
     */
    void initPapers(int papersInSession);

    /**
     * Get the id of the paper at the specified index
     * 
     * @param index the index of the paper
     * @return the id of the paper
     */
    int getPaper(int index);

    /**
     * Set the paper id at the specified index.
     * 
     * @param index is the index in the array
     * @param paperId is the id of the paper
     */
    void addPaper(int paperId);

    /**
     * Returns if session is full
     */
    bool isSessionFull();

    /**
     * Returns if session is empty
     */
    bool isSessionEmpty();

    /**
     * Copy Session
     */
    void copySession(int * papers_copy);

    /**
     * Print the papers present in current session 
     *
     */
    void printSession();
};

#endif	/* SESSION_H */


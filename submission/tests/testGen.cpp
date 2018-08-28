/* 
 * File:   Node.cpp
 * Author: Shreshth Tuli
 * 
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>     // std::string, std::stoi
using namespace std;

int main(int argc, char const *argv[])
{
    if(argc < 7){
        exit;
    }
    int t = std::stoi(argv[1]);
    int p = std::stoi(argv[2]);
    int k = std::stoi(argv[3]);
    int n = t*p*k;
    double tradeOff = stoi(argv[4]);
    int timeLimit = std::stoi(argv[5]);
    std::string filename = (argv[6]);

    ofstream ofile(filename);
    ofile << timeLimit << endl;
    ofile << k << endl;
    ofile << p << endl;
    ofile << t << endl;
    ofile << tradeOff << endl;
    double ** tempDistanceMatrix = new double*[n];
    for ( int i = 0; i < n; ++i )
    {
        tempDistanceMatrix[i] = new double[n];
    }

    for(int i = 0; i < n; i++)
    {
        tempDistanceMatrix[i][i] = 0;
        for(int j = i+1; j < n; j++)
        {
            double k = (rand() % 11) / 10.0;
            tempDistanceMatrix[i][j] = k;
            tempDistanceMatrix[j][i] = k;
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n-1; j++)
        {
            ofile << tempDistanceMatrix[i][j] << " ";
        }
        ofile << tempDistanceMatrix[i][n-1] <<"\n";
    }

    return 0;

}

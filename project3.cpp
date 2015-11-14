// Author:  Yupeng Wang
// EECS 281
// Project 3
///////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "project3.h"

using namespace std;


int main(int argc, const char * argv[])
{

    ios_base::sync_with_stdio(false);
    
    ostringstream os;
    
    int counter = 0;
    int counter2 = 0;
    
    string line;
    string parse;
    char command;
    
    pair<unordered_map<string, logEntry>::iterator,bool> check;
    
    vector<logEntry> masterLog;
    unordered_map<string, vector<logEntry>> excerpt;
    
    if (strcmp(argv[1],"--help") == 0|| strcmp(argv[1],"-h") == 0) {
        cout << "Use this program to do a variety of search, sort,"
            << " and move operations to a log file" << '\n';
        exit(0);
    }
    
    else {
        ifstream myFile(argv[1]);
        
        if (myFile.is_open()) {
            while (getline(myFile,line)) {
                logEntry next;
                counter = line.find('|',0);
                next.timeStamp = line.substr(0, counter);
                counter2 = line.find('|',counter + 1);
                next.category = line.substr(counter + 1,counter2 - counter - 1);
                next.message = line.substr(counter2 + 1,string::npos);
                masterLog.push_back(next);
            }
        }
        
        cin >> command;
        while (command != 'q') {
            
            if (command == '#') break;
            else if (command == 'p') {
                
            }
            else if (command == 'g') {
                
            }
            else if (command == 'l') {
                
            }
            else if (command == 's') {
                
            }
            else if (command == 'e') {
                
            }
            else if (command == 'b') {
                
            }
            else if (command == 'd') {
                
            }
            else if (command == 'r') {
                
            }
            else if (command == 'a') {
                
            }
            else if (command == 'k') {
                
            }
            else if (command == 'c') {
                
                
            }
            else if (command == 't') {
                
            }
            
            cin >> command;
        }
        
        
    }
    
    return 0;
}


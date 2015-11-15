// Author:  Yupeng Wang
// EECS 281
// Project 3
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstring>
#include "project3.h"

using namespace std;


int main(int argc, const char * argv[])
{

    ios_base::sync_with_stdio(false);
    
    int counter = 0;
    int counter2 = 0;
    
    string line;
    string parse;
    char* command;
    
    pair<unordered_map<string, logEntry>::iterator,bool> check;
    
    vector<pair<int,logEntry>> masterLog;
    vector<pair<int,logEntry>*> excerpt;
    
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
                pair<int,logEntry> add(masterLog.size(),next);
                masterLog.push_back(add);
            }
        }
        
        cout << "% ";
        cin >> command;
        while (strcmp(command,"q") != 0) {
            
            if (strcmp(command,"#") == 0) break;
            else if (strcmp(command,"p") == 0) {
                for (int i = 0; i < excerpt.size(); ++i) {
                    cout << i << "|" << excerpt[i]->first << "|" << excerpt[i]->
                        second.timeStamp << "|" << excerpt[i]->second.category << "|"
                        << excerpt[i]->second.message << '\n';
                }
            }
            else if (strcmp(command,"g") == 0) {
                
            }
            else if (strcmp(command,"l") == 0) {
                excerpt.clear();
                cout << "excerpt list cleared" << '\n';
            }
            else if (strcmp(command,"s") == 0) {
                
            }
            else if (strcmp(&command[0],"e") == 0) {
                char* num = command + 2;
                counter = atoi(num);
                pair<int,logEntry>* move;
                if (counter < excerpt.size()) {
                    move = excerpt[counter];
                    excerpt.erase(excerpt.begin() + counter);
                    excerpt.push_back(move);
                    cout << "excerpt list entry " << counter << " moved" << '\n';
                }
            }
            else if (strcmp(&command[0],"b") == 0) {
                char* num = command + 2;
                counter = atoi(num);
                pair<int,logEntry>* move;
                if (counter < excerpt.size()) {
                    move = excerpt[counter];
                    excerpt.erase(excerpt.begin() + counter);
                    excerpt.insert(excerpt.begin(),move);
                    cout << "excerpt list entry " << counter << " moved" << '\n';
                }
                
            }
            else if (strcmp(&command[0],"d") == 0) {
                char* num = command + 2;
                counter = atoi(num);
                if (counter < excerpt.size()) {
                    excerpt.erase(excerpt.begin() + counter);
                    cout << "excerpt list entry " << counter << " deleted" << '\n';
                }
            }
            else if (strcmp(command,"r") == 0) {
                
            }
            else if (strcmp(&command[0],"a") == 0) {
                char* num = command + 2;
                counter = atoi(num);
                if (counter < excerpt.size()) {
                    excerpt.push_back(&masterLog[counter]);
                    cout << "log entry " << counter << " appended" << '\n';
                }
            }
            else if (strcmp(&command[0],"k") == 0) {
                
            }
            else if (strcmp(&command[0],"c") == 0) {
                
                
            }
            else if (strcmp(&command[0],"t") == 0) {
                
            }
            else cout << "Invalid command. Try again" << '\n';
            cout << "% ";
            cin >> command;
        }
        
        
    }
    
    return 0;
}


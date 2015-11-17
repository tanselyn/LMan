// Author:  Yupeng Wang
// EECS 281
// Project 3
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iterator>
#include "project3.h"

using namespace std;

vector<logEntry*>::iterator lowerBoundFunc(vector<logEntry*>::iterator first,
                                vector<logEntry*>::iterator last, const string &val) {
    vector<logEntry*>::iterator it;
    int count = distance(first,last);
    while (count>0)
    {
        it = first; int step=count/2; advance (it,step);
        if ((*it)->timeStamp < val) {
            first = ++it;
            count -= step + 1;
        }
        else count = step;
    }
    return first;
}


int main(int argc, const char * argv[])
{
    
    ios_base::sync_with_stdio(false);
    
    bool inOrder = false;
    int counter = 0;
    int counter2 = 0;
    
    string line;
    string command;
    logEntry next;
    timeStampCompare comp;
    
    vector<logEntry> masterLog;
    vector<logEntry*> excerpt;
    vector<logEntry*> results;
    vector<string> keywords;
    
    vector<logEntry*> timeSearchList;
    unordered_map<string,set<logEntry*,timeStampCompare>> categorySearchList;
    unordered_map<string,set<logEntry*,timeStampCompare>> keywordSearchList;
    
    if (strcmp(argv[1],"--help") == 0|| strcmp(argv[1],"-h") == 0) {
        cout << "Use this program to do a variety of search, sort,"
        << " and move operations to a log file" << '\n';
        exit(0);
    }
    
    else {
        ifstream myFile(argv[1]);
        
        if (myFile.is_open()) {
            while (getline(myFile,line)) {
                counter = line.find('|',0);
                next.timeStamp = line.substr(0, counter);
                counter2 = line.find('|',counter + 1);
                next.category = line.substr(counter + 1,counter2 - counter - 1);
                next.message = line.substr(counter2 + 1,string::npos);
                next.entryID = masterLog.size();
                
                masterLog.push_back(next);
                
            }
        }
        myFile.close();
        
        cout << masterLog.size() << " entries read" << '\n';
        
        for (int i = 0; i < masterLog.size(); ++i) {
            for (int j = 0; j < masterLog[i].category.size(); ++j) {
                masterLog[i].lowerCaseCategory += tolower(masterLog[i].category[j]);
            }
            for (int j = 0; j < masterLog[i].message.size(); ++j) {
                masterLog[i].lowerCaseMessage += tolower(masterLog[i].message[j]);
            }
        }
        
        cout << "% ";
        getline(cin,command);
        while (command[0] != 'q') {
            
            if (command[0] == '#') {}
            
            else if (command[0] == 'p') {
                for (int i = 0; i < excerpt.size(); ++i) {
                    cout << i << "|" << excerpt[i]->entryID << "|" << excerpt[i]->
                    timeStamp << "|" << excerpt[i]->category << "|"
                    << excerpt[i]->message << '\n';
                }
            }
            else if (command[0] == 'g') {
                if (!results.empty()) {
                    for (int i = 0; i < results.size(); ++i) {
                        cout << results[i]->entryID << "|" << results[i]->
                        timeStamp << "|" << results[i]->category << "|"
                        << results[i]->message << '\n';
                    }
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'l') {
                inOrder = false;
                excerpt.clear();
                cout << "excerpt list cleared" << '\n';
            }
            else if (command[0] == 's') {
                if (inOrder == false) {
                    sort(excerpt.begin(),excerpt.end(),comp);
                    cout << "excerpt list sorted" << '\n';
                    inOrder = true;
                }
            }
            else if (command[0] == 'e') {
                inOrder = false;
                string parse = command.substr(2);
                counter = stoi(parse);
                if (counter < excerpt.size()) {
                    logEntry* move = excerpt[counter];
                    excerpt.erase(excerpt.begin() + counter);
                    excerpt.push_back(move);
                    cout << "excerpt list entry " << counter << " moved" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'b') {
                inOrder = false;
                string parse = command.substr(2);
                counter = stoi(parse);
                if (counter < excerpt.size()) {
                    logEntry* move = excerpt[counter];
                    excerpt.erase(excerpt.begin() + counter);
                    excerpt.insert(excerpt.begin(),move);
                    cout << "excerpt list entry " << counter << " moved" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'd') {
                string parse = command.substr(2);
                counter = stoi(parse);
                if (counter < excerpt.size()) {
                    excerpt.erase(excerpt.begin() + counter);
                    cout << "excerpt list entry " << counter << " deleted" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'r') {
                if (!results.empty()) {
                    for (int i = 0; i < results.size(); ++i) {
                        excerpt.push_back(results[i]);
                    }
                    cout << results.size() << " log entries appended" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'a') {
                inOrder = false;
                string parse = command.substr(2);
                counter = stoi(parse);
                if (counter < masterLog.size()) {
                    excerpt.push_back(&masterLog[counter]);
                    cout << "log entry " << counter << " appended" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'k') {
                if (keywordSearchList.empty()) {
                    for (int i = i; i < masterLog.size(); ++i) {
                        auto indexFirst = masterLog[i].lowerCaseCategory.begin();
                        auto indexLast = masterLog[i].lowerCaseCategory.begin();
                        while ((indexFirst = find_if(indexLast,masterLog[i].lowerCaseCategory.end(),
                                                     [](char c) {return isalnum(c);})) !=
                                                      masterLog[i].lowerCaseCategory.end()) {
                            indexLast = find_if(indexFirst,masterLog[i].lowerCaseCategory.end(),
                                                    [](char c) {return !isalnum(c);});
                            string word(indexFirst,indexLast);
                            
                            if (!word.empty()) {
                                keywordSearchList[word].insert(&masterLog[i]);
                                
                            }
                        }
                        indexFirst = masterLog[i].lowerCaseMessage.begin();
                        indexLast = masterLog[i].lowerCaseMessage.begin();
                        while ((indexFirst = find_if(indexLast,masterLog[i].lowerCaseMessage.end(),
                                                     [](char c) {return isalnum(c);})) !=
                                                     masterLog[i].lowerCaseMessage.end()) {
                            indexLast = find_if(indexFirst, masterLog[i].lowerCaseMessage.end(),
                                                [](char c) {return !isalnum(c);});
                            string word(indexFirst, indexLast);
                            if (!word.empty()) {
                                keywordSearchList[word].insert(&masterLog[i]);
                            }
                        }
                    }
                }
                results.clear();
                counter2 = 0;
                string parse = command.substr(2);
                set<logEntry*,timeStampCompare> v;
                
                auto indexFirst = parse.begin();
                auto indexLast = parse.begin();
                while ((indexFirst = find_if(indexLast,parse.end(),[](char c) {return isalnum(c);}))
                       != parse.end()) {
                    indexLast = find_if(indexFirst,parse.end(),[](char c) {return !isalnum(c);});
                    string word(indexFirst,indexLast);
                    for (int i = 0; i < word.size(); ++i) {
                        word[i] = tolower(word[i]);
                    }
                    auto location = keywordSearchList.find(word);
                    if (location == keywordSearchList.end()) {
                        v.clear();
                        break;
                    }
                    else {
                        if (v.empty()) {
                            v = keywordSearchList[word];
                        }
                        set<logEntry*,timeStampCompare> temp;
                        set_intersection(location->second.begin(),location->second.end(),
                                        v.begin(),v.end(),inserter(temp,temp.begin()),
                                         comp);
                        v = temp;
                        if (v.empty()) break;
                    }
                }
                
                counter2 = v.size();
                for (logEntry* a : v) {
                    results.push_back(a);
                }
                
                cout << counter2 << " entries found" << '\n';
            }
            else if (command[0] == 'c') {
                auto location = categorySearchList.begin();
                if (categorySearchList.empty()) {
                    for (int i = 0; i < masterLog.size(); ++i) {
                        categorySearchList[masterLog[i].lowerCaseCategory].insert
                                (&masterLog[i]);
                    }
                    
                }
                results.clear();
                counter2 = 0;
                string parse = command.substr(2);
                for (int i = 0; i < parse.size(); ++i) {
                    parse[i] = tolower(parse[i]);
                }
                location = categorySearchList.find(parse);
                if (location != categorySearchList.end()) {
                    counter2 = location->second.size();
                    for (auto a : location->second) {
                        results.push_back(a);
                    }
                }
                
                cout << counter2 << " entries found" << '\n';
                
                
            }
            else if (command[0] == 't') {
                if (timeSearchList.empty()) {
                    for (int i = 0; i < masterLog.size(); ++i) {
                        timeSearchList.push_back(&masterLog[i]);
                    }
                    sort(timeSearchList.begin(),timeSearchList.end(),comp);
                }
                
                results.clear();
                counter2 = 0;
                string parse = command.substr(2);
                counter = parse.find('|',0);
                string start = parse.substr(0,counter);
                string end = parse.substr(counter + 1,string::npos);
                if (start.size() == 14 && end.size() == 14) {
                
                    vector<logEntry*>::iterator lower = lowerBoundFunc(timeSearchList.begin(),
                                                            timeSearchList.end(), start);
                
                    vector<logEntry*>::iterator upper = lowerBoundFunc(timeSearchList.begin(),
                                                            timeSearchList.end(), end);
                    while (lower != upper) {
                        results.push_back(*lower);
                        ++lower;
                        ++counter2;
                    }
                    cout << counter2 << " entries found" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else cerr << "Error: Invalid command" << '\n';
            cout << "% ";
            getline(cin,command);
        }
        
        
    }
    
    return 0;
}
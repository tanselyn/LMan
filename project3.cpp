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
#include <algorithm>
#include <cctype>
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
    bool resultsInOrder = false;
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
    unordered_map<string,vector<int>> categorySearchList;
    unordered_map<string,vector<int>> keywordSearchList;
    
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
                for (int i = 0; i < next.category.size(); ++i) {
                    next.lowerCaseCategory += tolower(next.category[i]);
                }
                for (int i = 0; i < next.message.size(); ++i) {
                    next.lowerCaseMessage += tolower(next.message[i]);
                }
                
                masterLog.push_back(next);
                timeSearchList.push_back(&next);
                
                unordered_map<string,vector<int>>::iterator location
                    = categorySearchList.find(next.lowerCaseCategory);
                if (location != categorySearchList.end()) {
                    location->second.push_back(masterLog.size() - 1);
                }
                else {
                    categorySearchList[next.lowerCaseCategory];
                }
                string word;
                for (int i = 0; i < next.lowerCaseCategory.size(); ++i) {
                    if (!isalnum(next.lowerCaseCategory[i])) {
                        if (!word.empty()) {
                            location = keywordSearchList.find(word);
                            if (location != keywordSearchList.end()) {
                                location->second.push_back(masterLog.size() - 1);
                            }
                            else keywordSearchList[word];
                            word.clear();
                        }
                    }
                    else word += next.lowerCaseCategory[i];
                }
                
                for (int i = 0; i < next.lowerCaseMessage.size(); ++i) {
                    if (!isalnum(next.lowerCaseMessage[i])) {
                        if (!word.empty()) {
                            location = keywordSearchList.find(word);
                            if (location != keywordSearchList.end()) {
                                location->second.push_back(masterLog.size() - 1);
                            }
                            else keywordSearchList[word];
                            word.clear();
                        }
                    }
                    else word += next.lowerCaseMessage[i];
                }
            }
        }
        myFile.close();
        
        sort(timeSearchList.begin(),timeSearchList.end(),comp);
        
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
                    if (resultsInOrder == false) {
                        sort(results.begin(),results.end(),comp);
                        resultsInOrder = true;
                    }
                    for (int i = 0; i < results.size(); ++i) {
                        cout << results[i]->entryID << "|" << results[i]->
                        timeStamp << "|" << results[i]->category << "|"
                        << results[i]->message << '\n';
                    }
                }
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
                
            }
            else if (command[0] == 'd') {
                string parse = command.substr(2);
                counter = stoi(parse);
                if (counter < excerpt.size()) {
                    excerpt.erase(excerpt.begin() + counter);
                    cout << "excerpt list entry " << counter << " deleted" << '\n';
                }
            }
            else if (command[0] == 'r') {
                if (!results.empty()) {
                    if (resultsInOrder == false) {
                        sort(results.begin(),results.end(),comp);
                        resultsInOrder = true;
                    }
                    for (int i = 0; i < results.size(); ++i) {
                        excerpt.push_back(results[i]);
                    }
                    cout << results.size() << " log entries appended" << '\n';
                }
            }
            else if (command[0] == 'a') {
                inOrder = false;
                string parse = command.substr(2);
                counter = stoi(parse);
                if (counter < masterLog.size()) {
                    excerpt.push_back(&masterLog[counter]);
                    cout << "log entry " << counter << " appended" << '\n';
                }
            }
            else if (command[0] == 'k') {
                resultsInOrder = false;
                bool resultsExist = true;
                results.clear();
                counter2 = 0;
                string parse = command.substr(2);
                string word;
                for (int i = 0; i < parse.size(); ++i) {
                    if (!isalnum(parse[i])) {
                        if (!word.empty()) {
                            keywords.push_back(word);
                            word.clear();
                        }
                    }
                    else word += parse[i];
                }
                vector<int> v(1);
                vector<int>::iterator intersection = v.begin();
                unordered_map<string,vector<int>>::iterator location1;
                unordered_map<string,vector<int>>::iterator location2;
                for (int i = 0; i < keywords.size(); i += 2) {
                    location1 = keywordSearchList.find(keywords[i]);
                    location2 = keywordSearchList.find(keywords[i + 1]);
                    if (location1 == keywordSearchList.end() || location2 ==
                        keywordSearchList.end()) {
                        resultsExist = false;
                        break;
                    }
                    else {
                        intersection = (location1->second.begin(),location1->second.end(),
                                        location2->second.begin(),location2->second.end(),
                                        intersection);
                    }
                }
                if (resultsExist) {
                    while (!v.empty()) {
                        counter2 = v.size();
                        for (int i = 0; i < v.size(); ++i) {
                            results.push_back(&masterLog[v[1]]);
                        }
                    }
                }
                resultsInOrder = true;
                
                cout << counter2 << " entries found" << '\n';
            }
            else if (command[0] == 'c') {
                resultsInOrder = false;
                results.clear();
                counter2 = 0;
                string parse = command.substr(2);
                unordered_map<string,vector<int>>::iterator location = categorySearchList.find(parse);
                if (location != categorySearchList.end()) {
                    counter2 = location->second.size();
                }
                for (int i = 0; i < location->second.size(); ++i) {
                    results.push_back(&masterLog[location->second[i]]);
                }
                
                cout << counter2 << " entries found" << '\n';
                
                
            }
            else if (command[0] == 't') {
                resultsInOrder = true;
                results.clear();
                counter2 = 0;
                string parse = command.substr(2);
                counter = parse.find('|',0);
                string start = parse.substr(0,counter);
                string end = parse.substr(counter + 1,string::npos);

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
            else cerr << "Invalid command. Try again" << '\n';
            cout << "% ";
            getline(cin,command);
        }
        
        
    }
    
    return 0;
}
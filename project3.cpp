// Author:  Yupeng Wang
// EECS 281
// Project 3
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <deque>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iterator>
#include "project3.h"

using namespace std;

int main(int argc, const char * argv[])
{
    
    ios_base::sync_with_stdio(false);
    
    argc = argc;
    
    ostringstream os;
    
    vector<logEntry> masterLog;
    deque<unsigned int> excerpt;
    deque<unsigned int> results;
    
    unordered_map<string,vector<unsigned int>> categorySearchList;
    unordered_map<string,vector<unsigned int>> keywordSearchList;
    
    sortCompare comp;
    timeStampCompare comp2;
    
    bool inOrder = false;
    bool previousSearch = false;
    bool timeSearch = false;
    bool resultsExist = true;
    
    if (strcmp(argv[1],"--help") == 0|| strcmp(argv[1],"-h") == 0) {
        os << "Use this program to do a variety of search, sort,"
        << " and move operations to a log file" << '\n';
        exit(0);
    }
    
    else {
        ifstream myFile(argv[1]);
        
        if (myFile.is_open()) {
            string line;
            while (getline(myFile,line)) {
                int counter = line.find_first_of('|',0);
                int counter2 = line.find_last_of('|');
                logEntry next(string(line,0,counter),string(line,counter + 1,counter2 - counter - 1),string(line,counter2 + 1,(int)string::npos),masterLog.size());
                
                masterLog.push_back(next);
                
            }
        }
        myFile.close();
        
        os << masterLog.size() << " entries read" << '\n';
        
        for (int i = 0; i < (int)masterLog.size(); ++i) {
            transform (masterLog[i].category.begin(),masterLog[i].category.end(),
                       back_inserter(masterLog[i].lowerCaseCategory),::tolower);
        }
        sort(masterLog.begin(),masterLog.end(),comp);
        
        string command;
        os << "% ";
        getline(cin,command);
        while (true) {
            
            if (command[0] == 'q') break;
            else if (command[0] == '#') {}
            else if (command[0] == 'p') {
                for (int i = 0; i < (int)excerpt.size(); ++i) {
                    os << i << "|" << masterLog[excerpt[i]].entryID << "|"
                    << masterLog[excerpt[i]].timeStamp << "|" << masterLog[excerpt[i]].
                    category << "|" << masterLog[excerpt[i]].message << '\n';
                }
            }
            else if (command[0] == 'g') {
                if (timeSearch) {
                    if (!results.empty()) {
                        while (results[0] != results [1]) {
                            os << masterLog[results[0]].entryID << "|" << masterLog[results[0]].
                            timeStamp << "|" << masterLog[results[0]].category << "|"
                            << masterLog[results[0]].message << '\n';
                            ++results[0];
                        }
                    }
                }
                else if (previousSearch) {
                    for (int i = 0; i < (int)results.size(); ++i) {
                        os << masterLog[results[i]].entryID << "|" << masterLog[results[i]].
                        timeStamp << "|" << masterLog[results[i]].category << "|"
                        << masterLog[results[i]].message << '\n';
                    }
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'l') {
                inOrder = false;
                excerpt.clear();
                os << "excerpt list cleared" << '\n';
            }
            else if (command[0] == 's') {
                if (inOrder == false) {
                    sort(excerpt.begin(),excerpt.end());
                    inOrder = true;
                }
                os << "excerpt list sorted" << '\n';
            }
            else if (command[0] == 'e') {
                inOrder = false;
                string parse(command,2,string::npos);
                unsigned int counter = stoi(parse);
                if (counter < excerpt.size()) {
                    if (counter < excerpt.size() - 1) {
                        unsigned int move = excerpt[counter];
                        excerpt.erase(excerpt.begin() + counter);
                        excerpt.push_back(move);
                    }
                    os << "excerpt list entry " << counter << " moved" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'b') {
                inOrder = false;
                string parse(command,2,string::npos);
                unsigned int counter = stoi(parse);
                if (counter < excerpt.size()) {
                    if (counter > 0) {
                        unsigned int move = excerpt[counter];
                        excerpt.erase(excerpt.begin() + counter);
                        excerpt.push_front(move);
                    }
                    os << "excerpt list entry " << counter << " moved" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'd') {
                string parse(command,2,string::npos);
                unsigned int counter = stoi(parse);
                if (counter < excerpt.size()) {
                    excerpt.erase(excerpt.begin() + counter);
                    os << "excerpt list entry " << counter << " deleted" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'r') {
                if (timeSearch) {
                    if (!results.empty()) {
                        os << results[1] - results[0] << " log entries appended" << '\n';
                        unsigned int counter = results[0];
                        while (counter != results[1]) {
                            excerpt.push_back(counter);
                            ++counter;
                        }
                    }
                    else os << results.size() << " log entries appended" << '\n';
                }
                else if (previousSearch) {
                    for (int i = 0; i < (int)results.size(); ++i) {
                        excerpt.push_back(results[i]);
                    }
                    os << results.size() << " log entries appended" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'a') {
                inOrder = false;
                string parse(command,2,string::npos);
                unsigned counter = stoi(parse);
                if (counter < masterLog.size()) {
                    for (unsigned int i = 0; i < masterLog.size(); ++i) {
                        if (masterLog[i].entryID == counter) {
                            excerpt.push_back(i);
                        }
                    }
                    os << "log entry " << counter << " appended" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else if (command[0] == 'k') {
                previousSearch = true;
                timeSearch = false;
                resultsExist = true;
                if (keywordSearchList.empty()) {
                    for (int i = 0; i < (int)masterLog.size(); ++i) {
                        auto indexFirst = masterLog[i].lowerCaseCategory.begin();
                        auto indexLast = masterLog[i].lowerCaseCategory.begin();
                        while ((indexFirst = find_if(indexLast,masterLog[i].lowerCaseCategory.end(),
                                                     [](char c) {return isalnum(c);})) !=
                               masterLog[i].lowerCaseCategory.end()) {
                            indexLast = find_if(indexFirst,masterLog[i].lowerCaseCategory.end(),
                                                [](char c) {return !isalnum(c);});
                            string word(indexFirst,indexLast);
                            
                            if (!word.empty()) {
                                keywordSearchList[word].push_back(i);
                            }
                        }
                        indexFirst = masterLog[i].message.begin();
                        indexLast = masterLog[i].message.begin();
                        while ((indexFirst = find_if(indexLast,masterLog[i].message.end(),
                                                     [](char c) {return isalnum(c);})) !=
                               masterLog[i].message.end()) {
                            indexLast = find_if(indexFirst, masterLog[i].message.end(),
                                                [](char c) {return !isalnum(c);});
                            string word(indexFirst, indexLast);
                            if (!word.empty()) {
                                transform (indexFirst,indexLast,word.begin(),::tolower);
                                keywordSearchList[word].push_back(i);
                            }
                        }
                    }
                }
                results.clear();
                string parse(command,2,string::npos);
                deque<vector<unsigned int>> intersections;
                
                auto indexFirst = parse.begin();
                auto indexLast = parse.begin();
                while ((indexFirst = find_if(indexLast,parse.end(),[](char c) {return isalnum(c);}))
                       != parse.end()) {
                    indexLast = find_if(indexFirst,parse.end(),[](char c) {return !isalnum(c);});
                    string word(indexFirst,indexLast);
                    transform(indexFirst,indexLast,word.begin(),::tolower);
                    auto location = keywordSearchList.find(word);
                    if (location == keywordSearchList.end()) {
                        resultsExist = false;
                        break;
                    }
                    intersections.push_back(location->second);
                }
                while (intersections.size() > 1) {
                    vector<unsigned int> temp;
                    set_intersection(intersections.begin()->begin(),intersections.begin()->end(),
                                     (intersections.begin() + 1)->begin(),(intersections.begin() + 1)
                                     ->end(),back_inserter(temp));
                    if (temp.empty()) {
                        resultsExist = false;
                        break;
                    }
                    intersections.push_back(temp);
                    intersections.pop_front();
                    intersections.pop_front();
                }
                int counter2 = 0;
                if (resultsExist) {
                    auto newEnd = unique(intersections.begin()->begin(),intersections.
                                         begin()->end());
                    intersections.begin()->resize(distance(intersections.begin()->begin(),newEnd));
                    counter2 = intersections.begin()->size();
                    for (int i = 0; i < (int)intersections.begin()->size(); ++i) {
                        results.push_back((intersections[0])[i]);
                    }
                }
                os << counter2 << " entries found" << '\n';
            }
            else if (command[0] == 'c') {
                previousSearch = true;
                timeSearch = false;
                auto location = categorySearchList.begin();
                if (categorySearchList.empty()) {
                    for (int i = 0; i < (int)masterLog.size(); ++i) {
                        categorySearchList[masterLog[i].lowerCaseCategory].push_back(i);
                    }
                }
                results.clear();
                unsigned int counter2 = 0;
                string parse(command,2,string::npos);
                for (int i = 0; i < (int)parse.size(); ++i) {
                    parse[i] = tolower(parse[i]);
                }
                location = categorySearchList.find(parse);
                if (location != categorySearchList.end()) {
                    counter2 = location->second.size();
                    for (int i = 0; i < (int)location->second.size(); ++i) {
                        results.push_back(location->second[i]);
                    }
                }
                
                os << counter2 << " entries found" << '\n';
            }
            else if (command[0] == 't') {
                previousSearch = false;
                timeSearch = true;
                
                results.clear();
                unsigned int counter2 = 0;
                string parse(command,2,string::npos);
                int counter = parse.find('|',0);
                string start(parse,0,counter);
                string end(parse,counter + 1,string::npos);
                if (start.size() == 14 && end.size() == 14) {
                    
                    auto lower = lower_bound(masterLog.begin(),masterLog.end(),start,comp2);
                    auto upper = lower_bound(masterLog.begin(),masterLog.end(),end,comp2);
                    
                    if (lower != upper) {
                        counter2 = upper - lower;
                        results.push_back(lower - masterLog.begin());
                        results.push_back(upper - masterLog.begin());
                    }
                    os << counter2 << " entries found" << '\n';
                }
                else cerr << "Error: Invalid command" << '\n';
            }
            else cerr << "Error: Invalid command" << '\n';
            os << "% ";
            getline(cin,command);
        }
    }
    cout << os.str();
    return 0;
}
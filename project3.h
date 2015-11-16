//
//  project3.h
//  LMan
//
//  Created by Hannah Wang on 11/13/15.
//  Copyright (c) 2015 Hannah. All rights reserved.
//

#ifndef LMan_project3_h
#define LMan_project3_h

#include <string>

struct logEntry {
    std::string timeStamp;
    std::string category;
    std::string message;
    std::string lowerCaseCategory;
    std::string lowerCaseMessage;
    
    logEntry(): timeStamp("a"), category("a"), message("a"),
                lowerCaseCategory("a"), lowerCaseMessage("a") {}
    
    void operator=(const logEntry &other) {
        timeStamp = other.timeStamp;
        category = other.category;
        message = other.message;
        lowerCaseCategory = other.lowerCaseCategory;
        lowerCaseMessage = other.lowerCaseMessage;
    }
};

struct timeStampCompare {
    bool operator() (std::pair<int,logEntry>* rhs, std::pair<int,logEntry>* lhs) const {
        if (rhs->second.timeStamp == lhs->second.timeStamp) {
            if (rhs->second.category == lhs->second.category) {
                return rhs->first < lhs->first;
            }
            else return rhs->second.category < lhs->second.category;
        }
        else return rhs->second.timeStamp < lhs->second.timeStamp;
    }
};

struct timeSearchCompare {
    bool operator() (std::pair<std::string,logEntry*> &rhs,
                     std::pair<std::string,logEntry*> &lhs) const {
        if (rhs.first == lhs.first) {
            if (rhs.second->category == lhs.second->category) {
                return rhs.second < lhs.second;
            }
            else return rhs.second->category < lhs.second->category;
        }
        else return rhs.second->timeStamp < lhs.second->timeStamp;
    }
};

#endif
